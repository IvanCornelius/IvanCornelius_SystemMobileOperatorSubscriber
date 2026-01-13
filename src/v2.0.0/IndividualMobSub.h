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
    string FullName = "не указано";
    //паспортные данные
    string PassportData ="не указано";
    //баланс счета
    double Balance = 0;
//публичные методы
public:
    //создание нового объекта класса (способ 1)
    IndividualMobSub();
    //создание нового объекта класса (способ 2)
    IndividualMobSub(unsigned long long, double, double, string, string, double, string *TextError = 0);
    //указать ФИО
    void setFullName(string);
    //указать паспортные данные
    void setPassportData(string);
    //указать баланс счета
    void setBalance(double);
    //получить ФИО
    string getFullName();
    //получить паспортные данные
    string getPassportData();
    //получить баланс счета
    double getBalance();
    //получить специфический параметр
    string getSpecParam(int com);
    //ввод информации (способ 1)
    bool inp(string * TextError = 0);
    //ввод информации (способ 2)
    bool inp(unsigned long long, double, double, string, string, double, string *TextError = 0);
    //ввод информации (способ 3)
    bool inp(string, string, double);
    //ввод информации (способ 4)
    bool inp(ifstream *file, string *TextError = 0);
    //вывод информации (способ 1)
    void out();
    //вывод информации (способ 2)
    bool out(ofstream *file);
};


#endif // IndividualMobSub_H
