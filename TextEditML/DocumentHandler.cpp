#include "DocumentHandler.h"

#include <QTextBlock>
#include <QQuickTextDocument>

#include <Definition>
#include <Theme>

DocumentHandler::DocumentHandler(QObject *parent):
  QObject(parent),
  m_highlightingTheme(HighlightingTheme::LightTheme)
{
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
    updateHighlighting();
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
    updateHighlighting();
  }
}

DocumentHandler::HighlightingTheme DocumentHandler::highlightingTheme() const
{
  return m_highlightingTheme;
}

void DocumentHandler::setHighlightingTheme(DocumentHandler::HighlightingTheme _theme)
{
  m_highlightingTheme = _theme;
  emit(highlightingThemeChanged());
  if(m_syntaxHighlighter)
  {
    updateHighlighting();
  }
}

void DocumentHandler::updateHighlighting()
{
  switch(m_highlightingTheme)
  {
    case HighlightingTheme::LightTheme:
      m_syntaxHighlighter->setTheme(m_repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
      break;
    case HighlightingTheme::DarkTheme:
      m_syntaxHighlighter->setTheme(m_repository.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme));
      break;
  }
  if(not m_highlightingDefinition.isEmpty())
  {
    KSyntaxHighlighting::Definition def = m_repository.definitionForName(m_highlightingDefinition);
    if(not def.isValid())
    {
      def = m_repository.definitionForMimeType(m_highlightingDefinition);
    }
    if(def.isValid())
    {
      m_syntaxHighlighter->setDefinition(def);
    } else {
      qWarning() << "No syntax definition for " << m_highlightingDefinition;
    }
  }
}

int DocumentHandler::positionForLine(int _line) const
{
  return m_textDocument->textDocument()->findBlockByLineNumber(_line).position();
}

