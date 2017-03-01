import QtQuick 2.0

Item
{
  property color backgroundColor: "white"
  property color textColor: "black"
  property font  font: fontProvider.font

  property int indentSize: 2
  Text
  {
    id: fontProvider
    font.family: "monospace"
  }
}
