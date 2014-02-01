#ifndef TRACKER_H
#define TRACKER_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QMutex>
#include <QTimer>
#include <QDateTime>
//#include <QSystemInfo>
#include <QtGui/QApplication>
#include "request.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>


class Tracker : public QObject {
    Q_OBJECT
public:
    static Tracker* getInstance(/*QApplication *app, */QString appId);
    static Tracker* getInstance(/*QApplication *app, */QString appId, long flushInterval);
    Tracker(/*QApplication *app, */QString appId, long flushInterval);
    int randInt(int high);
    void track(Request &request);
    void addToQueue(Request &request);
    int queueSize();
    void flush(bool asynchronously);
    void processQueue();
    void process(Request &request);
    void runTask(long delay);
    void fillRequestParams(Request &request);
    void loadCookie();
    QString getUserAgent();
private:
    Q_DISABLE_COPY(Tracker)
private Q_SLOTS:
    void log();
    void runTask();
    void replyFinished(QNetworkReply* reply);
public:
    Q_INVOKABLE void trackPage(QString page);
    Q_INVOKABLE void trackEvent(QString event);
private:
    static QMap<QString,Tracker*> trackerPool;
    QNetworkAccessManager *manager;
    QString appId;
    QVector<Request*> queue;
    QTimer *timer;
    //Task task;
    long flushInterval;
    int userId;
    qlonglong firstVisitTimestamp;
    qlonglong lastVisitTimestamp;
    qlonglong currentVisitTimestamp;
    QMutex lock;
//    QApplication* app
    //QSystemDeviceInfo sysInfo;
};

#endif // TRACKER_H
