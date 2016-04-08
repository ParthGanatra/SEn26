QT += qml quick webengine
CONFIG += c++11

# Add more folders to ship with the application, here
folder_01.source = qml/StockAnalyser
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH = [qml/StockAnalyser/modules]

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# The .cpp file which was generated for your project. Feel free to hack it.
HEADERS += \
    backend.h \
    SMTP/emailaddress.h \
    SMTP/mimeattachment.h \
    SMTP/mimecontentformatter.h \
    SMTP/mimefile.h \
    SMTP/mimehtml.h \
    SMTP/mimeinlinefile.h \
    SMTP/mimemessage.h \
    SMTP/mimemultipart.h \
    SMTP/mimepart.h \
    SMTP/mimetext.h \
    SMTP/quotedprintable.h \
    SMTP/smtpclient.h \
    SMTP/smtpexports.h \
    frontend.h

SOURCES += main.cpp \
    backend.cpp \
    SMTP/emailaddress.cpp \
    SMTP/mimeattachment.cpp \
    SMTP/mimecontentformatter.cpp \
    SMTP/mimefile.cpp \
    SMTP/mimehtml.cpp \
    SMTP/mimeinlinefile.cpp \
    SMTP/mimemessage.cpp \
    SMTP/mimemultipart.cpp \
    SMTP/mimepart.cpp \
    SMTP/mimetext.cpp \
    SMTP/quotedprintable.cpp \
    SMTP/smtpclient.cpp \
    frontend.cpp

# Please do not modify the following two lines. Required for deployment.
desktopInstallPrefix = D:\Qt\StockAnalyser
exists(qmlapplicationviewer/qmlapplicationviewer.pri):include(qmlapplicationviewer/qmlapplicationviewer.pri)
else:include(qmlapplicationviewer.pri)
qtcAddDeployment()
