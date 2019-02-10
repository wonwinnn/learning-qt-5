#include <QApplication>
#include <QTableWidget>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QItemSelection>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTableWidget tableWidget(8, 4);
    QItemSelectionModel *selectionModel = tableWidget.selectionModel();
    QModelIndex topLeft = tableWidget.model()->index(0, 0, QModelIndex());
    QModelIndex bottomRight = tableWidget.model()->index(5, 2, QModelIndex());
    QItemSelection selection(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::Select);

    tableWidget.show();

    return a.exec();
}
