#include "map.h"

Map::Map(QString fileName, int width, int height):
    fileName{fileName}
{
    if(fileName!= "NEW FILE"){
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
        }
        QTextStream stream(&file);
        file.seek(0);
        QString line = stream.readLine();
        while(!line.isNull()){
            map.push_back(line);
            line = stream.readLine();
        }
        file.close();
        mapWidth = map[1].length();
        mapHeiht = map.size();

    }
    else{
        mapWidth = width;
        mapHeiht = height;
        for(int x = 0; x < width; x++){
            QString line;
            for(int i = 0; i < height; i++){
                line.append("X");
            }
            map.push_back(line);
        }
    }
}
void Map::setObject(QChar object,int x, int y){
    if(x < mapWidth && y < mapHeiht){
        map[y][x] = object;
    }
}
QVector<QString> Map::getMap(){
    return map;
}

Map::~Map()
{
    qDebug() << "deleted";
}

int Map::getWidth(){
    return mapWidth;
}
int Map::getHeight(){
    return mapHeiht;
}
QString Map::getFileName(){
    return fileName;
}

int Map::checkMap(){
    int width = map[0].length();
    for(QString string : map){
        if (string.length() != width){
            return -2;
        }
        for(int i = 0; i<string.length(); i++){
            if((string[i]<'0' || string[i]>'9') && string[i]!='X'){
                return -1;
            }
        }
    }
    return 1;
}
void Map::save(){
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    for(QString line : map){
        file.write(line.toStdString().c_str());
        file.write("\n");
    }
    file.close();
}
void Map::saveAs(QString newFileName){
    fileName = newFileName;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    for(QString line : map){
        file.write(line.toStdString().c_str());
        file.write("\n");
    }
    file.close();
}
