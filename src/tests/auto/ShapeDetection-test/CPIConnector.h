#ifndef CPICONNECTOR_H_
#define CPICONNECTOR_H_


#include <cstdint>
#include <queue>
#include <iostream>

#include "BaseLidar.h"
#include "../../../../deps/incl/mavlink/udp_mavlink_commands/mavlink.h"

class CPIConnector : public BaseLidar
{
public:
	CPIConnector();
	void sendCommand(uint64_t payload, COMMAND_DESTINATION dest, LIDAR_COMMAND_FUNCTIONS lcf);
	void onMessage(mavlink_message_t & function) override;
};

#endif //CPICONNECTOR_H_
