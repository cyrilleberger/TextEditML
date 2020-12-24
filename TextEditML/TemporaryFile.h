#ifndef TEMPORARYFILE_H
#define TEMPORARYFILE_H

#include <QObject>
#include <QTemporaryFile>

class TemporaryFile : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString fileTemplate READ fileTemplate WRITE setFileTemplate NOTIFY fileTemplateChanged)
  Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged)
public:
  explicit TemporaryFile(QObject *parent = 0);
  ~TemporaryFile();
  Q_INVOKABLE void regenerate();

  QString fileTemplate() const { return m_fileTemplate; }
  void setFileTemplate(const QString& _template);
  QString fileName() const { return m_temporaryFile->fileName(); }
  Q_INVOKABLE void writeContent(const QString& _content);
signals:
  void fileTemplateChanged();
  void fileNameChanged();
private:
  QTemporaryFile* m_temporaryFile;
  QString m_fileTemplate;
};

#endif // TEMPORARYFILE_H
