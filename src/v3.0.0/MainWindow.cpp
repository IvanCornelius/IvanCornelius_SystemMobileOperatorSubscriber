#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sort_win = new SortUserWindow;
    sort_win->setModal(true);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update_list()
{
    ui->listWidget_user->clear();
    if (sort_win->get_type_filter() == 0)
    {
        if (sort_win->get_type_sort() == 0)
        {
            for (auto it = user_sort_number.begin(); it != user_sort_number.end(); it++)
            {
                    ui->listWidget_user->addItem("Номер: " + QString::number(it->second->getPhoneNumber()) + "; "
                                                 "Тип абонента: " + it->second->getTypeSubscriber() + "; "
                                                 "Время входящих: " + QString::number(it->second->getIncomingTime()) + "; "
                                                 "Исходящих звонков: " + QString::number(it->second->getOutgoingTime()) + ".");
                    ui->listWidget_user->item(ui->listWidget_user->count()-1)->setData(Qt::UserRole, it->second->getPhoneNumber());
            }
        } else
        if (sort_win->get_type_sort() == 1)
        {
            for (auto it = user_sort_inp_time.begin(); it != user_sort_inp_time.end(); it++)
            {
                    ui->listWidget_user->addItem("Номер: " + QString::number(it->second->getPhoneNumber()) + "; "
                                                 "Тип абонента: " + it->second->getTypeSubscriber() + "; "
                                                 "Время входящих: " + QString::number(it->second->getIncomingTime()) + "; "
                                                 "Исходящих звонков: " + QString::number(it->second->getOutgoingTime()) + ".");
                    ui->listWidget_user->item(ui->listWidget_user->count()-1)->setData(Qt::UserRole, it->second->getPhoneNumber());
            }
        } else
        if (sort_win->get_type_sort() == 2)
        {
            for (auto it = user_sort_out_time.begin(); it != user_sort_out_time.end(); it++)
            {
                    ui->listWidget_user->addItem("Номер: " + QString::number(it->second->getPhoneNumber()) + "; "
                                                 "Тип абонента: " + it->second->getTypeSubscriber() + "; "
                                                 "Время входящих: " + QString::number(it->second->getIncomingTime()) + "; "
                                                 "Исходящих звонков: " + QString::number(it->second->getOutgoingTime()) + ".");
                    ui->listWidget_user->item(ui->listWidget_user->count()-1)->setData(Qt::UserRole, it->second->getPhoneNumber());
            }
        }
    } else
    if (sort_win->get_type_filter() == 1)
    {
        for (auto it = user_sort_number.begin(); it != user_sort_number.end(); it++)
        {
            if ((it->second->getTypeSubscriber() == "физ") && (it->second->getSpecParam(3).toDouble() < 0))
            {
                ui->listWidget_user->addItem("Номер: " + QString::number(it->second->getPhoneNumber()) + "; "
                                             "Баланс: " + it->second->getSpecParam(3) + ".");
                ui->listWidget_user->item(ui->listWidget_user->count()-1)->setData(Qt::UserRole, it->second->getPhoneNumber());
            }
        }
    } else
    if (sort_win->get_type_filter() == 2)
    {
        for (auto it = user_sort_number.begin(); it != user_sort_number.end(); it++)
        {
            if ((it->second->getTypeSubscriber() == "юр") && (it->second->getSpecParam(2) == sort_win->get_value_filter_2()))
            {
                ui->listWidget_user->addItem("Номер: " + QString::number(it->second->getPhoneNumber()) + "; "
                                             "Название организации: " + it->second->getSpecParam(2) + ".");
                ui->listWidget_user->item(ui->listWidget_user->count()-1)->setData(Qt::UserRole, it->second->getPhoneNumber());
            }
        }
    }
}


void MainWindow::on_pushButton_add_clicked()
{
    AddUserWindow inp_win;
    inp_win.setModal(true);
    inp_win.exec();
    MobileSub * inp_user = inp_win.get_input();
    if (inp_user != 0)
    {
        if ((user_sort_number.size() == 0) || (user_sort_number.find(inp_user->getPhoneNumber()) == user_sort_number.end()))
        {
            user_sort_number.emplace(inp_user->getPhoneNumber(), inp_user);
            user_sort_inp_time.emplace(inp_user->getIncomingTime(), inp_user);
            user_sort_out_time.emplace(inp_user->getOutgoingTime(), inp_user);
            update_list();
        } else
        {
            QMessageBox::warning(this, "Ошибка добавления нового пользователя", "Пользователь с данным номером уже существует.");
            delete inp_user;
        }
    }
}


void MainWindow::on_pushButton_edit_clicked()
{
    if (ui->listWidget_user->selectedItems().size() == 0)
    {
        QMessageBox::information(this, "Редактирование информации абонента", "Чтобы редактировать информацию абонента, нужно выделить его, используя мышку.");
        return;
    }
    unsigned long long user_edit_num = ui->listWidget_user->currentItem()->data(Qt::UserRole).toULongLong();
    qDebug() << user_edit_num;
    auto user_edit_it = user_sort_number.find(user_edit_num);
    if (user_edit_it == user_sort_number.end()) return;
    AddUserWindow inp_win;
    inp_win.setModal(true);
    inp_win.set_input(user_edit_it->second);
    inp_win.exec();
    update_list();
}


void MainWindow::on_pushButton_delete_clicked()
{
    if (ui->listWidget_user->selectedItems().size() == 0)
    {
        QMessageBox::information(this, "Удаление абонента", "Чтобы удалить абонента, нужно выделить его, используя мышку.");
        return;
    }
    unsigned long long user_edit_num = ui->listWidget_user->currentItem()->data(Qt::UserRole).toULongLong();
    if (user_sort_number.find(user_edit_num) != user_sort_number.end())
    {
        for (auto it = user_sort_inp_time.begin(); it != user_sort_inp_time.end(); it++)
            if (it->second->getPhoneNumber() == user_edit_num)
            {
                user_sort_inp_time.erase(it);
                break;
            }
        for (auto it = user_sort_out_time.begin(); it != user_sort_out_time.end(); it++)
            if (it->second->getPhoneNumber() == user_edit_num)
            {
                user_sort_out_time.erase(it);
                break;
            }
        delete user_sort_number[user_edit_num];
        user_sort_number.erase(user_edit_num);
        update_list();
    }
}


void MainWindow::on_pushButton_info_clicked()
{
    if (ui->listWidget_user->selectedItems().size() == 0)
    {
        QMessageBox::information(this, "Информация абонента", "Чтобы посмотреть информацию абонента, нужно выделить его, используя мышку. ");
        return;
    }
    unsigned long long user_edit_num = ui->listWidget_user->currentItem()->data(Qt::UserRole).toULongLong();
    auto user_edit_it = user_sort_number.find(user_edit_num);
    if (user_edit_it == user_sort_number.end()) return;
    QMessageBox::information(this, "Информация абонента", user_edit_it->second->getTextOut());
}


void MainWindow::on_pushButton_sort_clicked()
{
    sort_win->exec();
    update_list();
}


void MainWindow::on_pushButton_open_file_clicked()
{
    QString name_file = QFileDialog::getOpenFileName(this, "Открыть файл", QDir::currentPath(),"*.txt");
    if (name_file.size() == 0) return;
    QFile qfile(name_file);
    if (!qfile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Ошибка чтения файла", "Файл или недоступен или не существует.");
        return;
    }
    QTextStream file(&qfile);
    QString type;
    MobileSub *newUser = 0;
    if (qfile.isOpen())
    {
        while (!file.atEnd())
        {
            file >> type;
            QString text_error;
            if ((type == "юридическое_лицо") || (type == "юр") || (type == "1")) newUser = new LegalEntityMobSub; else
            if ((type == "физическое_лицо") || (type == "физ") || (type == "2")) newUser = new IndividualMobSub; else
            if ((type == "собственный_сотрудник") || (type == "сотрудник") || (type == "3")) newUser = new EmployeeMobSub; else
                newUser = new MobileSub;
            if (newUser->inp(&file, &text_error))
            {
                if (user_sort_number.find(newUser->getPhoneNumber()) != user_sort_number.end())
                {
                    delete newUser;
                    QMessageBox::warning(this, "Ошибка чтения файла", "В файле записан абонент с номером, который уже существует в базе данных. ");
                    return;
                } else
                {
                    user_sort_number.emplace(newUser->getPhoneNumber(), newUser);
                    user_sort_inp_time.emplace(newUser->getIncomingTime(), newUser);
                    user_sort_out_time.emplace(newUser->getOutgoingTime(), newUser);
                }
            } else
            {
                QMessageBox::warning(this, "Ошибка чтения файла", "При чтении файла произошла ошибка. " + text_error);
                delete newUser;
                return;
            }
        }
        qfile.close();
        update_list();
    } else
    {
        QMessageBox::warning(this, "Ошибка чтения файла", "Программа не смогла обнаружить файл базы данных.");
    }
}
