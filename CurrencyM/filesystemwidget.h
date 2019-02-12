#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>

class FileSystemWidget : public QWidget
{
    Q_OBJECT
public:
    FileSystemWidget(QWidget *parent = 0);
public slots:
    void mkdir();
    void rm();
private:
    QFileSystemModel *model;
    QTreeView *treeView;
};

#endif // FILESYSTEMWIDGET_H
