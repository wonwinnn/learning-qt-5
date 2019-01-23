#include <QApplication>
#include <QJsonDocument>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString json("{"
            "\"encoding\" : \"UTF-8\","
            "\"plug-ins\" : ["
            "\"python\","
            "\"c++\","
            "\"ruby\""
            "],"
            "\"indent\" : { \"length\" : 3, \"use_space\" : true }"
            "}");
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject()) {
            QVariantMap result = jsonDocument.toVariant().toMap();
            qDebug() << "encoding:" << result["encoding"].toString();
            qDebug() << "plugins:";

            foreach (QVariant plugin, result["plug-ins"].toList()) {
                qDebug() << "\t-" << plugin.toString();
            }

            QVariantMap nestedMap = result["indent"].toMap();
            qDebug() << "length:" << nestedMap["length"].toInt();
            qDebug() << "use_space:" << nestedMap["use_space"].toBool();
        }
    } else {
        qFatal(error.errorString().toUtf8().constData());
        exit(1);
    }

    return a.exec();
}
