#include <QDebug>
#include <QFileInfo>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "eventrecv.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    qWarning() << "Usage: " << argv[0] << " /path/to/jpeg/file.jpg";
    exit(0);
  }

  if (!QFileInfo::exists(argv[1])) {
    qWarning() << "File " << argv[1] << " doesn't exists";
    exit(0);
  }

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  QObject *qmlWindow = engine.rootObjects().first();
  QObject *qmlImage = qmlWindow->findChild<QObject *>("image");
  QObject *qmlProgress = qmlWindow->findChild<QObject *>("loading");

  eventRecv *ev = new eventRecv(qmlWindow, qmlImage, qmlProgress, argv[1]);

  QObject::connect(qmlWindow, SIGNAL(moveForward()), ev, SLOT(moveForward()));
  QObject::connect(qmlWindow, SIGNAL(moveBackward()), ev, SLOT(moveBackward()));
  QObject::connect(qmlWindow, SIGNAL(moveHome()), ev, SLOT(moveHome()));
  QObject::connect(qmlWindow, SIGNAL(moveEnd()), ev, SLOT(moveEnd()));

  return app.exec();
}

