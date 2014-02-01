#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QDateTime>
#include "trackingurl.h"

class Request//: QObject
{
    //Q_OBJECT

public:
//    Q_PROPERTY(QString appID WRITE setAppID)
//    Q_PROPERTY(int userID WRITE setUserID)
//    Q_PROPERTY(QDateTime firstVisit WRITE setFirstVisit)
//    Q_PROPERTY(QDateTime lastVisit WRITE setLastVisit)
//    Q_PROPERTY(QDateTime currentVisit WRITE setCurrentVisit)
//    Q_PROPERTY(int screenWidth WRITE setScreenWidth)
//    Q_PROPERTY(int screenHeight WRITE setScreenHeight)
    QString appID() { return _appID; }
    QString userID() { return QString::number(_userID); }
    QDateTime firstVisit() { return _firstVisit; }
    QDateTime lastVisit() { return _lastVisit; }
    QDateTime currentVisit() { return _currentVisit; }
    int screenWidth() { return _screenWidth; }
    int screenHeight() { return _screenHeight; }
public:
    Request();
public:
    void setAppID(const QString &appID);
    void setUserID(int userID);
    void setFirstVisit(const QDateTime &timestamp);
    void setLastVisit(const QDateTime &timestamp);
    void setCurrentVisit(const QDateTime &timestamp);
    void setScreenWidth(int w);
    void setScreenHeight(int h);
    QString getCookie();
    virtual TrackingURL trackingURL();
    virtual void clone(Request* r);
    virtual Request* clone();

private:
    QString _appID;
    int _userID;
    QDateTime _firstVisit;
    QDateTime _lastVisit;
    QDateTime _currentVisit;
    int _screenWidth;
    int _screenHeight;
};

#endif // REQUEST_H
