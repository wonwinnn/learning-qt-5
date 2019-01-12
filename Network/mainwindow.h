#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QMessageBox>
#include <QNetworkReply>
#include <QDebug>
#include <QMap>
#include <QList>

#include "weather.h"

enum RemoteRequest {
    FetchWeatherInfo,
    FetchWeatherIcon
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    class Private;
    friend class Private;
    Private *d;
};

class MainWindow::Private
{
public:
    Private()
    {
        netWorker = NetWorker::instance();
    }

    void fetchWeather(const QString &cityName)
    {
        QNetworkReply *reply = netWorker->get(QString("http://api.openweathermap.org/data/2.5/weather?q=%1&mode=json&units=metric&lang=zh_cn&APPID=6b55db98c0b1a112f1f98bd93e4726ac").arg(cityName));
        replyMap.insert(reply, FetchWeatherInfo);
    }

    void fetchIcon(const QString &iconName)
    {
        QNetworkReply *reply = netWorker->get(QString("http://openweathermap.org/img/w/%1.png").arg(iconName));
        replyMap.insert(reply, FetchWeatherIcon);
    }

    NetWorker *netWorker;
    MainWindow *mainWindow;
    QMap<QNetworkReply *, RemoteRequest> replyMap;

};

#endif // MAINWINDOW_H
