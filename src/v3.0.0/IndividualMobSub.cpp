//заголовочные файлы
#include <iostream>
#include <fstream>
#include "MobileSub.h"
#include "IndividualMobSub.h"


//создание нового объекта класса (способ 1)
IndividualMobSub::IndividualMobSub() {setTypeSubscriber("физ");}


//создание нового объекта класса (способ 2)
IndividualMobSub::IndividualMobSub(unsigned long long inpNumber, double inpIncTime, double inpOutTime, QString inpName, QString inpPasData, double inpBal, QString *TextError)
{
    setTypeSubscriber("физ");
    inp(inpNumber, inpIncTime, inpOutTime, inpName, inpPasData, inpBal, TextError);
}


//указать ФИО
void IndividualMobSub::setFullName(QString inpFullName)
{
    FullName = inpFullName;
}


//указать паспортные данные
void IndividualMobSub::setPassportData(QString inpPassportData)
{
    PassportData = inpPassportData;
}


//указать баланс счета
void IndividualMobSub::setBalance(double inpBalance)
{
    Balance = inpBalance;
}


//получить ФИО
QString IndividualMobSub::getFullName()
{
    return FullName;
}


//получить паспортные данные
QString IndividualMobSub::getPassportData()
{
    return PassportData;
}


//получить баланс счета
double IndividualMobSub::getBalance()
{
    return Balance;
}


//указать специфический параметр
void IndividualMobSub::setSpecParam(int com, QString value)
{
    if (com == 1) setFullName(value); else
    if (com == 2) setPassportData(value); else
    if (com == 3) setBalance(value.toDouble());
}


//получить специфический параметр
QString IndividualMobSub::getSpecParam(int com)
{
    if (com == 1) return getFullName(); else
    if (com == 2) return getPassportData(); else
    if (com == 3) return QString::number(getBalance()); else
        return "Нет выбранного параметра.";
}


//ввод информации (способ 1)
bool IndividualMobSub::inp(unsigned long long inpNumber, double inpIncTime, double inpOutTime, QString inpName, QString inpPasData, double inpBal, QString *TextError)
{
    if (!MobileSub::inp(inpNumber, inpIncTime, inpOutTime, TextError)) return false;
    setFullName(inpName);
    setPassportData(inpPasData);
    setBalance(inpBal);
    return true;
}

//ввод информации (способ 2)
bool IndividualMobSub::inp(QString inpName, QString inpPasData, double inpBal)
{
    setFullName(inpName);
    setPassportData(inpPasData);
    setBalance(inpBal);
    return true;
}


//ввод информации (способ 3)
bool IndividualMobSub::inp(QTextStream *file, QString *TextError)
{
    if (!MobileSub::inp(file, TextError)) return false;
    try
    {
        QString inpFullName;
        QString inpPassportData;
        double inpBalance = 0;
        *file >> inpFullName >> inpPassportData >> inpBalance;
        return IndividualMobSub::inp(inpFullName, inpPassportData, inpBalance);
    } catch (...)
    {
        if (TextError != 0) *TextError = "Ведено недопустимое значение.";
        return false;
    }
}


//вывод информации (способ 1)
QString IndividualMobSub::getTextOut()
{
    return MobileSub::getTextOut()
            + "ФИО: " + getFullName() + "\n"
            + "Паспортные данные: " + getPassportData() + "\n"
            + "Баланс счета: " + QString::number(getBalance()) + "\n";
}


//вывод информации (способ 2)
bool IndividualMobSub::out(QTextStream *file)
{
    if (!MobileSub::out(file)) return false;
    try
    {
        *file << getFullName() << " "
             << getPassportData() << " "
             << getBalance() << "\n";
        return true;
    } catch (...)
    {
        return false;
    }
}
