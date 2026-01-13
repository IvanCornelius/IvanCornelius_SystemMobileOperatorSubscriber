#include "SortUserWindow.h"
#include "ui_SortUserWindow.h"


SortUserWindow::SortUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortUserWindow)
{
    ui->setupUi(this);
    ui->lineEdit_value_filter->hide();
}


SortUserWindow::~SortUserWindow()
{
    delete ui;
}


int SortUserWindow::get_type_sort()
{
    return ui->comboBox_type_sort->currentIndex();
}


int SortUserWindow::get_type_filter()
{
    return ui->comboBox_type_filter->currentIndex();
}


QString SortUserWindow::get_value_filter_2()
{
    return ui->lineEdit_value_filter->text();
}


void SortUserWindow::on_pushButton_save_clicked()
{
    this->hide();
}


void SortUserWindow::on_comboBox_type_filter_activated(int index)
{
    if (index != 0)
        ui->comboBox_type_sort->setEnabled(false);
    else
        ui->comboBox_type_sort->setEnabled(true);
    if (index == 2)
        ui->lineEdit_value_filter->show();
    else
        ui->lineEdit_value_filter->hide();
}
