#ifndef TRACKINGURL_H
#define TRACKINGURL_H
#include <QVector>
#include <QString>
#include <QObject>

#define URL_GAT "http://www.google-analytics.com/__utm.gif"
class TrackingURL
{
public:
    TrackingURL();
    void addParameter(QString key, QString value);
    void removeParameter(QString key);
    QString getParameter(QString key);
    QString getURL();
    int size();
    bool equals(QObject obj);
    int hashCode();
    QString toString();
    QString queryString();

private:
    QVector<QString> keys;
    QVector<QString> values;
};

#endif // TRACKINGURL_H
