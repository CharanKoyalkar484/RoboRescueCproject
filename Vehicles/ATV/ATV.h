/**
*                __
*    _________  / /_  ____  ________  ____________  _____
*   / ___/ __ \/ __ \/ __ \/ ___/ _ \/ ___/ ___/ / / / _ \
*  / /  / /_/ / /_/ / /_/ / /  /  __(__  ) /__/ /_/ /  __/
* /_/   \____/_.___/\____/_/   \___/____/\___/\__,_/\___/
*
*
* @file 			ATV.h
* @date Created:	2015-04-08
*
*  @author	Hylco Uding	
*  @author	Yorrick Lans
*  @author	Bart Muelders
*
*  @section LICENSE
*  License:	newBSD
*
*  Copyright © 2015, HU University of Applied Sciences Utrecht.
* 		All rights reserved.
*
*
*
*	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
*	- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
*	- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
*	- Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
*
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
*   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*   ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
*   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
*   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
*   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
*   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
#ifndef _ATV_H
#define _ATV_H

#include "../Dependencies/MAVLink/ardupilotmega/mavlink.h"
#include "MAVLinkCommunicator.h"
#include "PriorityMessage.h"

class ATV
{
public:
	/**
	*The Constructor for the ATV
	*@param MAVLinkCommunicator is the mavlinkCommunicator
	*/
	ATV(MAVLinkCommunicator & mavlinkCommunicator);
	
	/**
	*The default deconstructor
	*/
	~ATV();
	
	/**
	*Method to move the ATV forwards
	*@param value adjustment of PWM(PWM can't directly be converted to speed unis)
	*/
	void moveForward(int value);
	
	/**
	*Method to move the ATV backwards
	*@param value adjustment of PWM(PWM can't directly be converted to speed unis)
	*/
	void moveBackward(int value );
	
	/**
	* The steer method for the ATV.
	* The steer method is being called for turning the front wheels to a certain degree.
	* For a fast and reliable turn left give -400 as parameter and for a turn right give 400 as parameter.
	* Giving less then -400 or more then 400 will result in making the front wheels turn at its maximum.
	* @param value: the value of which the rc channel should be overwritten with.
	*/
	void steer(int value);
	
	/**
	* The reset method for the ATV
	* Calling this method will make the ATV to reset
	*/
	void reset();
	
	/**
	* The returnControlToRc method for the ATV
	* This method send a message to mavlinkCommunicator for returning the control to the Radio Controller
	*/
	void returnControlToRc();
	
	/**
	* This is the main loop for a ATV
	* This is made in a separate thread when the main program is started
	*/
	void loop();
	float getHeading();

	int getBatteryRemaining();

	float getGroundSpeed();

	int getSteeringDirection();

private:
	MAVLinkCommunicator & mavlinkCommunicator;
	PriorityMessage message;
	
	float groundSpeed = 0;
	float heading = 0;
	int steeringDirection = 0;
	//FlightMode flightMode;
	
	int batteryRemaining = 0;
	void handleIncomingMessage(PriorityMessage incomingMessage);
};

#endif

/*DEBUG
use this method to get the servo output, this used for steering
auto msg = mavlink_message_t();
int msgid;
while (1)
{
mavlinkSender.receiveMessage(msg);
msgid = (int)msg.msgid;
if (msgid == MAVLINK_MSG_ID_SERVO_OUTPUT_RAW)
{
std::cout << mavlink_msg_servo_output_raw_get_servo1_raw(&msg) << '\n';
}
}
*/
