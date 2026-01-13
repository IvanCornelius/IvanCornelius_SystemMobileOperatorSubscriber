#include "AddUserWindow.h"
#include "ui_AddUserWindow.h"


AddUserWindow::AddUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserWindow)
{
    ui->setupUi(this);
}


AddUserWindow::~AddUserWindow()
{
    delete ui;
}


void AddUserWindow::set_input(MobileSub * inp)
{
    input = inp;
    if (input != 0)
    {
        ui->lineEdit_number->setEnabled(false);
        ui->lineEdit_number->setText(QString::number(input->getPhoneNumber()));
        ui->doubleSpinBox_time_inp->setValue(input->getIncomingTime());
        ui->doubleSpinBox_time_out->setValue(input->getOutgoingTime());
        if (input->getTypeSubscriber() == "юр")
        {
            ui->tabWidget_type->setCurrentIndex(0);
            ui->tabWidget_type->setTabEnabled(1, false);
            ui->tabWidget_type->setTabEnabled(2, false);
            ui->lineEdit_LEMS_INN->setText(input->getSpecParam(1));
            ui->lineEdit_LEMS_name->setText(input->getSpecParam(2));
            ui->lineEdit_LEMS_addres->setText(input->getSpecParam(3));
        } else
        if (input->getTypeSubscriber() == "физ")
        {
            ui->tabWidget_type->setCurrentIndex(1);
            ui->tabWidget_type->setTabEnabled(0, false);
            ui->tabWidget_type->setTabEnabled(2, false);
            ui->lineEdit_IMS_full_name->setText(input->getSpecParam(1));
            ui->lineEdit_IMS_passport_data->setText(input->getSpecParam(2));
            ui->doubleSpinBox_IMS_balance->setValue(input->getSpecParam(3).toDouble());
        } else
        if (input->getTypeSubscriber() == "сотрудник")
        {
            ui->tabWidget_type->setCurrentIndex(2);
            ui->tabWidget_type->setTabEnabled(0, false);
            ui->tabWidget_type->setTabEnabled(1, false);
            ui->lineEdit_EMS_full_name->setText(input->getSpecParam(1));
            ui->spinBox_EMS_service_number->setValue(input->getSpecParam(2).toLongLong());
        }
    }
}


MobileSub *AddUserWindow::get_input()
{
    return input;
}


void AddUserWindow::on_pushButton_save_clicked()
{
    //проверка ввода на наличие ошибок
    bool ok = true;
    if (ui->tabWidget_type->currentIndex() == 0)
    {
        ui->lineEdit_LEMS_INN->text().toLongLong(&ok);
        if (!ok || (ui->lineEdit_LEMS_INN->text().size() != 11))
        {
            QMessageBox::warning(this, "Ошибка ввода ИНН", "ИНН должен содержать 11 цифр. ");
            return;
        }
    }
    unsigned long long number = ui->lineEdit_number->text().toULongLong(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Ошибка ввода номера телефона", "Номер телефона должен быть целым положительным числом. ");
        return;
    }
    if (ui->doubleSpinBox_time_inp->value() < 0)
    {
        QMessageBox::warning(this, "Ошибка ввода времени входящих звонков", "Время должно неотрицательным. ");
        return;
    }
    if (ui->doubleSpinBox_time_out->value() < 0)
    {
        QMessageBox::warning(this, "Ошибка ввода времени исходящих звонков", "Время должно неотрицательным. ");
        return;
    }
    //создание класса
    if (input == 0)
    {
        if (ui->tabWidget_type->currentIndex() == 0) input = new LegalEntityMobSub; else
        if (ui->tabWidget_type->currentIndex() == 1) input = new IndividualMobSub; else
        if (ui->tabWidget_type->currentIndex() == 2) input = new EmployeeMobSub; else return;
    }
    //ввод общих параметров
    input->setPhoneNumber(number);
    input->setIncomingTime(ui->doubleSpinBox_time_inp->value());
    input->setOutgoingTime(ui->doubleSpinBox_time_out->value());
    //ввод специальных параметров
    //юр
    if (ui->tabWidget_type->currentIndex() == 0)
    {
        input->setSpecParam(1, ui->lineEdit_LEMS_INN->text());
        input->setSpecParam(2, ui->lineEdit_LEMS_name->text());
        input->setSpecParam(3, ui->lineEdit_LEMS_addres->text());
    } else
    //физ
    if (ui->tabWidget_type->currentIndex() == 1)
    {
        input->setSpecParam(1, ui->lineEdit_IMS_full_name->text());
        input->setSpecParam(2, ui->lineEdit_IMS_passport_data->text());
        input->setSpecParam(3, ui->doubleSpinBox_IMS_balance->text());
    } else
    //сотрудник
    if (ui->tabWidget_type->currentIndex() == 2)
    {
        input->setSpecParam(1, ui->lineEdit_EMS_full_name->text());
        input->setSpecParam(2, ui->spinBox_EMS_service_number->text());
    }
    //закрытие окна
    this->hide();
}
