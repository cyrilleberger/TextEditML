#ifndef TEXTEDITML_PLUGIN_H
#define TEXTEDITML_PLUGIN_H

#include <QQmlExtensionPlugin>

class TextEditMLPlugin : public QQmlExtensionPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
  void registerTypes(const char *uri);
};

#endif // TEXTEDITML_PLUGIN_H

