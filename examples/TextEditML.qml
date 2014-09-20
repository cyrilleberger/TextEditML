import QtQuick 2.0
import QtQuick.Controls 1.0
import org.slidesml.textedit 1.0

ApplicationWindow
{
  width: 800
  height: 600
  Item
  {
    id: preview
    width: 300
    height: parent.height
    property Item childItem
  }
  Rectangle {
    width: preview.width
    height: 50
    color: "white"
    anchors.bottom: parent.bottom
    Text
    {
      id: error
      visible: false
      anchors.fill: parent
      color: "red"
    }
  }
  TextEditorArea
  {
    id: editor
    height: parent.height
    anchors.left: preview.right
    anchors.right: parent.right
    text: "import QtQuick 2.0;
Rectangle
{
  width: 80
  height: 60
  color: \"red\"
  Text
  {
    text: \"Test!\"
    color: \"white\"
  }
}"
    onTextChanged:
    {
      try
      {
        var item = Qt.createQmlObject(editor.text, preview, "preview")

        if(preview.childItem)
        {
          preview.childItem.visible = false
          preview.childItem.destroy()
          preview.childItem = null
        }

        preview.childItem = item
        error.text = ""
      } catch(ex)
      {
        var text = ""
        for(var k in ex['qmlErrors'])
        {
          var err = ex['qmlErrors'][k]
          text += err['lineNumber'] + "," + err['columnNumber'] + ":" + err['message']
        }
        error.text = text
        error.visible = true
      }
    }
  }
}
