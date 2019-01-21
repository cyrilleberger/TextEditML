#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>

#include <QUrl>

class FileIO : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
  Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
public:
  explicit FileIO(QObject *parent = 0);
  Q_INVOKABLE void readFile();
  Q_INVOKABLE void readFile(const QUrl& _url);
  Q_INVOKABLE void writeFile();
  Q_INVOKABLE void writeFile(const QUrl& _url);
  Q_INVOKABLE void addImportPath(const QUrl& _url);
  Q_INVOKABLE void setCurrentPath(const QUrl& _url);
  QString content() const { return m_content; }
  void setContent(const QString& _content) { if(m_content != _content) { m_content = _content; emit(contentChanged()); } }
  QUrl url() const { return m_url; }
  void setUrl(const QUrl& _url) { m_url = _url; emit(urlChanged()); }
signals:
  void contentChanged();
  void urlChanged();
private:
  QString m_content;
  QUrl m_url;
};

#endif // FILEIO_H
