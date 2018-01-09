#include <QDebug>
#include <QFileInfo>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "eventrecv.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QString path;

  if (argc > 2) {
    qWarning() << "Usage: ";
    qWarning() << "       " << argv[0] << " (folder selection dialog appears)";
    qWarning() << "       " << argv[0] << " /path/to/jpeg/file.jpg";
    qWarning() << "       " << argv[0] << " /path/to/folder/with/images/";
    exit(0);
  }

  if (argc == 2) {
    path = QString(argv[1]);

    QFileInfo finfo{path};
    if (finfo.isDir()) {
      path = path.append('/');
    } else if (!finfo.exists()) {
      qWarning() << "File " << path << " doesn't exists";
      exit(0);
    }
  }

  QQmlApplicationEngine engine;
  new eventRecv(&engine, path);

  return app.exec();
}
