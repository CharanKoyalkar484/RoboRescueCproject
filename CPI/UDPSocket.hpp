// Author@ Rene Keijzer
// class@ UDPSocket
// This class is used to make a connection with the client and to send and receive data.

#ifndef __UDPSOCKET__
#define __UDPSOCKET__
#include "Socket.hpp"
#include "Connection.hpp"
#include "UDPServer.hpp"
#include "..\..\mavlink_commands\mavlink_commands\mavlink.h"

class UDPSocket : public Socket
{
public:

	// Constructor to make a socket
	// Param@ Connection this is the connection you want to bind to the socket
	// Param@ UDPServer This is the server where you want to talk with
	UDPSocket(Connection c, UDPServer * serv) : con(c), server(serv){}

	// This function sends a messege
	//Param: message this is the message that you are sending
	void send(mavlink_message_t * message) override;

	// This Function recieves a message
	// Param@ message this is the mssage that you are recieving
	void receive(mavlink_message_t * message) override;

	// This function returns the connection id
	// Return@ The id of the connection
	uint8_t getId() override { return con.id; }

	// Standard destructor
	~UDPSocket(){}
private:
	friend class UDPServer;
	UDPServer * server;
	Connection con;
	std::vector<mavlink_message_t> responses;
};
#endif