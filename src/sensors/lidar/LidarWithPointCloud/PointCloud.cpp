/**
*               __
*    _________ / /_  ____  ________  ____________  _____
*   /___/ __ \/ __ \/ __ \/ ___/ _ \/ ___/ ___/ / / / _ \
*  / / / /_/ / /_/ / /_/ / /  /  __(__  ) /__/ /_/ /  __/
* /_/  \____/_.___/\____/_/   \___/____/\___/\__,_/\___/
*
*
* @file PointCloud.cpp
* @date Created: 29-04-2015
*
* @author Tijmen Bruggeman
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
#include "PointCloud.h"

void Pointcloud::setPoint(Point point){
	removePoint(point.X, point.Y);
	pointCloud.push_back(point);
}
void Pointcloud::setPoint(int x, int y){
	removePoint(x, y);
    Point * point = new Point;
    point->X = x;
    point->Y = y;
	pointCloud.push_back(*point);
}
std::vector<Pointcloud::Point> Pointcloud::getPoints(){
	return pointCloud;
}
void Pointcloud::removePoint(int x, int y){
	int i = 0;
	for (Point p : pointCloud){
		if (p.X == x && p.Y == y){
			pointCloud.erase(pointCloud.begin()+i);
			break;
		}
		i++;
	}
}
void Pointcloud::removePoint(Point point){
	int i = 0;
	for (Point p : pointCloud){
		if (p.X == point.X && p.Y == point.Y){
			pointCloud.erase(pointCloud.begin() + i);
			break;
		}
		i++;
	}
}
Pointcloud::Pointcloud(){}

int Pointcloud::getCloudHeight(){
	int maxHeight = 0;
	int minHeight = 0;
	for (Point p : pointCloud){
		if (p.Y < minHeight){
			minHeight = p.Y;
		}
		if (p.Y > maxHeight){
			maxHeight = p.Y;
		}
	}
	return maxHeight - minHeight;
}
int Pointcloud::getCloudWidth(){
	int maxWidth = 0;
	int minWidth = 0;
	for (Point p : pointCloud){
		if (p.X > maxWidth){
			maxWidth = p.X;
		}
		if (p.X < maxWidth){
			minWidth = p.X;
		}
	}
	return maxWidth - minWidth;
}
void Pointcloud::setOrientation(int degrees){
	orientation = degrees;
}
int Pointcloud::getOrientation(){
	return orientation;
}
//OPERATORS
std::ostream & operator<<(std::ostream & output, const Pointcloud::Point & s){
	output << "(" << s.X << "," << s.Y << ")";
	return output;
}
Pointcloud Pointcloud::operator+(Pointcloud & b){
	Pointcloud pt;
	for (Pointcloud::Point p : b.getPoints()){
		pt.setPoint(p);
	}
	for (Pointcloud::Point p : pointCloud){
		pt.removePoint(p);
		pt.setPoint(p);
	}
	pt.setOrientation(orientation);
	return pt;
}
Pointcloud Pointcloud::operator+=(Pointcloud & b){
	for (Pointcloud::Point p : b.getPoints()){
		setPoint(p);
	}
	return *this;
}
