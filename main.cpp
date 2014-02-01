#include <QtGui/QApplication>
#include "tracker.h"
#include "pageview.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(new QApplication(argc, argv));
    Tracker *t = Tracker::getInstance("UA-12789367-1");
    PageView p("damn");
    t->addToQueue(p);
    return app->exec();
}
