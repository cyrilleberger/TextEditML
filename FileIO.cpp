#include "FileIO.h"

#include <QDir>
#include <QFile>
#include <QQmlEngine>
#include <QFileInfo>

#include <qqml.h>

FileIO::FileIO(QObject *parent) :
  QObject(parent)
{
}

void FileIO::readFile(const QUrl& _url)
{
  setUrl(_url);
  readFile();
}

void FileIO::readFile()
{
  QFile file(m_url.toLocalFile());
  file.open(QIODevice::ReadOnly);
  setContent(file.readAll());
}

void FileIO::writeFile(const QUrl& _url)
{
  setUrl(_url);
  writeFile();
}

void FileIO::writeFile()
{
  QFile file(m_url.toLocalFile());
  file.open(QIODevice::WriteOnly);
  file.write(m_content.toUtf8());
}

void FileIO::addImportPath(const QUrl& _url)
{
  qmlEngine(this)->addImportPath(QFileInfo(_url.toLocalFile()).absolutePath());
}

void FileIO::setCurrentPath(const QUrl& _url)
{
  QDir::setCurrent(QFileInfo(_url.toLocalFile()).absolutePath());
}
