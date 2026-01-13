#ifndef MAINWINDOW_H
#define MAINWINDOW_H


//заголовочные файлы
#include <map>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include "AddUserWindow.h"
#include "SortUserWindow.h"
#include "MobileSub.h"
#include "LegalEntityMobSub.h"
#include "IndividualMobSub.h"
#include "EmployeeMobSub.h"


//пространство имён
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


//класс для создания главного окна
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update_list();
private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_edit_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_info_clicked();
    void on_pushButton_sort_clicked();
    void on_pushButton_open_file_clicked();
private:
    Ui::MainWindow *ui;
    SortUserWindow *sort_win;
    std::map <unsigned long long, MobileSub *> user_sort_number; // пользователь сортированный по номеру телефона
    std::multimap <double, MobileSub *> user_sort_inp_time;      // пользователь сортированный по времени входящих звонков
    std::multimap <double, MobileSub *> user_sort_out_time;      // пользователь сортированный по вермени исходящих звонков
};
#endif // MAINWINDOW_H
