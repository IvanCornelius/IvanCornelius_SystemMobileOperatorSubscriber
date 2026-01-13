#ifndef SORTUSERWINDOW_H
#define SORTUSERWINDOW_H

//заголовочные файлы
#include <QDialog>


//пространство имён
namespace Ui {
class SortUserWindow;
}


//класс для окна сортировки
class SortUserWindow : public QDialog
{
    Q_OBJECT
public:
    explicit SortUserWindow(QWidget *parent = nullptr);
    ~SortUserWindow();
    int get_type_sort();
    int get_type_filter();
    QString get_value_filter_2();
private slots:
    void on_pushButton_save_clicked();
    void on_comboBox_type_filter_activated(int index);
private:
    Ui::SortUserWindow *ui;
};

#endif
