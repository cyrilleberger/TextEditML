import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.1
import org.storyml.textedit 1.0

TextArea {
  id: root

  property TextEditorOptions options: TextEditorOptions {}
  property DocumentHandler document: DocumentHandler
  {
    textDocument: root.textDocument
  }

  font: options.font
  textColor: options.textColor
  style: TextAreaStyle
  {
    backgroundColor: options.backgroundColor
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
    root.insert(cursorPosition, __indent)
  }
  Keys.onPressed:
  {
    if (event.key === Qt.Key_BraceRight)
    {
      root.select(0, cursorPosition)
      var previousContent = root.selectedText.split(/\r\n|\r|\n/)
      root.deselect()
      var currentLine = previousContent[previousContent.length - 1]
      var leftBrace = /{/, rightBrace = /}/;
      if (!leftBrace.test(currentLine))
      {
        root.remove(cursorPosition, cursorPosition - currentLine.length);
        currentLine = currentLine.toString().replace(new RegExp(" {1,"+ options.indentSize +"}"), "");
        root.insert(cursorPosition, currentLine);
      }
    }
  }
  Keys.onReturnPressed:
  {
    root.select(0, cursorPosition)
    var previousContent = root.selectedText.split(/\r\n|\r|\n/)
    root.deselect()
    var currentLine = previousContent[previousContent.length - 1]
    var leftBrace = /{/, rightBrace = /}/;
    root.insert(cursorPosition, "\n")
    var whitespaceAppend = currentLine.match(new RegExp(/^[ \t]*/))  // whitespace
    if (leftBrace.test(currentLine)) // indent
      whitespaceAppend += __indent;
    root.insert(cursorPosition, whitespaceAppend)
  }
}
