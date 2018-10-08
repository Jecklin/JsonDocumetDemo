#ifndef CJSONIO_H
#define CJSONIO_H

#include <QHash>

////// *****************   visition 1: save : QHash<QString, QString>      ***************///
//read.json
//{
//    "1":"确定",
//    "2":"取消"
//}

class CJsonIO
{
public:
    static CJsonIO* GetInstance();
    
    bool        ReadJson(const QString& dir, const QString& fileName);
    bool        WriteJson(const QString& dir, const QString& fileName);
    void        PrintCurJson();
    QString     GetValue(QString key);
    
private:
    CJsonIO();
    ~CJsonIO();
    
    void    Init();
    
private:
    static  CJsonIO         m_jsonIO;
    QHash<QString, QString> m_hash;          //存储当前json
    QHash<QString, QString> m_defaultHash;   //存储默认json
};



#endif // CJSONIO_H
