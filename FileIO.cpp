#include "FileIO.h"

#include <QDir>
#include <QFile>
#include <QQmlEngine>
#include <QFileInfo>
#include <QFileSystemWatcher>

#include <qqml.h>

QFileSystemWatcher* FileIO::s_watcher = nullptr;

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

void FileIO::setUrl(const QUrl& _url)
{
  if(_url == m_url) return;
  if(m_monitorChanges)
  {
    if(not m_url.toLocalFile().isEmpty())
    {
      s_watcher->removePath(m_url.toLocalFile());
    }
    if(not _url.toLocalFile().isEmpty())
    {
      s_watcher->addPath(_url.toLocalFile());
    }
  }
  m_url = _url;
  emit(urlChanged());
}

void FileIO::setMonitorChanges(bool _v)
{
  if(m_monitorChanges == _v) return;
  if(_v)
  {
    if(not s_watcher)
    {
      s_watcher = new QFileSystemWatcher;
    }
    QObject::connect(s_watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(fileChanged(const QString&)));
    if(not m_url.toLocalFile().isEmpty())
    {
      s_watcher->addPath(m_url.toLocalFile());
    }
  } else {
    QObject::disconnect(s_watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(fileChanged(const QString&)));
    if(not m_url.toLocalFile().isEmpty())
    {
      s_watcher->removePath(m_url.toLocalFile());
    }
  }
  m_monitorChanges = _v;
  emit(monitorChangesChanged());
}

void FileIO::fileChanged(const QString& _name)
{
  if(_name == m_url.toLocalFile())
  {
    emit(fileChanged());
  }
}
