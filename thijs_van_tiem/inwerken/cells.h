#ifndef CELLS_H
#define CELLS_H

#include <QTableWidgetItem>
enum class terreinTypen { //selecteer het typen wat je ter plekken nodig hebt
    water,
    concrete,
    green,
    none
};

class cells
{
public:


    terreinTypen omgeving;

    bool quadPresent;
    bool atvPresent;
    bool rosbeePresent;

    //cell moet zichzelf kunnen formateren naar een qwidgettable
    // een cell klasse is pure logica en op deze manier wordt het grafisch weergeven
    QTableWidgetItem * formatCell();

    void changeTerrein(terreinTypen typen);
    void toggleQuad();
    void toggleAtv();
    void toggleRosbee();

    cells();
    ~cells();
};

#endif // CELLS_H

