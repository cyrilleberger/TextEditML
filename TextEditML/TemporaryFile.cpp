#include "TemporaryFile.h"

#include <QDebug>
#include <QUrl>

TemporaryFile::TemporaryFile(QObject *parent) :
  QObject(parent), m_temporaryFile(new QTemporaryFile)
{
}

TemporaryFile::~TemporaryFile()
{
  delete m_temporaryFile;
}

void TemporaryFile::regenerate()
{
  delete m_temporaryFile;
  m_temporaryFile = new QTemporaryFile(m_fileTemplate);
  emit(fileNameChanged());
}

void TemporaryFile::setFileTemplate(const QString& _template)
{
  m_fileTemplate = QUrl::fromUserInput(_template).toLocalFile();
  emit(fileTemplateChanged());
  regenerate();
}

void TemporaryFile::writeContent(const QString& _content)
{
  m_temporaryFile->open();
  m_temporaryFile->write(_content.toUtf8());
  m_temporaryFile->close();
}
