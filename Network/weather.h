#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>

class QNetworkReply;

class NetWorker : public QObject
{
    Q_OBJECT
public:
    static NetWorker * instance();
    ~NetWorker();

    QNetworkReply *get(const QString &url);
signals:
    void finished(QNetworkReply *reply);
private:
    class Private;
    friend class Private;
    Private *d;

    explicit NetWorker(QObject *parent = 0);
    NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;
    NetWorker& operator=(NetWorker rhs) Q_DECL_EQ_DELETE;
};

class NetWorker::Private
{
public:
    Private(NetWorker *q) :
        manager(new QNetworkAccessManager(q))
    {}

    QNetworkAccessManager *manager;
};

class WeatherDetail
{
public:
    WeatherDetail();
    ~WeatherDetail();

    QString desc() const;
    void setDesc(const QString &desc);

    QString icon() const;
    void setIcon(const QString &icon);

private:
    class Private;
    friend class Private;
    Private *d;
};

class WeatherDetail::Private
{
public:
    Private(WeatherDetail *parent) : q(parent)
    {}
    QString m_desc;
    QString m_icon;
    WeatherDetail *q;
};

class WeatherInfo
{
public:
    WeatherInfo();
    ~WeatherInfo();

    QString cityName() const;
    void setCityName(const QString &cityName);

    quint32 id() const;
    void setId(quint32 id);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &dateTime);

    float temperature() const;
    void setTemperature(float temperature);

    float humidity() const;
    void setHumidity(float humidity);

    float pressure() const;
    void setPressure(float pressure);

    QList<WeatherDetail *> details() const;
    void setDetails(const QList<WeatherDetail *> details);

private:
    class Private;
    friend class Private;
    Private *d;
};

class WeatherInfo::Private
{
public:
    Private(WeatherInfo *parent) : q(parent)
    {}
    QString m_cityName;
    quint32 m_id;
    QDateTime m_dateTime;
    float m_temperature;
    float m_humidity;
    float m_pressure;
    QList<WeatherDetail *> m_details;
    WeatherInfo *q;
};

#endif // WEATHER_H
