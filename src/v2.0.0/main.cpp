//заголовочные файлы
#include <map>
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
map <unsigned long long, MobileSub *> user_sort_number; // пользователь сортированный по номеру телефона
multimap <double, MobileSub *> user_sort_inp_time;      // пользователь сортированный по времени входящих звонков
multimap <double, MobileSub *> user_sort_out_time;      // пользователь сортированный по вермени исходящих звонков


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
        if (user_sort_number.find(newUser->getPhoneNumber()) != user_sort_number.end())
        {
            delete newUser;
            error("Номер уже есть в базе данных.");
            return;
        } else
        {
            user_sort_number.emplace(newUser->getPhoneNumber(), newUser);
            user_sort_inp_time.emplace(newUser->getIncomingTime(), newUser);
            user_sort_out_time.emplace(newUser->getOutgoingTime(), newUser);
        }
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
        MobileSub * num_user = 0;
        unsigned long long number = 0;
        cout << "Введите номер телефона: ";
        getline(cin, inpstr);
        number = stoull(inpstr);
        if (user_sort_number.find(number) != user_sort_number.end())
        {
            status = true;
            num_user = user_sort_number[number];
        }
        if (status)
        {
            cout << "Введите время входящих звонков: ";
            getline(cin, inpstr);
            if (!num_user->setIncomingTime(stod(inpstr)))
            {
                error("Недопустимое время входящих звонков.");
                return;
            }
            cout << "Введите время исходящих звонков: ";
            getline(cin, inpstr);
            if (!num_user->setOutgoingTime(stod(inpstr)))
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


// 3. Вывод списка всех абонентов с указанием всех характеристик (сорт. по номеру телефона)
void ChapterOutAllSortNumber()
{
    system("cls");
    if (user_sort_number.size() != 0)
    {
        cout << "Список всех абонентов: \n\n";
        for (auto it = user_sort_number.begin(); it != user_sort_number.end(); it++)
        {
            it->second->out();
            cout << "\n";
        }
    } else cout << "Список пользователей пуст.\n";
    system("pause");
}


// 4. Вывод списка всех абонентов с указанием всех характеристик (сорт. по входящему времени)
void ChapterOutAllSortInpTime()
{
    system("cls");
    if (user_sort_inp_time.size() != 0)
    {
        cout << "Список всех абонентов: \n\n";
        for (auto it = user_sort_inp_time.begin(); it != user_sort_inp_time.end(); it++)
        {
            it->second->out();
            cout << "\n";
        }
    } else cout << "Список пользователей пуст.\n";
    system("pause");
}



// 5. Вывод списка всех абонентов с указанием всех характеристик (сорт. по исходящему времени)
void ChapterOutAllSortOutTime()
{
    system("cls");
    if (user_sort_out_time.size() != 0)
    {
        cout << "Список всех абонентов: \n\n";
        for (auto it = user_sort_out_time.begin(); it != user_sort_out_time.end(); it++)
        {
            it->second->out();
            cout << "\n";
        }
    } else cout << "Список пользователей пуст.\n";
    system("pause");
}


// 6. Вывод списка физических лиц с отрицательным балансом счета
void ChapterOutBadBalance()
{
    system("cls");
    bool status = false;
    if (user_sort_number.size() != 0)
    {
        cout << "Список физических лиц c отрицательным балансом: \n\n";
        for (auto it = user_sort_number.begin(); it != user_sort_number.end(); it++)
            if (it->second->getTypeSubscriber() == "физ")
                if (stod(it->second->getSpecParam(3)) < 0)
                {
                    it->second->out();
                    cout << "\n";
                    status = true;
                }
        if (!status) cout << "Не найдено ни одного пользователя. \n";
    } else cout << "Список пользователей пуст.\n";
    system("pause");
}


// 7. Удаление информации о абоненте, отказавшемся от услуг оператора
void ChapterDeleteUser()
{
    try
    {
        system("cls");
        string inpstr;
        unsigned long long number = 0;
        cout << "Введите номер телефона удаляемого абонента: ";
        getline(cin, inpstr);
        number = stoull(inpstr);
        if (user_sort_number.find(number) != user_sort_number.end())
        {
            for (auto it = user_sort_inp_time.begin(); it != user_sort_inp_time.end(); it++)
                if (it->second->getPhoneNumber() == number)
                {
                    user_sort_inp_time.erase(it);
                    break;
                }
            for (auto it = user_sort_out_time.begin(); it != user_sort_out_time.end(); it++)
                if (it->second->getPhoneNumber() == number)
                {
                    user_sort_out_time.erase(it);
                    break;
                }
            delete user_sort_number[number];
            user_sort_number.erase(number);
            cout << "Указанный пользователь удалён.\n";
            system("pause");
            return;
        }
        error("Указанный пользователь не найден.");
    } catch (...)
    {
        error("Ошибка ввод. Номер должен быть числом. ");
    }
;
}


// 8. Вывод списка абонентов, выбранного юридического лица
void ChapterOutLegalEntity()
{
    system("cls");
    bool status = false;
    if (user_sort_number.size() != 0)
    {
        string name;
        cout << "Выберите юридическое лицо: "; getline(cin, name);
        cout << "Cписок абонентов, выбранного юридического лица: \n\n";
        for (auto it = user_sort_number.begin(); it != user_sort_number.end(); it++)
            if (it->second->getTypeSubscriber() == "юр")
                if (it->second->getSpecParam(2) == name)
                {
                    it->second->out();
                    cout << "\n";
                    status = true;
                }
        if (!status) cout << "Не найдено ни одного пользователя.  \n";
    } else cout << "Список пользователей пуст.\n";
    system("pause");
}


// 9. Ввод из файла
void ChapterInpFile()
{
    system("cls");
    string type;
    MobileSub *newUser = 0;
    ifstream file("../A591_FilyuchkovaPV_task5_option_7/MobelSubDB.txt");
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
                if (user_sort_number.find(newUser->getPhoneNumber()) != user_sort_number.end())
                {
                    delete newUser;
                    error("Номер уже есть в базе данных.");
                    return;
                } else
                {
                    user_sort_number.emplace(newUser->getPhoneNumber(), newUser);
                    user_sort_inp_time.emplace(newUser->getIncomingTime(), newUser);
                    user_sort_out_time.emplace(newUser->getOutgoingTime(), newUser);
                }
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


// 10. Информация
void ChapterInfo()
{
    system("cls");
    cout << "Информация о программе: \n"
         << "Cистема абонентов мобильного оператора,\n"
         << "Кузнецов Иван Корнелиевич, v2.0.0, 17.05.2022\n\n";
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
         << "     Версия 2.0.0                                 Кузнецов И. К.\n\n\n\n\n"
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
             << "  3) Вывод списка всех абонентов с указанием всех характеристик (сорт. по номеру телефона). \n"
             << "  4) Вывод списка всех абонентов с указанием всех характеристик (сорт. по входящему времени). \n"
             << "  5) Вывод списка всех абонентов с указанием всех характеристик (сорт. по исходящему времени). \n"
             << "  6) Вывод списка  физических  лиц с отрицательным балансом счета. \n"
             << "  7) Удаление информации о абоненте, отказавшемся от услуг оператора. \n"
             << "  8) Вывод списка абонентов, выбранного юридического лица. \n"
             << "  9) Ввод данных из файла. \n"
             << "  10) Вывод информации. \n"
             << "  11) Выход из программы. \n";
        getline(cin, option);
        if (option == "1") ChapterInpNewUser(); else
        if (option == "2") ChapterInpTime(); else
        if (option == "3") ChapterOutAllSortNumber(); else
        if (option == "4") ChapterOutAllSortInpTime(); else
        if (option == "5") ChapterOutAllSortOutTime(); else
        if (option == "6") ChapterOutBadBalance(); else
        if (option == "7") ChapterDeleteUser(); else
        if (option == "8") ChapterOutLegalEntity(); else
        if (option == "9") ChapterInpFile(); else
        if (option == "10") ChapterInfo(); else
        if (option == "11") return 0; else
        {
            system("cls");
            cout << "Ошибка! Неправильно введена команда.  \n";
            system("pause");
        }
    }
}
