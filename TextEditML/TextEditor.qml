import QtQuick 2.15

import TextEditML 2.0
 
TextEdit
{
  id: root
  
  property alias options: internal.options
  property alias document: internal.document
  
  TextEditorInternal
  {
    id: internal
  }
  
  //color: options.textColor

  function moveToLine(_line)
  {
    root.cursorPosition = document.positionForLine(_line)
  }

  Keys.onTabPressed: internal.handleOnTabPressed(event)
  Keys.onPressed: internal.handleOnKeysPressed(event)
  Keys.onReturnPressed: internal.handleOnReturnPressed(event)
}


