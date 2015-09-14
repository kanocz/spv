#include <QFileInfo>
#include <QDir>
#include <QDebug>

#include "eventrecv.h"

eventRecv::eventRecv(QObject *title, QObject *source, QString image, QObject *parent)
  : QObject(parent), m_title(title), m_source(source)
{
  QFileInfo fi(image);
  m_path = fi.absolutePath();
  m_currentFile = fi.fileName();
  update();
  QDir dir(m_path, "*.jpg", QDir::Name | QDir::IgnoreCase, QDir::Files);
  m_filelist = dir.entryList();
  qDebug() << m_filelist;
  m_currentIndex = m_filelist.indexOf(m_currentFile);
}

void eventRecv::moveForward()
{
  m_currentIndex++;
  if (m_filelist.length() <= m_currentIndex) {
    m_currentIndex = 0;
  }
  m_currentFile = m_filelist.at(m_currentIndex);
  update();
}

void eventRecv::moveBackward()
{
  m_currentIndex--;
  if (m_currentIndex < 0) {
    m_currentIndex = m_filelist.length() - 1;
  }
  m_currentFile = m_filelist.at(m_currentIndex);
  update();
}

void eventRecv::update()
{
  QString fname = m_path + '/' + m_currentFile;
  m_title->setProperty("title", fname);
  m_source->setProperty("source", QString("file://") + fname);
}

