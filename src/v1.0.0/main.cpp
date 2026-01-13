//заголовочные файлы
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <cmath>
#include <vector>
#include "MobileSub.h"
#include "IndividualMobSub.h"
#include "LegalEntityMobSub.h"
#include "EmployeeMobSub.h"


//пространство имён
using namespace std;


//глобальные переменные
vector <MobileSub*> user;


// 0. Ошибка
void error(string text)
{
    system("cls");
    cout << "Ошибка! " << text << "\n";
    system("pause");
}


// 1. Ввод данных о новом абоненте
void ChapterInpNewUser()
{
    system("cls");
    string TextError;
    string inpstr;
    MobileSub * newUser = 0;
    cout << "Введите тип пользователя: "; getline(cin, inpstr);
    if ((inpstr == "юридическое_лицо") || (inpstr == "юр") || (inpstr == "1")) newUser = new LegalEntityMobSub; else
    if ((inpstr == "физическое_лицо") || (inpstr == "физ") || (inpstr == "2")) newUser = new IndividualMobSub; else
    if ((inpstr == "собственный_сотрудник") || (inpstr == "сотрудник") || (inpstr == "3")) newUser = new EmployeeMobSub; else
        newUser = new MobileSub;
    if(!newUser->inp(&TextError))
    {
        delete newUser;
        error(TextError);
        return;
    } else
    {
        user.emplace_back(newUser);
    }
    system("pause");
}


// 2. Ввод данных о времени входящих и исходящих звонков по номеру телефона
void ChapterInpTime()
{
    try
    {
        system("cls");
        string inpstr;
        bool status = false;
        unsigned int num_user = 0;
        unsigned long long number = 0;
        cout << "Введите номер телефона: ";
        getline(cin, inpstr);
        number = stoull(inpstr);
        for (unsigned int i = 0; i < user.size(); i++)
            if (user[i]->getPhoneNumber() == number)
            {
                status = true;
                num_user = i;
                break;
            }
        if (status)
        {
            cout << "Введите время входящих звонков: ";
            getline(cin, inpstr);
            if (!user[num_user]->setIncomingTime(stod(inpstr)))
            {
                error("Недопустимое время входящих звонков.");
                return;
            }
            cout << "Введите время исходящих звонков: ";
            getline(cin, inpstr);
            if (!user[num_user]->setOutgoingTime(stod(inpstr)))
            {
                error("Недопустимое время исходящих звонков.");
                return;
            }
        } else
        {
            error("Указанный пользователь не найден.");
            return;
        }
        system("pause");
    } catch (...)
    {
        error("Введено недопустимое значение.");
        return;
    }
}


// 3. Вывод списка всех абонентов с указанием всех характеристик
void ChapterOutAll()
{
    system("cls");
    if (user.size() != 0)
    {
        cout << "Список всех абонентов: \n\n";
        for (unsigned int i = 0; i < user.size(); i++)
        {
                user[i]->out();
                cout << "\n";
        }
    } else cout << "Список пользователей пуст.\n";
    system("pause");
}


// 4. Вывод списка физических лиц с отрицательным балансом счета
void ChapterOutBadBalance()
{
    system("cls");
    bool status = false;
    if (user.size() != 0)
    {
        cout << "Список физических лиц c отрицательным балансом: \n\n";
        for (unsigned int i = 0; i < user.size(); i++)
            if (user[i]->getTypeSubscriber() == "физ")
                if (stod(user[i]->getSpecParam(3)) < 0)
                {
                    user[i]->out();
                    cout << "\n";
                    status = true;
                }
        if (!status) cout << "Не найдено ни одного пользователя. \n";
    } else cout << "Список пользователей пуст.\n";
    system("pause");
}


// 5. Удаление информации о абоненте, отказавшемся от услуг оператора
void ChapterDeleteUser()
{
    system("cls");
    string inpstr;
    bool status = false;
    unsigned int num_user = 0;
    unsigned long long number = 0;
    cout << "Введите номер телефона удаляемого абонента: ";
    getline(cin, inpstr);
    number = stoull(inpstr);
    for (unsigned int i = 0; i < user.size(); i++)
        if (user[i]->getPhoneNumber() == number)
        {
            status = true;
            num_user = i;
            break;
        }
    if (status)
    {
        delete user[num_user];
        user.erase(user.begin()+num_user);
        cout << "Указанный пользователь удалён.\n";
    } else
    {
        error("Указанный пользователь не найден.");
        return;
    }
    system("pause");
}


// 6. Вывод списка абонентов, выбранного юридического лица
void ChapterOutLegalEntity()
{
    system("cls");
    bool status = false;
    if (user.size() != 0)
    {
        string name;
        cout << "Выберите юридическое лицо: "; getline(cin, name);
        cout << "Cписок абонентов, выбранного юридического лица: \n\n";
        for (unsigned int i = 0; i < user.size(); i++)
            if (user[i]->getTypeSubscriber() == "юр")
                if (user[i]->getSpecParam(2) == name)
                {
                    user[i]->out();
                    cout << "\n";
                    status = true;
                }
        if (!status) cout << "Не найдено ни одного пользователя.  \n";
    } else cout << "Список пользователей пуст.\n";
    system("pause");
}


//7. Ввод из файла
void ChapterInpFile()
{
    system("cls");
    string type;
    MobileSub *newUser = 0;
    ifstream file("test.database.txt");
    if (file)
    {
        while (!file.eof())
        {
            file >> type;
            if ((type == "юридическое_лицо") || (type == "юр") || (type == "1")) newUser = new LegalEntityMobSub; else
            if ((type == "физическое_лицо") || (type == "физ") || (type == "2")) newUser = new IndividualMobSub; else
            if ((type == "собственный_сотрудник") || (type == "сотрудник") || (type == "3")) newUser = new EmployeeMobSub; else
                newUser = new MobileSub;
            if (newUser->inp(&file))
            {
                user.emplace_back(newUser);
            } else
            {
                cout << "При чтении файла произошла ошибка. \n";
                delete newUser;
                system("pause");
                return;
            }
        }
        cout << "Чтение файла прошло успешно.\n";
    } else cout << "Программа не смогла обнаружить файл базы данных.\n";
    system("pause");
}


// 8. Информация
void ChapterInfo()
{
    system("cls");
    cout << "Информация о программе: \n"
         << "Cистема абонентов мобильного оператора,\n"
         << "Кузнецов Иван Корнелиевич, v1.0.0, 16.05.2022\n\n";
    system("pause");
}


//главная программа
int main()
{
    //настройка программы
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    system("color 1f");
    system("title Cистема абонентов мобильного оператора ");
    HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {80, 1000};
    SetConsoleScreenBufferSize(hWnd, bufferSize);
    //заставка
    cout << "\n\n\n\n\n\n\n\n"
         << "                 СИСТЕМА АБОНЕНТОВ МОБИЛЬНОГО ОПЕРАТОРА\n\n\n\n\n\n\n\n"
         << "     Версия 1.0.0                                 Кузнецов И. К.\n\n\n\n\n"
         << "                     Санкт-Петербург, 2022\n\n\n\n";
    system("pause");
    //меню
    string option;
    while (true)
    {
        system("cls");
        cout << "Меню: \n"
             << "  1) Ввод данных о новом абоненте. \n"
             << "  2) Ввод данных о времени входящих и исходящих звонков по номеру телефона. \n"
             << "  3) Вывод списка всех абонентов с указанием всех характеристик. \n"
             << "  4) Вывод списка  физических  лиц с отрицательным балансом счета. \n"
             << "  5) Удаление информации о абоненте, отказавшемся от услуг оператора. \n"
             << "  6) Вывод списка абонентов, выбранного юридического лица. \n"
             << "  7) Ввод данных из файла. \n"
             << "  8) Вывод информации. \n"
             << "  9) Выход из программы. \n";
        getline(cin, option);
        if (option == "1") ChapterInpNewUser(); else
        if (option == "2") ChapterInpTime(); else
        if (option == "3") ChapterOutAll(); else
        if (option == "4") ChapterOutBadBalance(); else
        if (option == "5") ChapterDeleteUser(); else
        if (option == "6") ChapterOutLegalEntity(); else
        if (option == "7") ChapterInpFile(); else
        if (option == "8") ChapterInfo(); else
        if (option == "9") return 0; else
        {
            system("cls");
            cout << "Ошибка! Неправильно введена команда.  \n";
            system("pause");
        }
    }
}
