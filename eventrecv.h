#ifndef EVENTRECV_H
#define EVENTRECV_H

#include <QObject>
#include <QStringList>


class eventRecv : public QObject
{
    Q_OBJECT
  public:
    explicit eventRecv(QObject *title, QObject *source, QString image, QObject *parent = 0);

  signals:

  public slots:
    void moveForward();
    void moveBackward();

  private:
    QObject *m_title, *m_source;
    QString m_path;
    QString m_currentFile;
    QStringList m_filelist;
    int m_currentIndex;

    void update();

};

#endif // EVENTRECV_H
