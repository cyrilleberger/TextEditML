#include "TextEditMLPlugin.h"
#include "DocumentHandler.h"

#include <qqml.h>

void TextEditMLPlugin::registerTypes(const char *uri)
{
  // @uri org.slidesml.textedit
  qmlRegisterType<DocumentHandler>(uri, 1, 0, "DocumentHandler");
}


