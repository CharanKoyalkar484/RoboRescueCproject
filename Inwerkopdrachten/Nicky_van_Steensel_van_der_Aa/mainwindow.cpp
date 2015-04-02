#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loader.h"
#include "QFileDialog"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"),"",tr("Files(*.*)"));
    Loader loader;
loader.getMap(fileName);


}
