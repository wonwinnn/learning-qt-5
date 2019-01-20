#include <QApplication>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QTableView>
#include <QAbstractItemView>
#include <QHeaderView>

bool connect(const QString &dbName);

enum ColumnIndex
{
    Column_ID = 0,
    Column_Name = 1,
    Column_Age = 2
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (connect("demo.db")) {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable("student");
        model->setSort(Column_Name, Qt::AscendingOrder);
        model->setHeaderData(Column_Name, Qt::Horizontal, "Name");
        model->setHeaderData(Column_Age, Qt::Horizontal, "Age");
        model->select();

        QTableView *view = new QTableView;
        view->setModel(model);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
//        view->setColumnHidden(Column_ID, true);
        view->resizeColumnsToContents();
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);

        QHeaderView *header = view->horizontalHeader();
        header->setStretchLastSection(true);

        view->show();
    } else {
        return 1;
    }
    return a.exec();
}


bool connect(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
        return false;
    }
    return true;
}
