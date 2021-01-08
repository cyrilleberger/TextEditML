#include "TextEditMLPlugin.h"

#include "DocumentHandler.h"
#include "FileIO.h"
#include "TemporaryFile.h"

#include <qqml.h>

void TextEditMLPlugin::registerTypes(const char *uri)
{
  // @uri TextEditML
  qmlRegisterType<DocumentHandler>(uri, 2, 0, "DocumentHandler");
  qmlRegisterType<FileIO>(uri, 2, 0, "FileIO");
  qmlRegisterType<TemporaryFile>(uri, 2, 0, "TemporaryFile");
}


