#include <QApplication>
#include <QDebug>
#include <QDirModel>
#include <QFileSystemModel>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*QFileSystemModel建立之后，直接调用rowCount时返回零，因为它使用一个单独的线程来填充树。
     * 当树被填充之后，才能正确地返回rowCount。而QDir没有多线程，可以正确返回已填充的树rowCount。
     * 缺点在于阻塞式地执行，程序会有一段时间的“假死”，特别是如果文件夹层级很多的时候，卡顿会很明显。*/
    QDirModel*model = new QDirModel;
    //QFileSystemModel *model = new QFileSystemModel;
    QModelIndex parentIndex = model->index(QDir::currentPath());
    int numRows = model->rowCount(parentIndex);

    for (int row = 0; row < numRows; ++row){
        QModelIndex index = model->index(row, 0, parentIndex);
        QString text = model->data(index, Qt::DisplayRole).toString();
        qDebug() << text;
    }

    a.exit();

}
