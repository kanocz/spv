#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "eventrecv.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  QObject *qmlWindow = engine.rootObjects().first();
  QObject *qmlImage = qmlWindow->children().first();

  eventRecv *ev = new eventRecv(qmlWindow, qmlImage, argv[1]);

  QObject::connect(qmlWindow, SIGNAL(moveForward()), ev, SLOT(moveForward()));
  QObject::connect(qmlWindow, SIGNAL(moveBackward()), ev, SLOT(moveBackward()));
  QObject::connect(qmlWindow, SIGNAL(moveHome()), ev, SLOT(moveHome()));
  QObject::connect(qmlWindow, SIGNAL(moveEnd()), ev, SLOT(moveEnd()));

  return app.exec();
}

