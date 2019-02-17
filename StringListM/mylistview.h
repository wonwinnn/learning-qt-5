#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H
#include <QWidget>
#include <QStringListModel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListView>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <spinboxdelegate.h>



class MyListView : public QWidget
{
    Q_OBJECT
public:
    MyListView(QWidget *parent = 0);
public slots:
    void insertData();
    void deleteData();
    void showData();
private:
    QStringListModel *model;
    QListView *listView;
};

#endif // MYLISTVIEW_H
