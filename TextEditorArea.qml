import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.1
import org.slidesml.textedit 1.0

TextArea {
  id: root

  property TextEditorOptions options: TextEditorOptions {}

  font: options.font
  textColor: options.textColor
  style: TextAreaStyle
  {
    backgroundColor: options.backgroundColor
  }
  DocumentHandler
  {
    textDocument: root.textDocument
  }

}
