#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "Rosbee.h"
#include "Lidar.h"
#include "Quadcopter.h"
#include "ATV.h"
#include "MAVLinkExchanger.h"
#include "SerialPort.h"
#include "StrategyController.h"
#include "virtualRosbee.h"
#include "VirtualATV.h"
#include "VirtualQuadCopter.h"
#include "UDPServer.h"
//#include "databaseconnector.h"
#include <iostream>

int main(int argc, char *argv[])
{
    RobotManager robotmanager;
    SerialPort p{ "" };
    UDPServer server(robotmanager);
    MAVLinkExchanger exch{ p };
    Quadcopter q{ exch };
    ATV a{ exch };
    while(robotmanager.getRobots<Rosbee>().size()==0){}
    Rosbee* rosbee =robotmanager.getRobot<Rosbee>(0);

    //while(robotmanager.getRobots<Quadcopter>().size()==0){}
    //Quadcopter* actualQuad =robotmanager.getRobot<Quadcopter>(1);

    while(robotmanager.getRobots<Lidar>().size()==0){}
    Lidar* actualLidar =robotmanager.getRobot<Lidar>(1);

    VirtualQuadCopter copter(Dimension(1,1),Dimension(3,3),1,1);
    virtualRosbee bee(1,1,rosbee);
    VirtualATV atv(Dimension(1,1),1,1);
    virtualLidar lidar(actualLidar);
    Map map;
    
    
    QApplication app(argc, argv);
    MainWindow w{server, q, a};
    w.show();
    //databaseConnector dbc("127.0.0.1","root","desktop","robodata");
  //  std::cout << dbc.getMaps().at(0).name;
	app.exec();

	std::cout << "Nu strategy";
	getchar();
	StrategyController controller(map, copter, bee, lidar);
	controller.scanArea();
	std::cout << "Scan Area Done";
	getchar();
	controller.searchArea();
	controller.movePairwise();
	return 1;
}