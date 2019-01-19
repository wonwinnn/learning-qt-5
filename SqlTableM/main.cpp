#include <QApplication>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

bool connect(const QString &dbName);

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    //SELECT
    if (connect("demo.db")) {
        QSqlTableModel model;
        model.setTable("student");
        model.setFilter("age > 20 and age < 25");
        if (model.select()) {
            for (int i = 0; i < model.rowCount(); ++i) {
                QSqlRecord record = model.record(i);
                QString name = record.value("name").toString();
                int age = record.value("age").toInt();
                qDebug() << name << ": " << age;
            }
        }
    } else {
        return 1;
    }

    //INSERT INTO
    /*if (connect("demo.db")) {
        QSqlTableModel model;
        model.setTable("student");
        int row = 0;
        model.insertRows(row, 1);
        model.setData(model.index(row, 1), "Cheng");
        model.setData(model.index(row, 2), 24);
        model.submitAll();
    } else {
        return 1;
    }*/

    //UPDATE
    /*if (connect("demo.db")) {
        QSqlTableModel model;
        model.setTable("student");
        model.setFilter("age = 25");
        if (model.select()) {
            if (model.rowCount() == 1) {
                QSqlRecord record = model.record(0);
                record.setValue("age", 26);
                model.setRecord(0, record);
                model.submitAll();
            }
        }
    } else {
        return 1;
    }*/

    //DELETE
    /*if (connect("demo.db")) {
        QSqlTableModel model;
        model.setTable("student");
        model.setFilter("age = 26");
        if (model.select()) {
            if (model.rowCount() == 1) {
                model.removeRows(0, 1);
                model.submitAll();
            }
        }
    } else {
        return 1;
    }*/

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
