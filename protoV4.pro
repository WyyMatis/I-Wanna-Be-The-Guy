QT       += core gui #multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apple.cpp \
    block.cpp \
    commande.cpp \
    creditmenu.cpp \
    lightning.cpp \
    main.cpp \
    pausemenu.cpp \
    personn.cpp \
    piece.cpp \
    resultmenu.cpp \
    secret.cpp \
    spike.cpp \
    startmenu.cpp \
    thegameloop.cpp \
    tile.cpp \
    top10menu.cpp

HEADERS += \
    apple.h \
    block.h \
    commande.h \
    creditmenu.h \
    lightning.h \
    pausemenu.h \
    personn.h \
    piece.h \
    resultmenu.h \
    secret.h \
    spike.h \
    startmenu.h \
    thegameloop.h \
    tile.h \
    top10menu.h

FORMS += \
    commande.ui \
    creditmenu.ui \
    pausemenu.ui \
    resultmenu.ui \
    secret.ui \
    startmenu.ui \
    thegameloop.ui \
    top10menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Ressources.qrc

QMAKE_LFLAGS+=-static
