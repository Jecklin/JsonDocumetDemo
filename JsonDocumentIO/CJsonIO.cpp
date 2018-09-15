#include "CJsonIO.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QDebug>

CJsonIO::CJsonIO()
{
    
}

CJsonIO::~CJsonIO()
{
    
}

bool CJsonIO::ReadJson(const QString &dir, const QString &fileName)
{
    bool result = false;
    do
    {
        QString file = dir + fileName;
        qDebug() << file;
        
        QFile loadFile(file);
        if (!loadFile.open(QIODevice::ReadOnly))
        {
            qDebug() << "could't open projects json";
            break;
        }
              
        QByteArray allData = loadFile.readAll();
        loadFile.close();
        
        QJsonParseError jsonError;
        QJsonDocument   document    = QJsonDocument::fromJson(allData, &jsonError); //函数说明：解析UTF-8编码的JSON文档并从中创建QJsonDocument。
        QStringList     keys        = document.object().keys();
        QHash<QString, QString> indexHash;
        
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
        
        if (!document.isObject())
        {
            qDebug() << "document is not object";
            break;
        }
        
        QJsonObject object      = document.object();
        int         keySize     = keys.size();
        
        for (int i = 0; i < keySize; ++i)
        {
            QString strKey = keys.at(i); 
            if (object.contains(strKey))
            {
                QJsonValue value = object.value(strKey);
                if (value.isString())
                {
                    QString strValue = value.toString();
                    indexHash.insert(strKey, strValue);  
                }
            }
        }

        this->m_hash = indexHash;
        result = true;
   
    }while(false);
    
    return result;
}

bool CJsonIO::WriteJson(const QString &dir, const QString &fileName)
{
    bool result = false;
    do
    {
        //set QJsonObject
        QJsonObject object;
        QHash<QString, QString>::iterator iter;
        for (iter = m_hash.begin(); iter != m_hash.end(); ++iter)
        {
            object.insert(iter.key(), iter.value());
        }
        
        //write document
        QString strFile = dir + fileName;
        QFile loadFile(strFile);
        if (!loadFile.open(QIODevice::WriteOnly))
        {
            qDebug() << "could't open projects json";
            break;
        }

        QJsonDocument doc(object);
        QByteArray byteArray = doc.toJson();
        loadFile.write(byteArray);

        loadFile.close();
        
        result = true;
   
    }while(false);
    
    return result;
}

void CJsonIO::Test()
{
    QHash<QString,QString>::const_iterator iter = this->m_hash.constBegin();
    while (iter != this->m_hash.constEnd())
    {
        QString     key       = iter.key();
        QString     value     = iter.value();
        
        qDebug() << "key:" << key << ": " << "value: " << value;
        
        ++iter;
    }   
}
