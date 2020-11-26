#include "DocumentHandler.h"

#include <QTextBlock>
#include <QQuickTextDocument>

#include <Definition>
#include <Theme>

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
  delete m_syntaxHighlighter;
  m_syntaxHighlighter = nullptr;
  if(m_textDocument)
  {
    m_doc = m_textDocument->textDocument();
    m_syntaxHighlighter = new KSyntaxHighlighting::SyntaxHighlighter(m_doc);
    m_syntaxHighlighter->setTheme(m_repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    if(not m_highlightingDefinition.isEmpty())
    {
      KSyntaxHighlighting::Definition def = m_repository.definitionForName(m_highlightingDefinition);
      if(def.isValid())
      {
        m_syntaxHighlighter->setDefinition(def);
      } else {
        qWarning() << "No syntax definition for " << m_highlightingDefinition;
      }
    }
  }
  emit(textDocumentChanged());
}

QString DocumentHandler::highlightingDefinition() const
{
  return m_highlightingDefinition;
}

void DocumentHandler::setHighlightingDefinition(const QString& _hd)
{
  m_highlightingDefinition = _hd;
  emit(highlightingDefinition());
  if(m_syntaxHighlighter)
  {
    m_syntaxHighlighter->setDefinition(m_repository.definitionForName(m_highlightingDefinition));
  }
}

int DocumentHandler::positionForLine(int _line) const
{
  return m_textDocument->textDocument()->findBlockByLineNumber(_line).position();
}

