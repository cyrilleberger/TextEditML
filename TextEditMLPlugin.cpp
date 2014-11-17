#include "TextEditMLPlugin.h"

#include "DocumentHandler.h"
#include "FileIO.h"
#include "TemporaryFile.h"

#include <qqml.h>

void TextEditMLPlugin::registerTypes(const char *uri)
{
  // @uri org.storyml.textedit
  qmlRegisterType<DocumentHandler>(uri, 1, 0, "DocumentHandler");
  qmlRegisterType<FileIO>(uri, 1, 0, "FileIO");
  qmlRegisterType<TemporaryFile>(uri, 1, 0, "TemporaryFile");
}


