#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T18:18:33
#
#-------------------------------------------------

QT       += widgets
QT       += core            # 随机数生成器需要。不加入此库，则永远只能得到固定的数，即使头文件里引入了qrandom.h

# 加入此项配置，以使得编译的库能作为插件被加载
# 若缺少，则dde-dock会提示：
# load plugin failed!!! "无法加载库/usr/lib/dde-dock/plugins/libDDE_BasicDock.so：(/usr/lib/dde-dock/plugins/libDDE_BasicDock.so: undefined symbol: _ZTV13DDE_BasicDock)" "/usr/lib/dde-dock/plugins/libDDE_BasicDock.so"
# 其余细节参见dde_basicdock.h。
CONFIG   += plugin

TARGET = DDE_BasicDock
TEMPLATE = lib

DEFINES += DDE_BASICDOCK_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        dde_basicdock.cpp \
    dde_basicdockplugin.cpp

HEADERS += \
        dde_basicdock.h \
    dde_basicdockplugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    res.qrc

DISTFILES += \
    basicDock.json
