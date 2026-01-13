#ifndef MOBILESUB_H
#define MOBILESUB_H


//заголовочные файлы
#include <QString>
#include <QTextStream>


//класс для информации абонента мобильного оператора
class MobileSub
{
//приватные методы
private:
    //номер телефона
    unsigned long long PhoneNumber = 0;
    //тип абонента
    QString TypeSubscriber = "не указано";
    //время входящих звонков
    double IncomingTime = 0;
    //время исходящих звонков
    double OutgoingTime = 0;
//публичные методы
public:
    //создание нового объекта класса (способ 1)
    MobileSub();
    //создание нового объекта класса (способ 2)
    MobileSub(unsigned long long inpPhoneNumber, double inpIncomingTime, double inpOutgoingTime, QString *TextError = 0);
    //указать функция для номер телефона
    void setPhoneNumber(unsigned long long);
    //указать тип абонента
    bool setTypeSubscriber(QString);
    //указать время входящих звонков
    bool setIncomingTime(double);
    //указать время исходящих звонков
    bool setOutgoingTime(double);
    //получить номер телефона
    unsigned long long getPhoneNumber();
    //получить тип абонента
    QString getTypeSubscriber();
    //получить время входящих звонков
    double getIncomingTime();
    //получить время исходящих звонков
    double getOutgoingTime();
    //указать специфический параметр
    virtual void setSpecParam(int com, QString value);
    //получить специфический параметр
    virtual QString getSpecParam(int com);
    //ввод информации (способ 2)
    bool inp(unsigned long long inpPhoneNumber, double inpIncomingTime, double inpOutgoingTime, QString *TextError = 0);
    //ввод информации (способ 3)
    virtual bool inp(QTextStream *file, QString *TextError = 0);
    //вывод информации (способ 1)
    virtual QString getTextOut();
    //вывод информации (способ 2)
    virtual bool out(QTextStream *file);
};


#endif // MOBILESUB_H
