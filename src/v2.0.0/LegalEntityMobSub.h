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
    string Name = "не указано";
    //адрес
    string Address = "не указано";
//публичные методы
public:
    //создание нового объекта класса (способ 1)
    LegalEntityMobSub();
    //создание нового объекта класса (способ 2)
    LegalEntityMobSub(unsigned long long, double, double, unsigned long long, string, string, string *TextError);
    //указать ИНН
    bool setINN(unsigned long long);
    //указать название
    void setName(string);
    //указать адрес
    void setAddress(string);
    //получить ИНН
    unsigned long long getINN();
    //получить название
    string getName();
    //получить адрес
    string getAddress();
    //получить специфический параметр
    string getSpecParam(int com);
    //ввод информации (способ 1)
    bool inp(string *TextError = 0);
    //ввод информации (способ 2)
    bool inp(unsigned long long, double, double, unsigned long long, string, string, string *TextError);
    //ввод информации (способ 3)
    bool inp(unsigned long long, string, string, string *TextError);
    //ввод информации (способ 4)
    bool inp(ifstream *file, string *TextError = 0);
    //вывод информации (способ 1)
    void out();
    //вывод информации (способ 2)
    bool out(ofstream *file);
};

#endif // LegalEntityMobSub_H
