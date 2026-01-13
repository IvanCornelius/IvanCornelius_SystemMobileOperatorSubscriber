//заголовочные файлы
#include <iostream>
#include <fstream>
#include "MobileSub.h"
#include "IndividualMobSub.h"


//создание нового объекта класса (способ 1)
IndividualMobSub::IndividualMobSub() {setTypeSubscriber("физ");}


//создание нового объекта класса (способ 2)
IndividualMobSub::IndividualMobSub(unsigned long long inpNumber, double inpIncTime, double inpOutTime, string inpName, string inpPasData, double inpBal, string *TextError)
{
    setTypeSubscriber("физ");
    inp(inpNumber, inpIncTime, inpOutTime, inpName, inpPasData, inpBal, TextError);
}


//указать ФИО
void IndividualMobSub::setFullName(string inpFullName)
{
    FullName = inpFullName;
}


//указать паспортные данные
void IndividualMobSub::setPassportData(string inpPassportData)
{
    PassportData = inpPassportData;
}


//указать баланс счета
void IndividualMobSub::setBalance(double inpBalance)
{
    Balance = inpBalance;
}


//получить ФИО
string IndividualMobSub::getFullName()
{
    return FullName;
}


//получить паспортные данные
string IndividualMobSub::getPassportData()
{
    return PassportData;
}


//получить баланс счета
double IndividualMobSub::getBalance()
{
    return Balance;
}


//получить специфический параметр
string IndividualMobSub::getSpecParam(int com)
{
    if (com == 1) return getFullName(); else
    if (com == 2) return getPassportData(); else
    if (com == 3) return to_string(getBalance()); else
        return "Нет выбранного параметра.";
}


//ввод информации (способ 1)
bool IndividualMobSub::inp(string *outTextError)
{
    try
    {
        if (!MobileSub::inp(outTextError)) return false;
        string inpStr;
        string FullName;
        string PassportData;
        double Balance = 0;
        cout << "Введите ФИО: ";
        getline(cin, FullName);
        cout << "Введите паспортные данные: ";
        getline(cin, PassportData);
        cout << "Введите баланс счета: ";
        getline(cin, inpStr);
        Balance = stod(inpStr);
        return inp(FullName, PassportData, Balance);
    } catch (...)
    {
        if (outTextError != 0) *outTextError = "Ведено недопустимое значение.";
        return false;
    }
}


//ввод информации (способ 2)
bool IndividualMobSub::inp(unsigned long long inpNumber, double inpIncTime, double inpOutTime, string inpName, string inpPasData, double inpBal, string *TextError)
{
    if (!MobileSub::inp(inpNumber, inpIncTime, inpOutTime, TextError)) return false;
    setFullName(inpName);
    setPassportData(inpPasData);
    setBalance(inpBal);
    return true;
}

//ввод информации (способ 3)
bool IndividualMobSub::inp(string inpName, string inpPasData, double inpBal)
{
    setFullName(inpName);
    setPassportData(inpPasData);
    setBalance(inpBal);
    return true;
}


//ввод информации (способ 4)
bool IndividualMobSub::inp(ifstream *file, string *TextError)
{
    if (!MobileSub::inp(file, TextError)) return false;
    try
    {
        string inpFullName;
        string inpPassportData;
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
void IndividualMobSub::out()
{
    MobileSub::out();
    cout << "ФИО: " << getFullName() << "\n"
         << "Паспортные данные: " << getPassportData() << "\n"
         << "Баланс счета: " << getBalance() << "\n";
}


//вывод информации (способ 2)
bool IndividualMobSub::out(ofstream *file)
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
