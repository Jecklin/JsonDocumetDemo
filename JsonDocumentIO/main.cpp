#include <QCoreApplication>
#include "CJsonIO.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    CJsonIO json;
    QString dir = "./";
    QString fileName = "read.json";
    json.ReadJson(dir, fileName);
    json.Test();
    
    QString writeFile = "write.json";
    json.WriteJson(dir, writeFile);
    
    
    return a.exec();
}
