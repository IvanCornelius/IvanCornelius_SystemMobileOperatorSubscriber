#ifndef INDIVIDUALMOBSUB_H
#define INDIVIDUALMOBSUB_H


//заголовочные файлы
#include <fstream>
#include "MobileSub.h"


//класс для работы с физическим лицом
class IndividualMobSub : public MobileSub
{
//приватные методы
private:
    //ФИО
    QString FullName = "не указано";
    //паспортные данные
    QString PassportData ="не указано";
    //баланс счета
    double Balance = 0;
//публичные методы
public:
    //создание нового объекта класса (способ 1)
    IndividualMobSub();
    //создание нового объекта класса (способ 2)
    IndividualMobSub(unsigned long long, double, double, QString, QString, double, QString *TextError = 0);
    //указать ФИО
    void setFullName(QString);
    //указать паспортные данные
    void setPassportData(QString);
    //указать баланс счета
    void setBalance(double);
    //получить ФИО
    QString getFullName();
    //получить паспортные данные
    QString getPassportData();
    //получить баланс счета
    double getBalance();
    //указать специфический параметр
    void setSpecParam(int com, QString value);
    //получить специфический параметр
    QString getSpecParam(int com);
    //ввод информации (способ 1)
    bool inp(unsigned long long, double, double, QString, QString, double, QString *TextError = 0);
    //ввод информации (способ 2)
    bool inp(QString, QString, double);
    //ввод информации (способ 3)
    bool inp(QTextStream *file, QString *TextError = 0);
    //вывод информации (способ 1)
    virtual QString getTextOut();
    //вывод информации (способ 2)
    bool out(QTextStream *file);
};


#endif // IndividualMobSub_H
