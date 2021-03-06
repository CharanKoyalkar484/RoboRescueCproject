/**
*               __
*    _________ / /_  ____  ________  ____________  _____
*   /___/ __ \/ __ \/ __ \/ ___/ _ \/ ___/ ___/ / / / _ \
*  / / / /_/ / /_/ / /_/ / /  /  __(__  ) /__/ /_/ /  __/
* /_/  \____/_.___/\____/_/   \___/____/\___/\__,_/\___/
*
*
* @file XYLocalisationModule.cpp
* @date Created: 29-5-2015
*
* @author Kjeld Perquin
*
* @section LICENSE
* License: newBSD
*
* Copyright � 2015, HU University of Applied Sciences Utrecht.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
* - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
* GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#include "XYLocalisationModule.h"
#include <iostream>

XYLocalisationModule::XYLocalisationModule(io_service& service, std::string host, std::string port):
TCPClient{ service, host, port}
{	
}

Coordinate<double> XYLocalisationModule::getCoordinate() const
{
	return coordinate;
}

double XYLocalisationModule::getX() const
{
	return coordinate.getX();
}

double XYLocalisationModule::getY() const
{
	return coordinate.getY();
}

void XYLocalisationModule::handleMessage(std::string message)
{
	int xPos;
	if ((xPos = message.find('X')) != std::string::npos)
	{
		int yPos;
		if ((yPos = message.find('Y')) != std::string::npos)
		{
			if (yPos > xPos)
			{
				std::string xString;
				std::string yString;
				xString = message.substr(xPos + 1, yPos - xPos);
				yString = message.substr(yPos + 1, message.length() - yPos);
				try
				{
					double newX = stod(xString);
					double newY = stod(yString);
					coordinate.setX(newX);
					coordinate.setY(newY);
					//std::cout << "Coordinate: \nX: " << getX() << std::endl;
					//std::cout << "Y: " << getY() << std::endl;

				}
				catch (std::invalid_argument&)
				{
				}
			}
		}
	}
}