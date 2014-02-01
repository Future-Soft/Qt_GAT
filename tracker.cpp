#include "tracker.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QString>
#include <QSettings>
#include <QStringList>
#include "pageview.h"
#include "event.h"

Tracker* Tracker::getInstance(/*QApplication* app,*/
                                    QString appId) {
    return getInstance(/*app, */appId, 60);
}


Tracker* Tracker::getInstance(/*QApplication* app,*/ QString appId,
                                    long flushInterval) {
    //    if (appId.isEmpty()) {
    //        throw new IllegalArgumentException(
    //                    "Application Id must not be empty.");
    //    }
    //
//    if (trackerPool == null) {
//        trackerPool = new Hashtable();
//    }
    //
    Tracker* tracker = NULL;//(Tracker*)trackerPool[appId];
    if (tracker == NULL) {
        tracker = new Tracker(/*app,*/ appId, flushInterval);
        //trackerPool.put(appId, tracker);
    }
    return tracker;
}


Tracker::Tracker(/*QApplication* app, */QString appId, long flushInterval): queue(0)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    timer = new QTimer(this);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    flushInterval *= 1000; //secs to millis.
    //
//    this->app = app;
    this->appId = appId;
    this->flushInterval = flushInterval;
    this->currentVisitTimestamp = QDateTime::currentMSecsSinceEpoch();
    //
    loadCookie();
    //
    connect(timer, SIGNAL(timeout()), this, SLOT(runTask()));
    //
    if (flushInterval > 0) {
        //qDebug() << timer->isActive();
        timer->start(flushInterval);
        //qDebug() << timer->isActive();
    }
}

int Tracker::randInt(int high)
{

    // Random number between low and high
    return qrand() % (high);
}

void Tracker::log()
{
    qDebug() << "ABOUT TO QUIT WAS CALLED";
}

void Tracker::trackPage(QString page)
{
    qDebug() << "Tracker::trackPage";
    PageView p(page);
    addToQueue(p);
}

void Tracker::trackEvent(QString event)
{
    //TODO: implement
    //Event e(event);
    //addToQueue(e);
}


void Tracker::track(Request &request) {
    //    if (request == null) {
    //        throw new IllegalArgumentException("Request must not be null.");
    //    }
    //
    fillRequestParams(request);
    //
    //try {
        process(request);
//    } catch (Exception e) {
//        addToQueue(request);
//    }
}


void Tracker::addToQueue(Request &request) {
    //    if (request == null) {
    //        throw new IllegalArgumentException("Request must not be null.");
    //    }
    //
    fillRequestParams(request);
    //
    lock.lock();
    Request *r = request.clone();
    queue.append(r);
    lock.unlock();
}


int Tracker::queueSize() {
    return queue.size();
}


void Tracker::flush(bool asynchronously) {
    if (queue.size() > 0) {
        if (asynchronously) {
            runTask(1000);
        } else {
            processQueue();
        }
    }
}

void Tracker::processQueue() {
    qDebug() << "Tracker::processQueue";
    int size = queue.size();
    int head = 0;
    //
    while (size-- > 0) {
        //try {
            process(*(queue[head]));
            //
            lock.lock();
            delete (queue[head]);
            queue.remove(head);
            lock.unlock();
//        } catch (Exception e) {
//            head++;
//        }
    }
}

void Tracker::process(Request &request) {
    qDebug() << "Tracker::process";

    QUrl tmpUrl = QUrl::fromEncoded(request.trackingURL().getURL().toAscii());
    QNetworkRequest *nr = new QNetworkRequest(tmpUrl);
    nr->setRawHeader("Accept-Language", QByteArray());
    //nr.setUrl(tmpUrl);
    nr->setRawHeader(QByteArray("User-Agent"), QByteArray().append(getUserAgent()));
    manager->get(nr);
    qDebug() << "Tracker::process ended";
}

void Tracker::replyFinished(QNetworkReply* reply)
{
    ///qDebug() << "reply finished";
    reply->deleteLater();
}

void Tracker::runTask(long delay) {
//    if (!isRunning) {
//        if (flushInterval > 0) {
//            long delayNextRun =
//                    task.endExecutionTime +
//                    flushInterval -
//                    QDateTime::currentMSecsSinceEpoch();
//            if (delayNextRun > delay) {
//                task.cancel();
//                task = new Task();
//                //
//                timer.schedule(task, delay, flushInterval);
//            }
//        } else {
//            task = new Task();
//            timer.schedule(task, delay);
//        }
//    }
}

void Tracker::fillRequestParams(Request &request) {
    request.setAppID(appId);
    request.setUserID(userId);
    request.setFirstVisit(QDateTime::fromMSecsSinceEpoch(firstVisitTimestamp));
    request.setLastVisit(QDateTime::fromMSecsSinceEpoch(lastVisitTimestamp));
    request.setCurrentVisit(QDateTime::fromMSecsSinceEpoch(currentVisitTimestamp));
    //
    //Display display = Display.getDisplay(midlet);
    //Displayable screen = display.getCurrent();
    //
    //if (screen != null) {
   // request.setScreenWidth(QApplication::desktop()->width());
    //request.setScreenHeight(QApplication::desktop()->height());
    //request.setNumberOfColors(display.numColors());
    //}
}

void Tracker::loadCookie() {
    QSettings prefs(QSettings::NativeFormat, QSettings::UserScope,"Future soft","GAT");
    if (prefs.allKeys().size() > 0)
    {
            userId = prefs.value("userId",QVariant(-1)).toInt();
            firstVisitTimestamp = prefs.value("firstVisitTimestamp",QVariant(-1)).toLongLong();
            lastVisitTimestamp = prefs.value("lastVisitTimestamp",QVariant(-1)).toLongLong();
            prefs.setValue("lastVisitTimestamp", QVariant(currentVisitTimestamp));
        } else {
            userId = randInt(2147483647);
            firstVisitTimestamp = currentVisitTimestamp;
            lastVisitTimestamp = currentVisitTimestamp;
            prefs.setValue("userId", QVariant(userId));
            prefs.setValue("firstVisitTimestamp", QVariant(firstVisitTimestamp));
            prefs.setValue("lastVisitTimestamp", QVariant(lastVisitTimestamp));
        }
        prefs.sync();
}
long endExecutionTime = QDateTime::currentMSecsSinceEpoch();
bool isRunning;

QString Tracker::getUserAgent() {
    //    QString midletName = midlet.getAppProperty("MIDlet-Name");
    //    QString midletVersion = midlet.getAppProperty("MIDlet-Version");
    //    QString profile = midlet.getAppProperty("MicroEdition-Profile");
    //    QString config = midlet.getAppProperty("MicroEdition-Configuration");
    //    QString device = System.getProperty("microedition.platform");
    //    device = device != null ? StringUtil.extractDevice(device) : "Unknown";
    //    QString userAgent =
    //            midletName + "/" + midletVersion +
    //            " (Qt; " +
    //            device + "; " +
    //            "Profile/" + profile + " Configuration/" + config + ")";
    //    return userAgent;
    //return "Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.1; WOW64; Trident/6.0)";
    return "Mozilla/5.0 (Macintosh; U; Intel Mac OS X; en) AppleWebKit/523.15 (KHTML, like Gecko) Safari/419.3 Qt";

}

void Tracker::runTask()
{
    isRunning = true;
    //
    processQueue();
    //
    isRunning = false;
    endExecutionTime = QDateTime::currentMSecsSinceEpoch();
}





