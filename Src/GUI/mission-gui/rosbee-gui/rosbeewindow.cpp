#include "ui_rosbeewindow.h"
#include "rosbeewindow.h"

#include <QtWidgets/QMessageBox>

RosbeeWindow::RosbeeWindow(Rosbee &rosbee, QWidget *parent) :
   QMainWindow(parent),
   rosbee(rosbee),
   ui(new Ui::RosbeeWindow)
{
   ui->setupUi(this);

   connect(ui->startButton, SIGNAL(clicked()), this, SLOT(handleButton()));
   connect(ui->abortButton, SIGNAL(clicked()), this, SLOT(handleButton()));
   connect(ui->stopButton , SIGNAL(clicked()), this, SLOT(handleButton()));
   connect(&   timer      , SIGNAL(timeout()), this, SLOT(timerTick()));

   timer.start(1000);
}

RosbeeWindow::~RosbeeWindow(){
   delete ui;
}

void RosbeeWindow::handleButton(){
   QPushButton * button = static_cast<QPushButton *>(sender());
   if(button == nullptr) return;

   if(button == ui->startButton){
      if(!ui->startButton->isEnabled()) return;

      rosbee.startMission();
      SetMissionRunning(true);
   } else if(button == ui->abortButton){
      if(!ui->abortButton->isEnabled()) return;

      rosbee.abortMission();
      SetMissionRunning(false);
      ui->startButton->setEnabled(false);
   } else if(button == ui->stopButton){
      if(!ui->stopButton->isEnabled()) return;

      rosbee.stopMission();
      SetMissionRunning(false);
   }
}

void RosbeeWindow::SetMissionRunning(bool is_mission_running){
   ui->startButton->setEnabled(!is_mission_running);
   ui->abortButton->setEnabled( is_mission_running);
   ui->stopButton ->setEnabled( is_mission_running);
}

void RosbeeWindow::timerTick(){
   if(rosbee.isReady()){
      ui->statusLabel->setText(tr("Ready"));
   }else{
      ui->statusLabel->setText(tr("Not ready"));
   }
}
