#ifndef EMPLOYEEMOBSUB_H
#define EMPLOYEEMOBSUB_H

//заголовочные файлы
#include <fstream>
#include "MobileSub.h"


//класс для работы с собственными сотрудниками оператора связи
class EmployeeMobSub : public MobileSub
{
//публичные методы
private:
    //ФИО
    QString FullName = "не указано";
    //табельный номер
    unsigned long long ServiceNumber = 0;
//приватные методы
public:
    //создание нового объекта класса (способ 1)
    EmployeeMobSub();
    //создание нового объекта класса (способ 2)
    EmployeeMobSub(unsigned long long, double, double, QString, unsigned long long, QString *TextError = 0);
    //указать ФИО
    void setFullName(QString);
    //указать табельный номер
    void setServiceNumber(unsigned long long);
    //получить ФИО
    QString getFullName();
    //получить табельный номер
    unsigned long long getServiceNumber();
    //указать специфический параметр
    void setSpecParam(int com, QString value);
    //получить специфический параметр
    QString getSpecParam(int com);
    //ввод информации (способ 1)
    bool inp(unsigned long long, double, double, QString, unsigned long long, QString *TextError = 0);
    //ввод информации (способ 2)
    void inp(QString, unsigned long long);
    //ввод информации (способ 3)
    bool inp(QTextStream *file, QString * TextError = 0);
    //вывод информации (способ 1)
    virtual QString getTextOut();
    //вывод информации (способ 2)
    bool out(QTextStream *file);
};

#endif // EMPLOYEEMOBSUB_H
