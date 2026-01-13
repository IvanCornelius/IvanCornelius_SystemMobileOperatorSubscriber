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
    string FullName = "не указано";
    //табельный номер
    unsigned long long ServiceNumber = 0;
//приватные методы
public:
    //создание нового объекта класса (способ 1)
    EmployeeMobSub();
    //создание нового объекта класса (способ 2)
    EmployeeMobSub(unsigned long long, double, double, string, unsigned long long, string *TextError = 0);
    //указать ФИО
    void setFullName(string);
    //указать табельный номер
    void setServiceNumber(unsigned long long);
    //получить ФИО
    string getFullName();
    //получить табельный номер
    unsigned long long getServiceNumber();
    //получить специфический параметр
    string getSpecParam(int com);
    //ввод информации (способ 1)
    bool inp(string * TextError = 0);
    //ввод информации (способ 2)
    bool inp(unsigned long long, double, double, string, unsigned long long, string *TextError = 0);
    //ввод информации (способ 3)
    void inp(string, unsigned long long);
    //ввод информации (способ 4)
    bool inp(ifstream *file, string * TextError = 0);
    //вывод информации (способ 1)
    void out();
    //вывод информации (способ 2)
    bool out(ofstream *file);
};

#endif // EMPLOYEEMOBSUB_H
