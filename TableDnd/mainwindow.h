#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datatablewidget.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    DataTableWidget *topTable;
    DataTableWidget *bottomTable;
};

#endif // MAINWINDOW_H
