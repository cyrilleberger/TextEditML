import QtQuick 2.0

Item
{
  property color backgroundColor: "black"
  property color textColor: "white"
  property font  font: fontProvider.font

  Text
  {
    id: fontProvider
    font.family: "monospace"
  }
}
