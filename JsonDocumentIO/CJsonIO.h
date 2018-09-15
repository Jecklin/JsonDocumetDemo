#ifndef CJSONIO_H
#define CJSONIO_H

#include <QHash>

////// *****************   visition 1: save : QHash<QString, QString>      ***************///
////// *****************  json :                                           ***************///
//Chinese.json
//{
//    "1": "确定",
//    "2":"取消"
//}
//English".json
//{
//    "1": "确定",
//    "2":"取消"
//}	

class CJsonIO
{
public:
    CJsonIO();
    ~CJsonIO();
    bool    ReadJson(const QString& dir, const QString& fileName);
    bool    WriteJson(const QString& dir, const QString& fileName);
    
    void    Test();
private:
    QHash<QString, QString> m_hash;   
    
};



#endif // CJSONIO_H
