#ifndef PAGEVIEW_H
#define PAGEVIEW_H

#include <QString>
#include "trackingurl.h"
#include "request.h"

class PageView : public Request
{
public:
    PageView(QString _uri, QString _title = QString());
    virtual TrackingURL trackingURL();
    virtual void clone(PageView* p);
    virtual PageView* clone();
private:
    QString title;
    QString uri;
};

#endif // PAGEVIEW_H
