#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QObject>
#include <KSyntaxHighlighting/Repository>
#include <KSyntaxHighlighting/SyntaxHighlighter>

class QQuickTextDocument;
class QTextDocument;

class DocumentHandler : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY(DocumentHandler)
  Q_PROPERTY(QQuickTextDocument* textDocument READ quickTextDocument WRITE setQuickTextDocument NOTIFY textDocumentChanged)
  Q_PROPERTY(QString highlightingDefinition READ highlightingDefinition WRITE setHighlightingDefinition NOTIFY highlightingDefinitionChanged)
  Q_PROPERTY(HighlightingTheme highlightingTheme READ highlightingTheme WRITE setHighlightingTheme NOTIFY highlightingThemeChanged)
public:
  enum HighlightingTheme
  {
    //! Theme with a light background color.
    LightTheme,
    //! Theme with a dark background color.
    DarkTheme
  };
  Q_ENUM(HighlightingTheme)
public:
  DocumentHandler(QObject *parent = 0);
  ~DocumentHandler();
public:
  QQuickTextDocument* quickTextDocument() const { return m_textDocument; }
  void setQuickTextDocument(QQuickTextDocument* _document);
  QString highlightingDefinition() const;
  void setHighlightingDefinition(const QString& _hd);
  HighlightingTheme highlightingTheme() const;
  void setHighlightingTheme(HighlightingTheme _theme);
  /**
   * @return the character position corresponding to line \p _line.
   */
  Q_INVOKABLE int positionForLine(int _line) const;
signals:
  void textDocumentChanged();
  void highlightingDefinitionChanged();
  void highlightingThemeChanged();
private:
  void updateHighlighting();
   QQuickTextDocument* m_textDocument = nullptr;
   QTextDocument *m_doc = nullptr;
   KSyntaxHighlighting::Repository m_repository;
   KSyntaxHighlighting::SyntaxHighlighter* m_syntaxHighlighter = nullptr;
   QString m_highlightingDefinition;
   HighlightingTheme m_highlightingTheme;
};

#endif // DOCUMENTHANDLER_H

