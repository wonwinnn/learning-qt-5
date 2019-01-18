#include <QApplication>
#include <QObject>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

bool connect(const QString &dbName);
bool isTableExist(QSqlQuery &q, QString &tbName);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString tbName = "student";

    if (connect("demo.db")) {
        QSqlQuery query;
        if(!isTableExist(query, tbName)){
            if (!query.exec(QString("CREATE TABLE %1 ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "name VARCHAR,"
                            "age INT)").arg(tbName))) {
                QMessageBox::critical(0, QObject::tr("Database Error"),
                                      query.lastError().text());
                return 1;
            }

            query.prepare("INSERT INTO student (name, age) VALUES (?, ?)");
            QVariantList names;
            names << "Tom" << "Jack" << "Jane" << "Jerry";
            query.addBindValue(names);
            QVariantList ages;
            ages << 20 << 23 << 22 << 25;
            query.addBindValue(ages);
            qDebug() << "Create table" << tbName;

            if (!query.execBatch()) {
                QMessageBox::critical(0, QObject::tr("Database Error"),
                                      query.lastError().text());
            }
        }

        query.finish();
        query.exec("SELECT name, age FROM student");
        while (query.next()) {
            QString name = query.value(0).toString();
            int age = query.value(1).toInt();
            qDebug() << name << ": " << age;
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

bool isTableExist(QSqlQuery &q, QString &tbName)
{
     q.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(tbName));
     if(q.next()){
        if(q.value(0).toInt()==0){
            qDebug() << "Table" << tbName << "doesn't exist";
            return false; // 表不存在
        }else{
            qDebug() << "Table" << tbName << "exists";
            return true; //表存在
        }
    }
}


