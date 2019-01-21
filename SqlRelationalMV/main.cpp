#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QTableView>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QtSql>

bool connect(const QString &dbName);

enum ColumnIndex
{
    StudentID = 0,
    ColumnID_Name = 1,
    ColumnID_Age = 2,
    ColumnID_City = 3
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (connect("demo.db")) {
        QSqlQuery query;
        query.exec(QString("PRAGMA foreign_keys = ON;")); //enable foreign key
        query.exec(QString("CREATE TABLE city ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "name VARCHAR)"));
        query.prepare("INSERT INTO city (name) VALUES (?)");
        QVariantList citynames;
        citynames << "Beijing" << "Shanghai" << "Nanjing" << "Tianjin" << "Wuhan"
                  << "Hangzhou" << "Suzhou" << "Guagnzhou";
        query.addBindValue(citynames);
        query.execBatch(); //!!!

        query.exec(QString("CREATE TABLE student ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "name VARCHAR,"
                               "age INTEGER,"
                               "address INTEGER,"
                               "FOREIGN KEY(address) REFERENCES city(id))"));
        query.prepare("INSERT INTO student (name, age, address) VALUES (?, ?, ?)");
        QVariantList stunames;
        stunames << "Tom" << "Jack" << "Jane" << "Jerry";
        query.addBindValue(stunames);
        QVariantList ages;
        ages << 20 << 23 << 22 << 25;
        query.addBindValue(ages);
        QVariantList addresses;
        addresses << 1 << 2 << 3 << 7;
        query.addBindValue(addresses);
        query.execBatch(); //!!!

        QSqlRelationalTableModel *model = new QSqlRelationalTableModel;
        model->setTable("student");
        //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setSort(StudentID, Qt::AscendingOrder);
        model->setHeaderData(ColumnID_Name, Qt::Horizontal, "Name");
        model->setHeaderData(ColumnID_Age, Qt::Horizontal, "Age");
        model->setHeaderData(ColumnID_City, Qt::Horizontal, "City");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setRelation(ColumnID_City, QSqlRelation("city", "id", "name"));
        model->select();

        QTableView *view = new QTableView;
        view->setModel(model);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->resizeColumnsToContents();
        view->setItemDelegate(new QSqlRelationalDelegate(view));

        QHeaderView *header = view->horizontalHeader();
        header->setStretchLastSection(true);

        view->show();

        if (!query.execBatch()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  query.lastError().text());
        }

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


