#include "mainwindow.h"
#include "weather.h"
#include <QApplication>

QDebug operator <<(QDebug dbg, const WeatherDetail &w);
QDebug operator <<(QDebug dbg, const WeatherInfo &w);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

QDebug operator <<(QDebug dbg, const WeatherDetail &w)
{
    dbg.nospace() << "("
                  << "Description: " << w.desc() << "; "
                  << "Icon: " << w.icon()
                  << ")";
    return dbg.space();
}

QDebug operator <<(QDebug dbg, const WeatherInfo &w)
{
    dbg.nospace() << "("
                  << "id: " << w.id() << "; "
                  << "City name: " << w.cityName() << "; "
                  << "Date time: " << w.dateTime().toString(Qt::DefaultLocaleLongDate) << ": " << endl
                  << "Temperature: " << w.temperature() << ", "
                  << "Pressure: " << w.pressure() << ", "
                  << "Humidity: " << w.humidity() << endl
                  << "Details: [";
    foreach (WeatherDetail *detail, w.details()) {
        dbg.nospace() << "( Description: " << detail->desc() << ", "
                      << "Icon: " << detail->icon() << "), ";
    }
    dbg.nospace() << "] )";
    return dbg.space();
}
