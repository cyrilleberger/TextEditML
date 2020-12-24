import QtQuick 2.0
import TextEditML 1.0

QtObject
{
  property TextEditorOptions options: TextEditorOptions {}
  property DocumentHandler document: DocumentHandler
  {
    textDocument: root.textDocument
  }

  property string indent: makeIndent(options.indentSize)

  Component.onCompleted:
  {
    root.font = Qt.binding(function() { return options.font })
  }
  
  function makeIndent(s)
  {
    var r = ""
    for(var i = 0; i < s; ++i)
    {
      r += ' '
    }
    return r;
  }
  
  function handleOnTabPressed(event)
  {
    root.insert(root.cursorPosition, indent)
  }
  function handleOnKeysPressed(event)
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
  function handleOnReturnPressed(event)
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
