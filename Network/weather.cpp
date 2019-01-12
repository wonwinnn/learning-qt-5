#include "weather.h"

NetWorker *NetWorker::instance()
{
    static NetWorker netWorker;
    return &netWorker;
}

NetWorker::NetWorker(QObject *parent) :
    QObject(parent),
    d(new NetWorker::Private(this))
{
    connect(d->manager, &QNetworkAccessManager::finished,
            this, &NetWorker::finished);
}

NetWorker::~NetWorker()
{
    delete d;
    d = 0;
}

QNetworkReply * NetWorker::get(const QString &url)
{
    return d->manager->get(QNetworkRequest(QUrl(url)));
}

WeatherDetail::WeatherDetail() : d(new Private(this))
{
}

WeatherDetail::~WeatherDetail()
{
    delete d;
    d = 0;
}

QString WeatherDetail::desc() const
{
    return d->m_desc;
}

void WeatherDetail::setDesc(const QString &desc)
{
    d->m_desc = desc;
}

QString WeatherDetail::icon() const
{
    return d->m_icon;
}

void WeatherDetail::setIcon(const QString &icon)
{
    d->m_icon = icon;
}

WeatherInfo::WeatherInfo() : d(new Private(this))
{
}

WeatherInfo::~WeatherInfo()
{
    delete d;
    d = 0;
}

QString WeatherInfo::cityName() const
{
    return d->m_cityName;
}

void WeatherInfo::setCityName(const QString &cityName)
{
    d->m_cityName = cityName;
}

quint32 WeatherInfo::id() const
{
    return d->m_id;
}

void WeatherInfo::setId(quint32 id)
{
    d->m_id = id;
}

QDateTime WeatherInfo::dateTime() const
{
    return d->m_dateTime;
}

void WeatherInfo::setDateTime(const QDateTime &dateTime)
{
    d->m_dateTime = dateTime;
}

float WeatherInfo::temperature() const
{
    return d->m_temperature;
}

void WeatherInfo::setTemperature(float temperature)
{
    d->m_temperature = temperature;
}

float WeatherInfo::humidity() const
{
    return d->m_humidity;
}

void WeatherInfo::setHumidity(float humidity)
{
    d->m_humidity = humidity;
}

float WeatherInfo::pressure() const
{
    return d->m_pressure;
}

void WeatherInfo::setPressure(float pressure)
{
    d->m_pressure = pressure;
}

QList<WeatherDetail *> WeatherInfo::details() const
{
    return d->m_details;
}

void WeatherInfo::setDetails(const QList<WeatherDetail *> details)
{
    d->m_details = details;
}



