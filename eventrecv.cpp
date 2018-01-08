#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>

#include "eventrecv.h"

eventRecv::eventRecv(QObject *title, QObject *source, QObject *progress, QString image, QObject *parent)
  : QObject(parent), m_title(title), m_source(source), m_progress(progress)
{
  QFileInfo fi(image);
  m_path = fi.absolutePath();
  QDir dir(m_path, "*.[jp][pn]g", QDir::Name | QDir::IgnoreCase, QDir::Files);
  m_filelist = dir.entryList();
  if (m_filelist.length() < 1) {
    qWarning() << "No JPEG or PNG files in folder!";
    QGuiApplication::quit();
    return;
  }
//  qDebug() << m_filelist;
  m_currentIndex = m_filelist.indexOf(fi.fileName());
  if (m_currentIndex < 0) {
    m_currentIndex = 0;
  }
  update();
}

void eventRecv::moveForward()
{
  if (m_filelist.length() <= (m_currentIndex + 1)) {
    return;
  }
  m_currentIndex++;
  update();
}

void eventRecv::moveBackward()
{
  if (m_currentIndex == 0) {
    return;
  }
  m_currentIndex--;
  update();
}

void eventRecv::moveHome()
{
  m_currentIndex = 0;
  update();
}

void eventRecv::moveEnd()
{
  m_currentIndex = m_filelist.length() - 1;
  update();
}

void eventRecv::update()
{
  m_currentFile = m_filelist.at(m_currentIndex);
  QString fname = m_path + '/' + m_currentFile;
  m_progress->setProperty("visible", true);
  QGuiApplication::processEvents();
  m_title->setProperty("title", fname);
  m_source->setProperty("source", QString("file://") + fname);
}

