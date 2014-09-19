#include "DocumentHandler.h"

#include <QQuickTextDocument>

DocumentHandler::DocumentHandler(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);
}

DocumentHandler::~DocumentHandler()
{
}

void DocumentHandler::setQuickTextDocument(QQuickTextDocument* _document)
{
  m_textDocument = _document;
  if(m_textDocument)
  {
    m_doc = m_textDocument->textDocument();
  }
  emit(textDocumentChanged());
}

