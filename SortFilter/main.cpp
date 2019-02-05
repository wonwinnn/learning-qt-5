#include "sortview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SortView w;
    w.show();

    return a.exec();
}
