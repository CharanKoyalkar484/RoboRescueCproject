/**
*               __
*    _________ / /_  ____  ________  ____________  _____
*   /___/ __ \/ __ \/ __ \/ ___/ _ \/ ___/ ___/ / / / _ \
*  / / / /_/ / /_/ / /_/ / /  /  __(__  ) /__/ /_/ /  __/
* /_/  \____/_.___/\____/_/   \___/____/\___/\__,_/\___/
*
*
* @file Map.cpp
* @date Created: 22-04-2015
* @version 1.0
*
* @author Danny Horvath, Thomas Fink
*
* @section LICENSE
* License: newBSD
*
* Copyright © 2015, HU University of Applied Sciences Utrecht.
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

#include "map.h"

Map::Map(std::string fileName, int height, int width):
    fileName(fileName),
    height(height),
    width(width)
{
    if(!fileName.empty()){
        createNewMap(fileName);
        loadMap(fileName);
    }
}

Map::Map(std::string fileName):
    fileName(fileName){
    loadMap(fileName);
}

Map::Map(std::string fileName, Pointcloud *pcl):
fileName(fileName){
    height = pcl->getCloudHeight()+1;
    width = pcl->getCloudWidth()+1;
    std::vector<Pointcloud::Point> *points = pcl->getPoints();
    if(points->size() == 0){
        throw Values::CONTENTEXCEPTION;
    }
    int minX = 0;
    int minY = 0;

    for(Pointcloud::Point & point : *points){
        if(point.X < minX){
            minX = point.X;
        }

        if(point.Y < minY){
            minY = point.Y;
        }
    }
    if(minX < 0){
        minX = minX * -1;
    }
    if(minY < 0){
        minY = minY * -1;
    }
    for(Pointcloud::Point & point : *points){
        setMapObject(1,point.Y + minY,point.X + minX);
    }

}

Map::~Map(){
}

void Map::loadMap(std::string fileName){
    std::ifstream mapFile;
    mapFile.open(fileName);
    if(!mapFile.is_open()){
        throw Values::FILEEXCEPTION;
    }
    std::string line;
    std::string item;
    int result;
    mapFile >> height >> width;
    while(std::getline(mapFile, line)){
        Map::Object object;
        std::stringstream ss(line);
        std::getline(ss, item, ':');
        std::stringstream convertX(item);
        if ( !(convertX >> result) )continue;
        object.X = result;

        std::getline(ss, item, ':');
        std::stringstream convertY(item);
        if ( !(convertY >> result) )result = 0;
        object.Y = result;

        std::getline(ss, item, ':');
        std::stringstream convertId(item);
        if ( !(convertId >> result) )result = 0;
        object.id = result;
        setMapObject(object);
    }
    mapFile.close();
}

void Map::setMapObject(int object,int y, int x){
    if(x < 0 || y < 0){
        return;
    }
    if(x < width && y < height){
        if(object == 0){
            removePoint(x, y);
        }
        else if(object >= 0){
            Object obj;
            obj.X = x;
            obj.Y = y;
            obj.id = object;
            mapLayout.push_back(obj);
        }
    }
}

void Map::setMapObject(Map::Object obj){
    if(obj.X < 0 || obj.Y < 0){
        return;
    }
    if(obj.X < width && obj.Y < height){
        if(obj.id == 0){
            removePoint(obj);
        }
        else if(obj.id >= 0){
            mapLayout.push_back(obj);
        }
    }
}

int Map::getMapObject(int y, int x){
    if(x < 0 || y < 0){
        return -1;
    }
    if(x < width && y < height){
        for (int i = mapLayout.size() - 1; i >= 0; --i){
            if (mapLayout[i].X == x && mapLayout[i].Y == y){
                return mapLayout[i].id;
            }
        }
        return 0;
    }
    return -1;
}

std::vector< Map::Object > Map::getMapContent(){
    return mapLayout;
}

void Map::saveMap(std::string filename){
    std::sort( mapLayout.begin(), mapLayout.end() );
    mapLayout.erase( std::unique( mapLayout.begin(), mapLayout.end() ), mapLayout.end() );
    std::ofstream mapFile;
    mapFile.open(filename);
    mapFile << height << ' ' << width << "\n";
    for(Map::Object & obj : mapLayout){
        mapFile << obj.X << ':' << obj.Y << ':' << obj.id << '\n';
    }
    mapFile.close();
}

void Map::savePcl(std::string filename){

    Pointcloud pC;

    for(Map::Object & obj : mapLayout){
        pC.setPoint(obj.X, obj.Y);
    }
    pC.savePointsToFile(filename + ".pcl");
}

void Map::createNewMap(std::string fileName){
    std::ofstream mapFile;
    mapFile.open(fileName);
    mapFile << height << ' ' << width << '\n';
    mapFile.close();
}

void Map::removePoint(int x, int y){
    std::sort( mapLayout.begin(), mapLayout.end() );
    mapLayout.erase( std::unique( mapLayout.begin(), mapLayout.end() ), mapLayout.end() );
    int i = 0;
    for (Map::Object & o : mapLayout){
        if (o.X == x && o.Y == y){
            mapLayout.erase(mapLayout.begin() + i);
            break;
        }
        ++i;
    }
}

void Map::removePoint(Map::Object obj){
    std::sort( mapLayout.begin(), mapLayout.end() );
    mapLayout.erase( std::unique( mapLayout.begin(), mapLayout.end() ), mapLayout.end() );
    int i = 0;
    for (Map::Object & o : mapLayout){
        if (o.X == obj.X && o.Y == obj.Y){
            mapLayout.erase(mapLayout.begin() + i);
            break;
        }
        ++i;
    }
}
