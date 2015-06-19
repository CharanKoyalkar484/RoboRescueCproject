/**
 * @file scanArea.h
 * @author Coen Andriessen
 * @version 1.3
 */

#ifndef SCANAREA_H
#define SCANAREA_H

#include <iostream>
#include <map.hpp>
#include <Rosbee.h>
#include <MapSearchNode.h>
#include <Route.h>
#include <mapLogicVSLAM.h>


class scanArea
{
public:
    // Constructor of scanArea.
    scanArea(map *Map, Rosbee *rosbee, MapSearchNode *mapSearchNode, Route *route, mapLogicVSLAM *MapLogicVSLAM);
    // Destructor of scanArea.
    ~scanArea();
    // Function to start the scan algorithm.
    void run();
private:
    map *Map;
    Rosbee *rosbee;
    MapSearchNode *mapSearchNode;
	mapLogicVSLAM *MapLogicVSLAM;
    Route * route;

};

#endif // SCANAREA_H