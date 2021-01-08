import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.1
import TextEditML 2.0

TextArea {
  id: root

  property TextEditorOptions options: TextEditorOptions {}
  property alias document: internal.document
  
  TextEditorInternal
  {
    
    id: internal
  }
  
  textColor: options.textColor

  style: TextAreaStyle
  {
    backgroundColor: options.backgroundColor
  }

  function moveToLine(_line)
  {
    root.cursorPosition = document.positionForLine(_line)
  }

  Keys.onTabPressed: internal.handleOnTabPressed(event)
  Keys.onPressed: internal.handleOnKeysPressed(event)
  Keys.onReturnPressed: internal.handleOnReturnPressed(event)
}
