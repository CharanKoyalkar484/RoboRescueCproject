#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include "map.h"
#include "gridpart.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void openFile();
    void createFile();
    void saveFile();
    void closeFile();
    void addName();
    void editAction();
    void editCell(int row, int collom);
private:
    void openFile(std::string filename);
    void setDisplayingFile(bool value);

    Ui::MainWindow *ui;
    Map * map;
    bool isDisplayingFile;
    std::vector<GridPart*> gridContent;
    GridPart * currentHover;
};

#endif // MAINWINDOW_H
