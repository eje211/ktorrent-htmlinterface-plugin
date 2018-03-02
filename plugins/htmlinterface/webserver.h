#ifndef KHTMLINTERFACEWEBSERVER_H
#define KHTMLINTERFACEWEBSERVER_H

#include <QtGlobal>
#include <QObject>

namespace kt
{
    class WebServer : public QObject
    {
        Q_OBJECT
    public:
        WebServer();
        ~WebServer();
    public slots:
        void process();
    signals:
        void finished();
        void error(QString err);
    private:
    };
}

#endif
