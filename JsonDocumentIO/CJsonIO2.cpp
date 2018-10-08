#include "CJsonIO2.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QDebug>

CJsonIO2 CJsonIO2::m_jsonIO;

CJsonIO2::CJsonIO2()
    :m_vector()
{
    this->Init();
}

CJsonIO2::~CJsonIO2()
{
    
}

CJsonIO2 *CJsonIO2::GetInstance()
{
    return &m_jsonIO;
}

bool CJsonIO2::ReadJson(const QString &dir, const QString &fileName)
{
    bool result = false;
    do
    {
        //read document
        QString file = dir + fileName;
        QFile loadFile(file);
        if (!loadFile.open(QIODevice::ReadOnly))
        {
            qDebug() << "could't open projects json";
            break;
        }
              
        QByteArray allData = loadFile.readAll();
        loadFile.close();
        
        //set QJsonDocument
        QJsonParseError jsonError;
        QJsonDocument   document    = QJsonDocument::fromJson(allData, &jsonError); //函数说明：解析UTF-8编码的JSON文档并从中创建QJsonDocument。

        if (document.isNull() || (jsonError.error != QJsonParseError::NoError))
        {
            qDebug() << "document error";
            break;
        }
        if (jsonError.error == QJsonParseError::IllegalUTF8String)                  //输入中出现非法UTF8序列
        {
            qDebug() << "An illegal UTF8 sequence occurred in the input";
            break;
        }
        
        if (!document.isArray())
        {
            qDebug() << "document is not array";
            break;
        }
        
        //read QJsonArray
        QVector<double> indexVector;
        QJsonArray      array       = document.array();
        int             size        = array.size();

        indexVector.clear();
        for (int i = 0; i < size; ++i)
        {
            QJsonValue value = array.at(i);
            if (value.type() == QJsonValue::Double)
            {
                double indexValue = value.toDouble();
                indexVector.push_back(indexValue);
            }
        }

        this->m_vector = indexVector;
        result = true;
   
    }while(false);
    
    return result;
}

bool CJsonIO2::WriteJson(const QString &dir, const QString &fileName)
{
    bool result = false;
    do
    {
        //set QJsonArray
        QJsonArray json;
        QVector<double>::iterator iter;
        for (iter = m_vector.begin(); iter != m_vector.end(); ++iter)
        {
            json.append(*iter);
        }

        //set QJsonDocument
        QJsonDocument doc(json);
        QByteArray byteArray = doc.toJson();
        
        //write document
        QString strFile = dir + fileName;
        QFile loadFile(strFile);
        if (!loadFile.open(QIODevice::WriteOnly))
        {
            qDebug() << "could't open projects json";
            break;
        }
        
        loadFile.write(byteArray);
        loadFile.close();
        
        result = true;
   
    }while(false);
    
    return result;
}

void CJsonIO2::PrintCurJson()
{
    QVector<double>::const_iterator iter = this->m_vector.constBegin();
    while (iter != this->m_vector.constEnd())
    {
        qDebug() << "value:" << *iter;
        ++iter;
    }  
}

void CJsonIO2::Init()
{
    this->ReadJson("./", "read2.json");
}
