//заголовочные файлы
#include <iostream>
#include <fstream>
#include "EmployeeMobSub.h"


//создание нового объекта класса (способ 1)
EmployeeMobSub::EmployeeMobSub() {setTypeSubscriber("сотрудник");}


//создание нового объекта класса (способ 2)
EmployeeMobSub::EmployeeMobSub(unsigned long long inpNumber, double inpIncTime, double inpOutTime, string inpFullName, unsigned long long inpSNumber, string *TextError)
{
    setTypeSubscriber("сотрудник");
    inp(inpNumber, inpIncTime, inpOutTime, inpFullName, inpSNumber);
}


//указать ФИО
void EmployeeMobSub::setFullName(string inpFullName)
{
    FullName = inpFullName;
}


//указать табельный номер
void EmployeeMobSub::setServiceNumber(unsigned long long inpNumber)
{
    ServiceNumber = inpNumber;
}


//указать ФИО
string EmployeeMobSub::getFullName()
{
    return FullName;
}


//указать табельный номер
unsigned long long EmployeeMobSub::getServiceNumber()
{
    return ServiceNumber;
}


//получить специфический параметр
string EmployeeMobSub::getSpecParam(int com)
{
    if (com == 1) return getFullName(); else
    if (com == 2) return to_string(getServiceNumber()); else
        return "Нет выбранного параметра.";
}



//ввод информации (способ 1)
bool EmployeeMobSub::inp(string *TextError)
{
    try
    {
        if (!MobileSub::inp(TextError)) return false;
        string inpStr;
        string inpFullName;
        unsigned long long inpSNumber = 0;
        cout << "Введите ФИО: ";
        getline(cin, inpFullName);
        cout << "Введите табельный номер: ";
        getline(cin, inpStr);
        inpSNumber = stoull(inpStr);
        inp(inpFullName, inpSNumber);
        return true;
    } catch (...)
    {
        if (TextError != 0) *TextError = "Ведено недопустимое значение.";
        return false;
    }
}


//ввод информации (способ 2)
bool EmployeeMobSub::inp(unsigned long long inpNumber, double inpIncTime, double inpOutTime, string inpFullName, unsigned long long inpSN, string *TextError)
{
    if (!MobileSub::inp(inpNumber, inpIncTime, inpOutTime, TextError)) return false;
    setFullName(inpFullName);
    setServiceNumber(inpSN);
    return true;
}


//ввод информации (способ 3)
void EmployeeMobSub::inp(string inpFullName, unsigned long long inpSN)
{
    setFullName(inpFullName);
    setServiceNumber(inpSN);
}


//ввод информации (способ 4)
bool EmployeeMobSub::inp(ifstream *file, string *TextError)
{
    if (!MobileSub::inp(file, TextError)) return false;
    try
    {
        string inpFullName;
        unsigned long long inpSN = 0;
        *file >> inpFullName >> inpSN;
        EmployeeMobSub::inp(inpFullName, inpSN);
        return true;
    } catch (...)
    {
        if (TextError != 0) *TextError = "Ведено недопустимое значение.";
        return false;
    }
}


//вывод информации (способ 1)
void EmployeeMobSub::out()
{
    MobileSub::out();
    cout << "ФИО: " << getFullName() << "\n"
         << "Табельный номер: " << getServiceNumber() << "\n";
}


//вывод информации (способ 2)
bool EmployeeMobSub::out(ofstream *file)
{
    if (!MobileSub::out(file)) return false;
    try
    {
        *file << getFullName() << " "
              << getServiceNumber() << "\n";
        return true;
    } catch (...)
    {
        return false;
    }
}
