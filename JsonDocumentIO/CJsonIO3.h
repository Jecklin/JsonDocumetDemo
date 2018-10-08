#ifndef CJSONIO3_H
#define CJSONIO3_H
#include <QHash>

////// *****************   visition 1: save : QHash<QString, QString>      ***************///
//read3.json
//{
// "case1":
//    [
//        "one",
//        "two"
//    ],
// "case2":
//    [
//        "three",
//        "four"
//    ]
//}


class CJsonIO3
{
public:
    static CJsonIO3* GetInstance();
    
    bool            ReadJson(const QString& dir, const QString& fileName);
    bool            WriteJson(const QString& dir, const QString& fileName);
    void            PrintCurJson();
    QStringList     GetValue(QString key);
    
private:
    CJsonIO3();
    ~CJsonIO3();
    
    void    Init();
    
private:
    static  CJsonIO3            m_jsonIO;
    QHash<QString, QStringList> m_hash;          //存储当前json
    QHash<QString, QStringList> m_defaultHash;   //存储默认json
    
};



#endif // CJSONIO3_H
