#include "mainwindow.h"
#include <QTableWidgetItem>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    topTable = new DataTableWidget(this);
    QStringList headers;
    headers << "ID" << "Name" << "Age";
    topTable->setHorizontalHeaderLabels(headers);
    topTable->setItem(0, 0, new QTableWidgetItem(QString("0001")));
    topTable->setItem(0, 1, new QTableWidgetItem(QString("Anna")));
    topTable->setItem(0, 2, new QTableWidgetItem(QString("20")));
    topTable->setItem(1, 0, new QTableWidgetItem(QString("0002")));
    topTable->setItem(1, 1, new QTableWidgetItem(QString("Tommy")));
    topTable->setItem(1, 2, new QTableWidgetItem(QString("21")));
    topTable->setItem(2, 0, new QTableWidgetItem(QString("0003")));
    topTable->setItem(2, 1, new QTableWidgetItem(QString("Jim")));
    topTable->setItem(2, 2, new QTableWidgetItem(QString("21")));
    topTable->setItem(3, 0, new QTableWidgetItem(QString("0004")));
    topTable->setItem(3, 1, new QTableWidgetItem(QString("Dick")));
    topTable->setItem(3, 2, new QTableWidgetItem(QString("24")));
    topTable->setItem(4, 0, new QTableWidgetItem(QString("0005")));
    topTable->setItem(4, 1, new QTableWidgetItem(QString("Tim")));
    topTable->setItem(4, 2, new QTableWidgetItem(QString("22")));

    bottomTable = new DataTableWidget(this);

    QWidget *content = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(content);
    layout->addWidget(topTable);
    layout->addWidget(bottomTable);

    setCentralWidget(content);

    setWindowTitle("Data Table");
}

MainWindow::~MainWindow()
{

}
