# QT -= gui
QT += core gui webenginewidgets qml
CONFIG += c++14

TARGET = rateljs
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp \
    src/jsbrowserui.cpp \
    src/jseditor.cpp \
    src/common.cpp \
    src/browsertab.cpp \
    src/browser.cpp \
    src/browserwindow.cpp \
    src/options.cpp \
    src/rateloptions.cpp \
    src/script.cpp \
    src/settingsreader.cpp \
    src/webpage.cpp \
    src/ratel.cpp \
    src/console.cpp \
    src/snippetdetector3.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/jsbrowserui.ui \
    ui/jsprogessview.ui \
    ui/jseditor.ui

HEADERS += \
    src/jsbrowserui.h \
    src/jseditor.h \
    src/common.h \
    src/browsertab.h \
    src/browser.h \
    src/browserwindow.h \
    src/options.h \
    src/rateloptions.h \
    src/script.h \
    src/settingsreader.h \
    src/webpage.h \
    src/ratel.h \
    src/console.h \
    src/webpagesettingsattribute.h \
    src/snippetdetector.h \
    src/snippetdetector3.h

DISTFILES += \
    notes.txt \
    init.js

RESOURCES += \
    embed.qrc
