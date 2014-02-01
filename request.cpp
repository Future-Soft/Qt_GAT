#include "request.h"

Request::Request():_screenWidth(-1),_screenHeight(-1)
{
}

void Request::setAppID(const QString &appID)
{
    _appID = appID;
}

void Request::setUserID(int userID)
{
    _userID = userID;
}

void Request::setFirstVisit(const QDateTime &timestamp)
{
    _firstVisit = timestamp;
}

void Request::setLastVisit(const QDateTime &timestamp)
{
    _lastVisit = timestamp;
}

void Request::setCurrentVisit(const QDateTime &timestamp)
{
    _currentVisit = timestamp;
}

void Request::setScreenWidth(int w)
{
    _screenWidth = w;
}

void Request::setScreenHeight(int h)
{
    _screenHeight = h;
}

void Request::clone(Request* r)
{
    r->_appID = _appID;
    r->_userID = _userID;
    r->_firstVisit = _firstVisit;
    r->_lastVisit = _lastVisit;
    r->_currentVisit = _currentVisit;
    r->_screenWidth = _screenWidth;
    r->_screenHeight = _screenHeight;
}
Request* Request::clone()
{
    Request* r = new Request();
    *r = *this;
    return r;
}

QString Request::getCookie()
{
    QString cookie = "__utma%3D1." + QString::number(_userID) + "." + QString::number(_firstVisit.toMSecsSinceEpoch()) + "." + QString::number(_lastVisit.toMSecsSinceEpoch()) + "." + QString::number(_currentVisit.toMSecsSinceEpoch()) + ".1;";
    return cookie;
}

TrackingURL Request::trackingURL()
{
    TrackingURL turl;// = new TrackingURL();
    turl.addParameter("utmac", _appID);
    turl.addParameter("utmcc", getCookie());
    if (_screenWidth != -1 && _screenHeight != -1) {
        turl.addParameter("utmsr", _screenWidth + "x" + _screenHeight);
    }
    //if (numberOfColors != -1) {
    // hard coded color depth
    // TODO: get real color depth
    turl.addParameter("utmsc", "24-bit");
    //}
    return turl;
}
