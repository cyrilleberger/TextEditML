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
  property string __indent: makeIndent(options.indentSize)

  function makeIndent(s)
  {
    var r = ""
    for(var i = 0; i < s; ++i)
    {
      r += ' '
    }
    return r;
  }

  Keys.onTabPressed:
  {
    textArea.insert(cursorPosition, __indent)
  }
  Keys.onPressed:
  {
    if (event.key === Qt.Key_BraceRight)
    {
      textArea.select(0, cursorPosition)
      var previousContent = textArea.selectedText.split(/\r\n|\r|\n/)
      textArea.deselect()
      var currentLine = previousContent[previousContent.length - 1]
      var leftBrace = /{/, rightBrace = /}/;
      if (!leftBrace.test(currentLine))
      {
        textArea.remove(cursorPosition, cursorPosition - currentLine.length);
        currentLine = currentLine.toString().replace(new RegExp(" {1,"+ options.indentSize +"}"), "");
        textArea.insert(cursorPosition, currentLine);
      }
    }
  }
  Keys.onReturnPressed:
  {
    textArea.select(0, cursorPosition)
    var previousContent = textArea.selectedText.split(/\r\n|\r|\n/)
    textArea.deselect()
    var currentLine = previousContent[previousContent.length - 1]
    var leftBrace = /{/, rightBrace = /}/;
    textArea.insert(cursorPosition, "\n")
    var whitespaceAppend = currentLine.match(new RegExp(/^[ \t]*/))  // whitespace
    if (leftBrace.test(currentLine)) // indent
      whitespaceAppend += __indent;
    textArea.insert(cursorPosition, whitespaceAppend)
  }
}
