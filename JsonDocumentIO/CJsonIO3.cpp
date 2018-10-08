#include "CJsonIO3.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QDebug>

CJsonIO3 CJsonIO3::m_jsonIO;

CJsonIO3::CJsonIO3()
    :m_hash()
    ,m_defaultHash()
{
    this->Init();
}

CJsonIO3::~CJsonIO3()
{
    
}

CJsonIO3 *CJsonIO3::GetInstance()
{
    return &m_jsonIO;
}

bool CJsonIO3::ReadJson(const QString &dir, const QString &fileName)
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
        
        if (!document.isObject())
        {
            qDebug() << "document is not object";
            break;
        }
        
        //read QJson
        QHash<QString, QStringList> indexHash;
        QStringList                 indexList;
        
        QStringList     keys        = document.object().keys();
        QJsonObject     object      = document.object();
        int             keySize     = keys.size();
        
        for (int i = 0; i < keySize; ++i)
        {
            QString strKey = keys.at(i);
            indexList.clear();
            
            if (object.contains(strKey))
            {
                QJsonValue value = object.value(strKey);
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int arrSize = array.size();
                    for (int i = 0; i < arrSize; ++i)
                    {
                        QJsonValue  arrValue = array.at(i);
                        if (arrValue.isString())
                        {
                            QString  strValue = arrValue.toString();
                            indexList.push_back(strValue);
                        }
                        
                    }
                    
                }
                
                indexHash.insert(strKey, indexList);
            }
            
            
        }

        this->m_hash        = indexHash;
        this->m_defaultHash = indexHash;
        result              = true;
   
    }while(false);
    
    return result;
}

bool CJsonIO3::WriteJson(const QString &dir, const QString &fileName)
{
    bool result = false;
    do
    {
        //set QJson
        QJsonObject jsonObject;
        QHash<QString,QStringList>::const_iterator iter = this->m_hash.constBegin();
        while (iter != this->m_hash.constEnd())
        {
            QJsonArray  jsonArray;
            QString     key       = iter.key();
            QStringList valueList = iter.value();
            
            QStringList::const_iterator listIter = valueList.begin();
            while (listIter != valueList.end())
            {
                jsonArray.append(*listIter);
                ++listIter;
            }
            
            jsonObject.insert(key, QJsonValue(jsonArray)); 
            ++iter;
        }
        
        //set QJsonDocument
        QJsonDocument doc(jsonObject);
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

void CJsonIO3::PrintCurJson()
{
    QHash<QString,QStringList>::const_iterator iter = this->m_hash.constBegin();
    while (iter != this->m_hash.constEnd())
    {
        
        QString     key       = iter.key();
        QStringList valueList = iter.value();
        
        qDebug() << "key:" << key << ": ";
        
        QStringList::const_iterator listIter = valueList.begin();
        while (listIter != valueList.end())
        {
            qDebug() << "value:" << *listIter;
            ++listIter;
        }
          
        ++iter;
    }
}

QStringList CJsonIO3::GetValue(QString key)
{
    QStringList valueList;

    QHash<QString, QStringList>::const_iterator iter = this->m_hash.constBegin();
    while (iter != this->m_hash.constEnd())
    {
        QString hashKey = iter.key();
        if (hashKey == key)
        {
            valueList = iter.value();
        }

        ++iter;
    }
    
    return valueList;
}

void CJsonIO3::Init()
{
    this->ReadJson("./", "read3.json");
}
