//заголовочные файлы
#include "MainWindow.h"
#include <QApplication>

//программа
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
