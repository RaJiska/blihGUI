# TODO: Clean Lib

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blihGUI
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -g3

LIBS = -lcurl -lcrypto

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
		src/main.cpp \
		src/BlihAPI.cpp \
		src/Credentials.cpp \
		src/MainWindow.cpp

HEADERS += \
		include/BlihGUI.hpp \
		include/BlihAPI.hpp \
		include/Credentials.hpp \
		include/MainWindow.hpp


# Lib JSON
libJSON.target = libJSON
libJSON.commands = cp lib/json/json.hpp include/json.hpp

PRE_TARGETDEPS += libJSON
QMAKE_EXTRA_TARGETS += libJSON