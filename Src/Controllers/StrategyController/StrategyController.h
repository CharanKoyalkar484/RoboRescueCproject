#ifndef _STRATEGY_CONTROLLER_H
#define _STRATEGY_CONTROLLER_H
#include "Map.hpp"
#include <thread>



#include "VSLAM.h"
#include "areacoveringalgorithm.h"
#include "mapLogicVSLAM.h"
class StrategyController
{
public:
	std::thread* Thread;
	virtualLidar virtuallidar;
	virtualRosbee virtualrosbee;
	Map* map;
        void run();
	StrategyController(Map *map, VirtualQuadCopter copter, virtualRosbee rosbee, virtualLidar virtuallidar);
	~StrategyController();
	void scanArea();
	void searchArea();
	void movePairwise();

	VirtualQuadCopter copter;
};
#endif

