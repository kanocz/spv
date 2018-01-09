#ifndef EVENTRECV_H
#define EVENTRECV_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QStringList>

class eventRecv : public QObject {
  Q_OBJECT
public:
  explicit eventRecv(QQmlApplicationEngine *engine, QString path);

signals:

public slots:
  void moveForward();
  void moveBackward();
  void moveHome();
  void moveEnd();
  void folderSelected(QString folder);

private:
  QQmlApplicationEngine *m_engine = nullptr;
  QObject *m_title = nullptr, *m_source = nullptr, *m_progress = nullptr;
  QString m_path;
  QString m_currentFile;
  QStringList m_filelist;
  int m_currentIndex;

  void update();
  void setPath(QString path);
};

#endif // EVENTRECV_H
