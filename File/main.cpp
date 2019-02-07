#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*QFile file("in.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open file failed.";
        return -1;
    } else {
        while (!file.atEnd()) {
            qDebug() << file.readLine();
        }
    }

    QFileInfo info(file);
    qDebug() << info.isDir();
    qDebug() << info.isExecutable();
    qDebug() << info.baseName();
    qDebug() << info.completeBaseName();
    qDebug() << info.suffix();
    qDebug() << info.completeSuffix();*/

    QFile file("file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << QString("the answer is");
    out << (qint32)42;
    file.close();

    //QFile file("file.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    QString str;
    qint32 a;
    in >> str >> a;
    qDebug() << str << a;

    /*QFile file("file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    // 写入魔术数字和版本
    out << (quint32)0xA0B0C0D0;
    out << (qint32)123;

    out.setVersion(QDataStream::Qt_4_0);

    // 写入数据
    out << QString("Data");

    file.close();

    //QFile file("file.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    // 检查魔术数字
    quint32 magic;
    in >> magic;
    if (magic != 0xA0B0C0D0) {
        //return BAD_FILE_FORMAT;
        return 0;
    }

    // 检查版本
    qint32 version;
    in >> version;
    if (version < 100) {
        //return BAD_FILE_TOO_OLD;
        return 0;
    }
    if (version > 123) {
        //return BAD_FILE_TOO_NEW;
        return 0;
    }

    // 读取数据
    QString str;
    in >> str;
    qDebug() << str;*/

    /*QFile file("file.dat");
    file.open(QIODevice::ReadWrite);

    QDataStream stream(&file);
    QString str = "the answer is 42";
    QString strout;

    stream << str;
    file.flush();
    stream.device()->seek(0);
    stream >> strout;
    qDebug() << strout;*/

    /*QFile data("file.txt");
    if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&data);
        out << "The answer is " << 42;
    }


    data.close();

    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        QString str;
        int ans = 0;
        in >> str >> ans;
        qDebug() << str;
    }*/

    return app.exec();
}
