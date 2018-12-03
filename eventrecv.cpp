#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QTimer>

#include "eventrecv.h"

void exitIt() {}

eventRecv::eventRecv(QQmlApplicationEngine *engine, QString path)
    : QObject(0), m_engine(engine) {
  QTimer::singleShot(1, [&]() { this->setPath(path); });
}

void eventRecv::moveForward() {
  if (m_filelist.length() <= (m_currentIndex + 1)) {
    return;
  }
  m_currentIndex++;
  update();
}

void eventRecv::moveBackward() {
  if (m_currentIndex == 0) {
    return;
  }
  m_currentIndex--;
  update();
}

void eventRecv::moveHome() {
  m_currentIndex = 0;
  update();
}

void eventRecv::moveEnd() {
  m_currentIndex = m_filelist.length() - 1;
  update();
}

void eventRecv::folderSelected(QString folder) {
  if (folder.startsWith("file:///")) {
    folder = folder.remove(0, 7);
  }
  folder = folder.append('/');
  this->setPath(folder);
}

void eventRecv::update() {
  m_currentFile = m_filelist.at(m_currentIndex);
  QString fname = m_path + '/' + m_currentFile;
  m_progress->setProperty("visible", true);
  QGuiApplication::processEvents();
  QFileInfo info(fname);
  m_title->setProperty(
      "title", QString("%1 (%2/%3) %4")
                   .arg(fname)
                   .arg(m_currentIndex + 1)
                   .arg(m_filelist.length())
                   .arg(info.created().toString("yyyy-MM-dd hh:mm:ss")));
  m_source->setProperty("source", QString("file://") + fname);
}

void eventRecv::setPath(QString path) {

  if (path.isEmpty() || path.isNull()) {
    m_engine->load(QUrl(QStringLiteral("qrc:/folderSelect.qml")));
    QObject *root = m_engine->rootObjects().first();
    QObject::connect(root, SIGNAL(folderSelected(QString)), this,
                     SLOT(folderSelected(QString)));
    QMetaObject::invokeMethod(root, "openit");
    return;
  }

  QFileInfo fi{path};
  m_path = fi.absolutePath();

  QDir dir(m_path, "*.[jp][pn]g", QDir::Name | QDir::IgnoreCase, QDir::Files);
  m_filelist = dir.entryList();
  if (m_filelist.length() < 1) {
    qWarning() << "No JPEG or PNG files in folder!";
    QGuiApplication::quit();
    return;
  }

  m_currentIndex = m_filelist.indexOf(fi.fileName());
  if (m_currentIndex < 0) {
    m_currentIndex = 0;
  }

  if (!m_title) {
    m_engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto roots = m_engine->rootObjects();
    for (QObject *o : roots) {
      if (o->objectName() == "window") {
        m_title = o;
      }
    }

    m_source = m_title->findChild<QObject *>("image");
    m_progress = m_title->findChild<QObject *>("loading");

    QObject::connect(m_title, SIGNAL(moveForward()), this, SLOT(moveForward()));
    QObject::connect(m_title, SIGNAL(moveBackward()), this,
                     SLOT(moveBackward()));
    QObject::connect(m_title, SIGNAL(moveHome()), this, SLOT(moveHome()));
    QObject::connect(m_title, SIGNAL(moveEnd()), this, SLOT(moveEnd()));
  }
  update();
}
