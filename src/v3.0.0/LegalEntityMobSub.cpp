//заголовочные файлы
#include <cmath>
#include <iostream>
#include <fstream>
#include "MobileSub.h"
#include "LegalEntityMobSub.h"


//создание нового объекта класса (способ 1)
LegalEntityMobSub::LegalEntityMobSub() {setTypeSubscriber("юр");}


//создание нового объекта класса (способ 2)
LegalEntityMobSub::LegalEntityMobSub(unsigned long long inpNumber, double inpIncTime, double inpOutTime, unsigned long long inpINN, QString inpName, QString inpAddress, QString *TextError)
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
void LegalEntityMobSub::setName(QString inpName)
{
    Name = inpName;
}


//указать адрес
void LegalEntityMobSub::setAddress(QString inpAddress)
{
    Address = inpAddress;
}


//получить ИНН
unsigned long long LegalEntityMobSub::getINN()
{
    return INN;
}


//получить название
QString LegalEntityMobSub::getName()
{
    return Name;
}

//получить адрес
QString LegalEntityMobSub::getAddress()
{
    return Address;
}

//указать специфический параметр
void LegalEntityMobSub::setSpecParam(int com, QString value)
{
    if (com == 1) setINN(value.toULongLong()); else
    if (com == 2) setName(value); else
    if (com == 3) setAddress(value);
}

//получить специфический параметр
QString LegalEntityMobSub::getSpecParam(int com)
{
    if (com == 1) return QString::number(getINN()); else
    if (com == 2) return getName(); else
    if (com == 3) return getAddress(); else
        return "Нет выбранного параметра.";
}


//ввод информации (способ 1)
bool LegalEntityMobSub::inp(unsigned long long inpNumber, double inpIncTime, double inpOutTime, unsigned long long inpINN, QString inpName, QString inpAddress, QString *TextError)
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


//ввод информации (способ 2)
bool LegalEntityMobSub::inp(unsigned long long inpINN, QString inpName, QString inpAddress, QString *TextError)
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


//ввод информации (способ 3)
bool LegalEntityMobSub::inp(QTextStream *file, QString *TextError)
{
    if (!MobileSub::inp(file, TextError)) return false;
    try
    {
        unsigned long long inpINN = 0;
        QString inpName;
        QString inpAddress;
        *file >> inpINN >> inpName >> inpAddress;
        return LegalEntityMobSub::inp(inpINN, inpName, inpAddress, TextError);
    } catch (...)
    {
        if (TextError != 0) *TextError += "Ведено недопустимое значение.";
        return false;
    }
}


//вывод информации (способ 1)
QString LegalEntityMobSub::getTextOut()
{
    return MobileSub::getTextOut()
           + "ИНН: " + QString::number(getINN()) + "\n"
           + "Название: " + getName() + "\n"
           + "Адрес: " + getAddress() + "\n";
}


//вывод информации (способ 2)
bool LegalEntityMobSub::out(QTextStream *file)
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
