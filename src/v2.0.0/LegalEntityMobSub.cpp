//заголовочные файлы
#include <cmath>
#include <iostream>
#include <fstream>
#include "MobileSub.h"
#include "LegalEntityMobSub.h"


//создание нового объекта класса (способ 1)
LegalEntityMobSub::LegalEntityMobSub() {setTypeSubscriber("юр");}


//создание нового объекта класса (способ 2)
LegalEntityMobSub::LegalEntityMobSub(unsigned long long inpNumber, double inpIncTime, double inpOutTime, unsigned long long inpINN, string inpName, string inpAddress, string *TextError)
{
    setTypeSubscriber("юр");
    inp(inpNumber, inpIncTime, inpOutTime, inpINN, inpName, inpAddress, TextError);
}


//указать ИНН
bool LegalEntityMobSub::setINN(unsigned long long inpINN)
{
    if ((inpINN >= pow(10, 10)) && (inpINN<pow(10, 11)))
    {
        INN = inpINN;
        return true;
    } else return false;
}


//указать название
void LegalEntityMobSub::setName(string inpName)
{
    Name = inpName;
}


//указать адрес
void LegalEntityMobSub::setAddress(string inpAddress)
{
    Address = inpAddress;
}


//получить ИНН
unsigned long long LegalEntityMobSub::getINN()
{
    return INN;
}


//получить название
string LegalEntityMobSub::getName()
{
    return Name;
}


//получить адрес
string LegalEntityMobSub::getAddress()
{
    return Address;
}


//получить специфический параметр
string LegalEntityMobSub::getSpecParam(int com)
{
    if (com == 1) return to_string(getINN()); else
    if (com == 2) return getName(); else
        if (com == 3) return getAddress(); else
            return "Нет выбранного параметра.";
}


//ввод информации (способ 1)
bool LegalEntityMobSub::inp(string *TextError)
{
    try
    {
        if (!MobileSub::inp(TextError)) return false;
        string inpStr;
        unsigned long long inpINN = 0;
        string inpName;
        string inpAddress;
        cout << "Введите ИНН: ";
        getline(cin, inpStr);
        inpINN = stoull(inpStr);
        cout << "Введите название: ";
        getline(cin, inpName);
        cout << "Введите адрес ";
        getline(cin, inpAddress);
        return  inp(inpINN, inpName, inpAddress, TextError);
    } catch (...)
    {
        if (TextError != 0) *TextError = "Ведено недопустимое значение. ";
        return false;
    }
}


//ввод информации (способ 2)
bool LegalEntityMobSub::inp(unsigned long long inpNumber, double inpIncTime, double inpOutTime, unsigned long long inpINN, string inpName, string inpAddress, string *TextError)
{
    if (!MobileSub::inp(inpNumber, inpIncTime, inpOutTime, TextError)) return false;
    if (!setINN(inpINN))
    {
        *TextError = "Недоступный ИНН. ";
        return false;
    }
    setName(inpName);
    setAddress(inpAddress);
    return true;
}


//ввод информации (способ 3)
bool LegalEntityMobSub::inp(unsigned long long inpINN, string inpName, string inpAddress, string *TextError)
{
    if (!setINN(inpINN))
    {
        *TextError = "Недоступный ИНН. ";
        return false;
    }
    setName(inpName);
    setAddress(inpAddress);
    return true;
}


//ввод информации (способ 4)
bool LegalEntityMobSub::inp(ifstream *file, string *TextError)
{
    if (!MobileSub::inp(file, TextError)) return false;
    try
    {
        unsigned long long inpINN = 0;
        string inpName;
        string inpAddress;
        *file >> inpINN >> inpName >> inpAddress;
        return LegalEntityMobSub::inp(inpINN, inpName, inpAddress, TextError);
    } catch (...)
    {
        if (TextError != 0) *TextError += "Ведено недопустимое значение.";
        return false;
    }
}


//вывод информации (способ 1)
void LegalEntityMobSub::out()
{
    MobileSub::out();
    cout << "ИНН: " << getINN() << "\n"
         << "Название: " << getName() << "\n"
         << "Адрес: " << getAddress() << "\n";
}


//вывод информации (способ 2)
bool LegalEntityMobSub::out(ofstream *file)
{
    if (!MobileSub::out(file)) return false;
    try
    {
        *file << getINN() << " "
              << getName() << " "
              << getAddress() << "\n";
        return true;
    } catch (...)
    {
        return false;
    }
}
