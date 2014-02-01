#include "trackingurl.h"
#include <QHash>
#include <QLocale>

TrackingURL::TrackingURL()//:keys(15),values(15)
{
    addParameter("utmwv", "5.1.7");
    addParameter("utmn", QString::number(qrand()));
    //default encoding
    addParameter("utmcs", "UTF-8");
    //System locale
    //addParameter("utmul",QLocale::system().bcp47Name());
    addParameter("utmul",QLocale::system().name());
    //addParameter("utmul","en-us");

    addParameter("utmje", "1");
    addParameter("utmdt", "");
    addParameter("utmhn", "localhost");
    addParameter("utmr", "");
    addParameter("utmt", "");
    addParameter("utme", "");
    addParameter("utmp", "");
}

void TrackingURL::addParameter(QString key, QString value) {
    if (keys.contains(key)) {
        values.replace(keys.indexOf(key),value);
    } else {
        keys.append(key);
        values.append(value);
    }
}

void TrackingURL::removeParameter(QString key) {
    if (keys.contains(key)) {
        int ix = keys.indexOf(key);
        //
        values.remove(ix);
        keys.remove(ix);
    }
}

QString TrackingURL::getParameter(QString key) {
    if (keys.contains(key)) {
        int ix = keys.indexOf(key);
        //
        return (QString)values[ix];
    } else {
        return "";
    }
}

QString TrackingURL::getURL() {
    QString url(URL_GAT);
    return url + "?" + queryString();
}

int TrackingURL::size() {
    return keys.size();
}

bool TrackingURL::equals(QObject obj) {
//    if (this == obj) {
//        return true;
//    } else if (obj == null || !(obj instanceof TrackingURL)) {
//        return false;
//    } else {
//        return toString().equals(obj.toString());
//    }
    return false;
}
int TrackingURL::hashCode() {
    return qHash(getURL());
}

QString TrackingURL::toString() {
    return getURL();
}
QString TrackingURL::queryString() {
    //TODO: should use QStringBuilder but incompatible between 4.7 and 4.8 use
    QString query;
    int size = keys.size();
    QString key;
    QString value;
    //
    for (int i = 0; i < size; i++) {
        key = (QString)keys[i];
        value = (QString)values[i];
        //
        if (!key.isEmpty() && !value.isEmpty()) {
            query += key;
            query += "=";
            query += value;
            query += "&";
        }
    }
    if (query.endsWith("&")) {
        query = query.remove(query.length() -1,1);
    }
    //
    return query;
}
