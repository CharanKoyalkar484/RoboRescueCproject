#include "SerialLinux.h"
#include "iostream"
/// @cond

SerialLinux::SerialLinux(const char* deviceName, unsigned int baudrate) 
{ 
	open(deviceName, baudrate);
}

SerialLinux::~SerialLinux() 
{
	close();
}

int SerialLinux::open(const char * device, unsigned int bauds)
{
	filedescriptor = ::open(device, O_RDWR | O_NOCTTY | O_NDELAY);
	if (filedescriptor == -1) 
	{
		std::cout << "Failed opening" << std::endl;
		return -1;
	}
	if (fcntl (filedescriptor, F_SETFL, FNDELAY) == 11)
	{
				std::cout << "Failed opening" << std::endl;

		return -2;
	}
	struct termios options;
	bzero (&options, sizeof (options));
	speed_t speed;
	switch(bauds) 
	{
		case 110 :     
			speed = B110; break;
		case 300 :     
			speed = B300; break;
		case 600 :     
			speed = B600; break;
		case 1200 :     
			speed = B1200; break;
		case 2400 :     
			speed = B2400; break;
		case 4800 :     
			speed = B4800; break;
		case 9600 :     
			speed = B9600; break;
		case 19200 :    
			speed = B19200; break;
		case 38400 :    
			speed = B38400; break;
		case 57600 :    
			speed = B57600; break;
		case 115200 :   
			speed = B115200; break;
		default :       
			return -3;
	}
	if (cfsetispeed (&options, speed) == -1 || cfsetospeed (&options, speed) == -1)
	{
		std::cout << "Failed opening" << std::endl;

		return -4;
	}
	
	options.c_cflag |= ( CLOCAL | CREAD |  CS8);
	options.c_cflag &= ~(PARENB | PARODD);
	options.c_cflag &= ~(CSTOPB);
	options.c_iflag |= ( IGNPAR | IGNBRK );
	options.c_cflag &= ~(CRTSCTS);
	options.c_cc[VTIME] = 0;
	options.c_cc[VMIN] = 2;
	if (tcsetattr (filedescriptor, TCSANOW, &options) == -1)
	{
		std::cout << "Failed opening" << std::endl;

		return -5;
	}
	return 1;
}

/*! \brief Close the connection with the current device
 */
void SerialLinux::close()
{
	::close (filedescriptor);
}

/*!  \brief Wait for a char from the serial device and return the data read
     \param pChar : char read on the serial device
     \return 1 success
     \return -1 error while reading the char
 */
int SerialLinux::readChar(char * pChar)
{
	if (::read (filedescriptor, pChar, 1) != 1)
	{
		return -1;
	}
	return 1;
}

/*!  \brief Write a char on the current serial port
     \param Char : char to send on the port
     \return 1 success
     \return -1 error while writting data
 */
int SerialLinux::writeChar(char Char)
{
   if (::write(filedescriptor, &Char, 1) != 1)
   {
        return -1;
   }
    return 1;
}

/*!  \brief Read a string from the serial device
     \param string : string read on the serial device
     \param finalChar : final char of the string
     \param maxChars : maximum allowed number of chars read
     \return >0 success, return the number of chars read
     \return -1 error while reading the char
     \return -2 maxChars is reached
 */
int SerialLinux::readString(char * string, char finalChar, unsigned int maxChars)
{
	unsigned int nbChars = 0;
	int ret;
	while (nbChars < maxChars) 
	{
		ret = readChar (&string[nbChars]);
		if (ret == 1) 
		{
			if (string[nbChars] == finalChar) 
			{
				string [++nbChars] = '\0';
				return nbChars;
			}
			nbChars++;
		}
		if (ret < 0) 
		{
			return ret;
		}
	}
	return -2;
}

/*!  \brief Write a string on the current serial port
     \param string : string to send on the port (must be terminated by '\0')
     \return 1 success
     \return -1 error while writting data
 */
int SerialLinux::writeString(const char * string)
{
	int length = strlen (string);
	if (::write(filedescriptor, string, length) != length)
	{
		return -1;
	}
	return 1;
}

/*!  \brief Write an array of data on the current serial port
     \param buffer : array of bytes to send on the port
     \param nbBytes : number of bytes to send
     \return 1 success
     \return -1 error while writting data
 */
int SerialLinux::write(const void * buffer, unsigned int nbBytes)
{
	if (::write(filedescriptor, buffer, nbBytes) != (ssize_t) nbBytes)
	{
		return -1;
	}
	return 1;
}

/*!  \brief Read an array of bytes from the serial device
     \param buffer : array of bytes read from the serial device
     \param maxBytes : maximum allowed number of bytes to read
     \return 1 success, return the number of bytes read
     \return -1 error while reading the bytes
 */
int SerialLinux::read(void *buffer, unsigned int maxBytes)
{
	unsigned int nbBytesRead = 0;
	while (nbBytesRead < maxBytes) 
	{
		auto ptr = static_cast<unsigned char *>(buffer) + nbBytesRead;
		auto ret = ::read(filedescriptor,static_cast<void *>(ptr), maxBytes - nbBytesRead);
		if (ret == -1) 
		{
			return -1;
		}
		if (ret > 0)
		{   
			nbBytesRead += ret;
		}
	}
	return 1;
}

/*! \brief Empty send and receive buffers
 */
void SerialLinux::flush()
{
	tcflush(filedescriptor, TCIOFLUSH);
}

/*! \brief  Return the number of bytes in the receive buffer
    \return The number of bytes in the receive buffer
 */
int SerialLinux::peek()
{
	auto nbBytes = 0;
	ioctl(filedescriptor, FIONREAD, &nbBytes);
	return nbBytes;
}

/// @endcond
