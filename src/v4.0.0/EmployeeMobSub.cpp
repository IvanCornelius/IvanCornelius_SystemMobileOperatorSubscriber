//заголовочные файлы
#include <iostream>
#include <fstream>
#include "EmployeeMobSub.h"


//создание нового объекта класса (способ 1)
EmployeeMobSub::EmployeeMobSub() {setTypeSubscriber("сотрудник");}


//создание нового объекта класса (способ 2)
EmployeeMobSub::EmployeeMobSub(unsigned long long inpNumber, double inpIncTime, double inpOutTime, QString inpFullName, unsigned long long inpSNumber, QString *TextError)
{
    setTypeSubscriber("сотрудник");
    inp(inpNumber, inpIncTime, inpOutTime, inpFullName, inpSNumber);
}


//указать ФИО
void EmployeeMobSub::setFullName(QString inpFullName)
{
    FullName = inpFullName;
}


//указать табельный номер
void EmployeeMobSub::setServiceNumber(unsigned long long inpNumber)
{
    ServiceNumber = inpNumber;
}


//указать ФИО
QString EmployeeMobSub::getFullName()
{
    return FullName;
}


//указать табельный номер
unsigned long long EmployeeMobSub::getServiceNumber()
{
    return ServiceNumber;
}


//указание специфический параметр
void EmployeeMobSub::setSpecParam(int com, QString value)
{
    if (com == 1) setFullName(value); else
    if (com == 2) setServiceNumber(value.toULongLong());
}


//получить специфический параметр
QString EmployeeMobSub::getSpecParam(int com)
{
    if (com == 1) return getFullName(); else
    if (com == 2) return QString::number(getServiceNumber()); else
        return "Нет выбранного параметра.";
}


//ввод информации (способ 1)
bool EmployeeMobSub::inp(unsigned long long inpNumber, double inpIncTime, double inpOutTime, QString inpFullName, unsigned long long inpSN, QString *TextError)
{
    if (!MobileSub::inp(inpNumber, inpIncTime, inpOutTime, TextError)) return false;
    setFullName(inpFullName);
    setServiceNumber(inpSN);
    return true;
}


//ввод информации (способ 2)
void EmployeeMobSub::inp(QString inpFullName, unsigned long long inpSN)
{
    setFullName(inpFullName);
    setServiceNumber(inpSN);
}


//ввод информации (способ 3)
bool EmployeeMobSub::inp(QTextStream *file, QString *TextError)
{
    if (!MobileSub::inp(file, TextError)) return false;
    try
    {
        QString inpFullName;
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
QString EmployeeMobSub::getTextOut()
{
    return MobileSub::getTextOut() + "ФИО: " + getFullName() + "\n"
            + "Табельный номер: " + QString::number(getServiceNumber()) + "\n";
}


//вывод информации (способ 2)
bool EmployeeMobSub::out(QTextStream *file)
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
