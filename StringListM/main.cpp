#include "mainwindow.h"
#include "mylistview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyListView w;
    w.show();

    return a.exec();
}
