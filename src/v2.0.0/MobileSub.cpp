//заголовочные файлы
#include <iostream>
#include <fstream>
#include "MobileSub.h"


//пространство имён
using namespace std;


//создание нового объекта класса (способ 1)
MobileSub::MobileSub() {}


//создание нового объекта класса (способ 2)
MobileSub::MobileSub(unsigned long long inpPhoneNumber, double inpIncomingTime, double inpOutgoingTime, string *TextError)
{
    inp(inpPhoneNumber, inpIncomingTime, inpOutgoingTime, TextError);
}


//указать функция для номер телефона
void MobileSub::setPhoneNumber(unsigned long long inpPhoneNumber)
{
   PhoneNumber = inpPhoneNumber;
}


//указать тип абонента
bool MobileSub::setTypeSubscriber(string inpType)
{
    if ((inpType == "юридическое_лицо") || (inpType == "юр") || (inpType == "1"))
    {
        TypeSubscriber = "юр";
        return true;
    } else
    if ((inpType == "физическое_лицо") || (inpType == "физ") || (inpType == "2"))
    {
        TypeSubscriber = "физ";
        return true;
    } else
    if ((inpType == "собственный_сотрудник") || (inpType == "сотрудник") || (inpType == "3"))
    {
        TypeSubscriber = "сотрудник";
        return true;
    } else return false;
}


//указать время входящих звонков
bool MobileSub::setIncomingTime(double inpTime)
{
    if (inpTime >= 0)
    {
        IncomingTime = inpTime;
        return true;
    } else return false;
}


//указать время исходящих звонков
bool MobileSub::setOutgoingTime(double inpTime)
{
    if (inpTime >= 0)
    {
        OutgoingTime = inpTime;
        return true;
    } else return false;
}


//получить номер телефона
unsigned long long MobileSub::getPhoneNumber()
{
    return PhoneNumber;
}


//получить тип абонента
string MobileSub::getTypeSubscriber()
{
    return TypeSubscriber;
}


//получить время входящих звонков
double MobileSub::getIncomingTime()
{
    return IncomingTime;
}


//получить время исходящих звонков
double MobileSub::getOutgoingTime()
{
    return OutgoingTime;
}


//получить специфический параметр
string MobileSub::getSpecParam(int com)
{
    return "Для данного класса не предусмотрено такого параметра. ";
}


//ввод информации (способ 1)
bool MobileSub::inp(string *outTextError)
{
    try
    {
        string inpStr;
        unsigned long long inpPhoneNumber = 0;
        string inpTypeSubscriber = TypeSubscriber;
        double inpIncomingTime = 0;
        double inpOutgoingTime = 0;
        cout << "Введите номер телефона: ";
        getline(cin, inpStr);
        inpPhoneNumber = stoull(inpStr);
        cout << "Введите время входящих звонков: ";
        getline(cin, inpStr);
        inpIncomingTime = stod(inpStr);
        cout << "Введите время исходящих звонков: ";
        getline(cin, inpStr);
        inpOutgoingTime = stod(inpStr);
        return inp(inpPhoneNumber, inpIncomingTime, inpOutgoingTime, outTextError);
    } catch (...)
    {
        if (outTextError != 0) *outTextError = "Ведено недопустимое значение.";
        return false;
    }
}


//ввод информации (способ 2)
bool MobileSub::inp(unsigned long long inpPhoneNumber, double inpIncomingTime, double inpOutgoingTime, string *outTextError)
{
    string TextError;
    setPhoneNumber(inpPhoneNumber);
    if (!setIncomingTime(inpIncomingTime)) TextError += "Время входящих звонков не может быть отрицательным.";
    if (!setOutgoingTime(inpOutgoingTime)) TextError += "Время исходящих звонков не может быть отрицательным. ";
    if (TextError.empty())
    {
        if (outTextError != 0) *outTextError = "Операция прошла успешно.";
        return true;
    } else
    {
        if (outTextError != 0) *outTextError = TextError;
        return false;
    }
}


//ввод информации (способ 3)
bool MobileSub::inp(ifstream *file, string *outTextError)
{
    try
    {
        unsigned long long inpPhoneNumber = 0;
        double inpIncomingTime = 0;
        double inpOutgoingTime = 0;
        *file >> inpPhoneNumber >> inpIncomingTime >> inpOutgoingTime;
        return MobileSub::inp(inpPhoneNumber, inpIncomingTime, inpOutgoingTime, outTextError);
    } catch (...)
    {
        if (outTextError != 0) *outTextError = "Ведено недопустимое значение.";
        return false;
    }
}


//вывод информации (способ 1)
void MobileSub::out()
{
    cout << "Номер телефона: " << getPhoneNumber() << "\n"
         << "Тип абонента: " << getTypeSubscriber() << "\n"
         << "Время входящих звонков: " << getIncomingTime() << "\n"
         << "Время исходящих звонков: " << getOutgoingTime() << "\n";
}


//вывод информации (способ 2)
bool MobileSub::out(ofstream *file)
{
    try
    {
        *file << getTypeSubscriber() << " "
              << getPhoneNumber() << " "
              << getIncomingTime() << " "
              << getOutgoingTime() << " ";
        return true;
    } catch (...)
    {
        return false;
    }
}
