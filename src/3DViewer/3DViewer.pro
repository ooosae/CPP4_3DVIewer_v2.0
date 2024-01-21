QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 -Wno-error=deprecated-declarations

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cc \
    controller/controller.cc \
    view/myopenglwidget.cc \
    model/edges.cc \
    model/figure.cc \
    model/point.cc \
    model/points.cc \
    model/faces.cc \
    gifimage/qgifimage.cpp \
    3rdParty/giflib/dgif_lib.c \
    3rdParty/giflib/egif_lib.c \
    3rdParty/giflib/gif_err.c \
    3rdParty/giflib/gif_font.c \
    3rdParty/giflib/gif_hash.c \
    3rdParty/giflib/gifalloc.c \
    3rdParty/giflib/quantize.c

HEADERS += controller/controller.h \
    view/myopenglwidget.h \
    model/edges.h \
    model/figure.h \
    model/figureBuilder.h \
    model/point.h \
    model/points.h \
    model/faces.h \
    model/errors.h \
    model/action_data.h \
    gifimage/qgifimage.h \
    3rdParty/giflib/gif_lib.h \
    3rdParty/giflib/gif_hash.h \
    3rdParty/giflib/gif_lib_private.h \
    model/factoryMethod.h

FORMS += \
    view/view.ui \

INCLUDEPATH =  \
    ./ \
    ./model \
    ./view \
    ./controller \
    ./gifimage \
    ./3rdParty \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
