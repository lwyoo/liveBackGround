#include <QApplication>
#include <QQmlApplicationEngine>
#include "imagecontrol.h"
#include <QImage>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    ImageControl::instance();
    ImageControl::instance()->getDominantColor(":/test.jpg");


//    QImage test(":/test.jpg");

//    if (false == test.isNull())
//    {
//        qDebug() << "ok";
//    }
//    else
//    {
//        qDebug() << "fa";
//    }

    return app.exec();
}
