#include "filesystemwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileSystemWidget w;
    w.show();

    return a.exec();
}
