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
  m_temporaryFile->open();
  emit(fileNameChanged());
}

void TemporaryFile::setFileTemplate(const QString& _template)
{
  m_fileTemplate = QUrl::fromUserInput(_template).toLocalFile();
  emit(fileTemplateChanged());
  regenerate();
}
