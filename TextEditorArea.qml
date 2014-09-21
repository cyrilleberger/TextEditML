import QtQuick 2.1
import QtQuick.Controls 1.0
import org.slidesml.textedit 1.0

Rectangle
{
  id: root
  property alias text: textArea.text
  property TextEditorOptions options: TextEditorOptions {}

  color: options.backgroundColor
  TextArea {
    id: textArea
    font: options.font
    textColor: options.textColor
    anchors.fill: parent
    DocumentHandler
    {
      textDocument: root.textDocument
    }

  }
}
