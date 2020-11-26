#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QObject>
#include <Repository>
#include <SyntaxHighlighter>

class QQuickTextDocument;
class QTextDocument;

class DocumentHandler : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY(DocumentHandler)
  Q_PROPERTY(QQuickTextDocument* textDocument READ quickTextDocument WRITE setQuickTextDocument NOTIFY textDocumentChanged)
  Q_PROPERTY(QString highlightingDefinition READ highlightingDefinition WRITE setHighlightingDefinition NOTIFY highlightingDefinitionChanged)
public:
  DocumentHandler(QObject *parent = 0);
  ~DocumentHandler();
public:

  QQuickTextDocument* quickTextDocument() const { return m_textDocument; }
  void setQuickTextDocument(QQuickTextDocument* _document);
  QString highlightingDefinition() const;
  void setHighlightingDefinition(const QString& _hd);
  Q_INVOKABLE int positionForLine(int _line) const;
signals:
  void textDocumentChanged();
  void highlightingDefinitionChanged();
private:
   QQuickTextDocument* m_textDocument = nullptr;
   QTextDocument *m_doc = nullptr;
   KSyntaxHighlighting::Repository m_repository;
   KSyntaxHighlighting::SyntaxHighlighter* m_syntaxHighlighter = nullptr;
   QString m_highlightingDefinition;
};

#endif // DOCUMENTHANDLER_H

