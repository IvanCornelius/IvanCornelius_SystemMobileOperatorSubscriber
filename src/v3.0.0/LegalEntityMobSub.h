#ifndef LegalEntityMobSub_H
#define LegalEntityMobSub_H


//заголовочные файлы
#include <fstream>
#include "MobileSub.h"


//класс для юридического лица
class LegalEntityMobSub : public MobileSub
{
//приватные методы
private:
    //ИНН
    unsigned long long INN = 0;
    //название
    QString Name = "не указано";
    //адрес
    QString Address = "не указано";
//публичные методы
public:
    //создание нового объекта класса (способ 1)
    LegalEntityMobSub();
    //создание нового объекта класса (способ 2)
    LegalEntityMobSub(unsigned long long, double, double, unsigned long long, QString, QString, QString *TextError);
    //указать ИНН
    bool setINN(unsigned long long);
    //указать название
    void setName(QString);
    //указать адрес
    void setAddress(QString);
    //получить ИНН
    unsigned long long getINN();
    //получить название
    QString getName();
    //получить адрес
    QString getAddress();
    //указать специфический параметр
    void setSpecParam(int com, QString value);
    //получить специфический параметр
    QString getSpecParam(int com);
    //ввод информации (способ 1)
    bool inp(unsigned long long, double, double, unsigned long long, QString, QString, QString *TextError);
    //ввод информации (способ 2)
    bool inp(unsigned long long, QString, QString, QString *TextError);
    //ввод информации (способ 3)
    bool inp(QTextStream *file, QString *TextError = 0);
    //вывод информации (способ 1)
    virtual QString getTextOut();
    //вывод информации (способ 2)
    bool out(QTextStream *file);
};

#endif // LegalEntityMobSub_H
