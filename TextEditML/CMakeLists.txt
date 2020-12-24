qt5_add_resources(TEXTEDITML_QRC_SRC TextEditML.qrc)

set(TEXTEDITML_SRCS
  DocumentHandler.cpp
  FileIO.cpp
  TemporaryFile.cpp
  TextEditMLPlugin.cpp
)

add_library(TextEditML SHARED ${TEXTEDITML_SRCS} )
target_link_libraries(TextEditML Qt5::Gui Qt5::Quick KF5::SyntaxHighlighting)

install(TARGETS TextEditML EXPORT TextEditMLTargets DESTINATION ${INSTALL_QML_PLUGIN_DIR} )


install(FILES qmldir TextEditorOptions.qml TextEditor.qml TextEditorInternal.qml DESTINATION ${INSTALL_QML_PLUGIN_DIR})

add_subdirectory(Controls/)
