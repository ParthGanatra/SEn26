file(GLOB QML_FILES *.qml)

install(FILES ${QML_FILES} qmldir
        DESTINATION ${QML_INSTALL_DIR}/Material/Extras)
install(DIRECTORY js images
        DESTINATION ${QML_INSTALL_DIR}/Material/Extras)
