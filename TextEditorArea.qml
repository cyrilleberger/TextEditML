import QtQuick 2.1
import QtQuick.Controls 1.0
import org.slidesml.textedit 1.0

TextArea {
  id: root
  font.family: "monospace"
  DocumentHandler
  {
    textDocument: root.textDocument
  }
}
