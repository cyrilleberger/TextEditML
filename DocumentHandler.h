#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QObject>

class QQuickTextDocument;
class QTextDocument;

class DocumentHandler : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY(DocumentHandler)
  Q_PROPERTY(QQuickTextDocument* textDocument READ quickTextDocument WRITE setQuickTextDocument NOTIFY textDocumentChanged)
public:
  DocumentHandler(QObject *parent = 0);
  ~DocumentHandler();
public:

  QQuickTextDocument* quickTextDocument() const { return m_textDocument; }
  void setQuickTextDocument(QQuickTextDocument* _document);
signals:
  void textDocumentChanged();
private:
   QQuickTextDocument* m_textDocument;
   QTextDocument *m_doc;
};

#endif // DOCUMENTHANDLER_H

