#include <QCoreApplication>
#include "CJsonIO.h"
#include "CJsonIO2.h"
#include "CJsonIO3.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    //json1
    CJsonIO *json1      = CJsonIO::GetInstance();
    QString  dir        = "./";
    QString  readName   = "read.json";
    QString  writeFile  = "write.json";
    
    json1->ReadJson(dir, readName);
    json1->WriteJson(dir, writeFile);
    
    json1->PrintCurJson();
    qDebug() << json1->GetValue("1");
    
    //json2
    CJsonIO2 *json2      = CJsonIO2::GetInstance();
    QString  dir2        = "./";
    QString  readName2   = "read2.json";
    QString  writeFile2  = "write2.json";
    
    json2->ReadJson(dir2, readName2);
    json2->WriteJson(dir2, writeFile2);    
    json2->PrintCurJson();
    
    //json3
    CJsonIO3 *json3      = CJsonIO3::GetInstance();
    QString  dir3        = "./";
    QString  readName3   = "read3.json";
    QString  writeFile3  = "write3.json";
    
    json3->ReadJson(dir3, readName3);
    json3->WriteJson(dir3, writeFile3);    
    json3->PrintCurJson();

    
    return a.exec();
}
