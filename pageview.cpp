#include "pageview.h"
#include <QUrl>

PageView::PageView(QString _uri , QString _title)
{
    title = _title;
    uri = !_uri.startsWith("/") ? "/" + _uri : _uri;
}

TrackingURL PageView::trackingURL()
{
    TrackingURL turl = Request::trackingURL();
    turl.addParameter("utmp", QUrl::toPercentEncoding(uri));
    if (!title.isEmpty()) {
        turl.addParameter("utmdt", QUrl::toPercentEncoding (title));
    }
    return turl;
}
void PageView::clone(PageView* p)
{
    Request::clone(p);
    p->title = title;
    p->uri = uri;
}

PageView* PageView::clone()
{
    PageView* p = new PageView(uri,QString());
    *p = *this;
    return p;
}
