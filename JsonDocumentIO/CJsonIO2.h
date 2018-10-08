#ifndef CJSONIO2_H
#define CJSONIO2_H
#include <QVector>
////// *****************   visition 2: save : vector<double>      ***************///
//read2.json
//[
//    1.2 ,
//    2.5 ,
//    3.5
//]


class CJsonIO2
{
public:
    static CJsonIO2* GetInstance();

    bool    ReadJson(const QString& dir, const QString& fileName);
    bool    WriteJson(const QString& dir, const QString& fileName);
    void    PrintCurJson();
    
private:
    CJsonIO2();
    ~CJsonIO2();
    
    void    Init();
    
private:
    static CJsonIO2  m_jsonIO;
    QVector<double>  m_vector;
    
};

#endif // CJSONIO2_H
