#ifndef ADDUSERWINDOW_H
#define ADDUSERWINDOW_H


//заголовочные файлы
#include <QDialog>
#include <QMessageBox>
#include "MobileSub.h"
#include "EmployeeMobSub.h"
#include "IndividualMobSub.h"
#include "LegalEntityMobSub.h"


//пространство имён
namespace Ui {
class AddUserWindow;
}


//класс для добавления абонента
class AddUserWindow : public QDialog
{
    Q_OBJECT
public:
    explicit AddUserWindow(QWidget *parent = nullptr);
    ~AddUserWindow();
    void set_input(MobileSub *); //указать пользователя для редактирования
    MobileSub * get_input();     //получить редактированного или заполненного пользователя
private slots:
    void on_pushButton_save_clicked();
private:
    Ui::AddUserWindow *ui;
    MobileSub * input;
};

#endif
