###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
##
##  Author    : You Name <your@email.org>
##  Project   : housing
##  FileName  : housing.pro
##  Date      : 2012-11-15T18:57:50
##  License   : GPL
##  Comment   : Creating using Monkey Studio RAD
##  Home Page : http://www.mydomain.org
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

XUP.QT_VERSION = Qt System (4.8.3)
XUP.TRANSLATIONS_BASENAME = housing
XUP.TRANSLATIONS_DIRECTORY = translations
XUP.OTHERS_PLATFORM_TARGET_DEFAULT = /ramdisk/housing/housing

TEMPLATE = app
LANGUAGE = C++/Qt4
TARGET = $$quote(housing)
CONFIG *= release
CONFIG -= debug debug_and_release
QT *= network webkit xml xmlpatterns
BUILD_PATH = ./build

INCLUDEPATH *= src
DEPENDPATH *= src \
    src/interface \
    src/seloger \
    src/widgets

CONFIG(debug, debug|release) {
    #Debug
    CONFIG *= console
    unix:TARGET = $$join(TARGET,,,_debug)
    else:TARGET = $$join(TARGET,,,d)
    unix:OBJECTS_DIR = $${BUILD_PATH}/debug/.obj/unix
    win32:OBJECTS_DIR = $${BUILD_PATH}/debug/.obj/win32
    mac:OBJECTS_DIR = $${BUILD_PATH}/debug/.obj/mac
    UI_DIR = $${BUILD_PATH}/debug/.ui
    MOC_DIR = $${BUILD_PATH}/debug/.moc
    RCC_DIR = $${BUILD_PATH}/debug/.rcc
} else {
    #Release
    unix:OBJECTS_DIR = $${BUILD_PATH}/release/.obj/unix
    win32:OBJECTS_DIR = $${BUILD_PATH}/release/.obj/win32
    mac:OBJECTS_DIR = $${BUILD_PATH}/release/.obj/mac
    UI_DIR = $${BUILD_PATH}/release/.ui
    MOC_DIR = $${BUILD_PATH}/release/.moc
    RCC_DIR = $${BUILD_PATH}/release/.rcc
}

include( src/3rdparty/qjson.pri )

RESOURCES *= resources/housing.qrc

TRANSLATIONS *= translations/housing_fr_FR.ts \
    translations/housing_en_US.ts

FORMS *= src/UIMain.ui \
    src/widgets/CitySearchWidget.ui \
    src/widgets/InputSearchWidget.ui \
    src/widgets/AnnouncementWidget.ui

HEADERS *= src/NetworkManager.h \
    src/interface/City.h \
    src/interface/CityModel.h \
    src/interface/AbstractCityQuery.h \
    src/seloger/SeLogerCityQuery.h \
    src/UIMain.h \
    src/widgets/CityComboBox.h \
    src/Housing.h \
    src/widgets/CitySearchWidget.h \
    src/interface/AbstractHousingDriver.h \
    src/seloger/SeLogerHousingDriver.h \
    src/interface/AnnouncementModel.h \
    src/interface/Announcement.h \
    src/widgets/InputSearchWidget.h \
    src/widgets/AnnouncementWidget.h \
    src/widgets/pComboBox.h \
    src/interface/AnnouncementItemDelegate.h \
    src/widgets/AnnouncementView.h

SOURCES *= src/main.cpp \
    src/NetworkManager.cpp \
    src/interface/City.cpp \
    src/interface/CityModel.cpp \
    src/interface/AbstractCityQuery.cpp \
    src/seloger/SeLogerCityQuery.cpp \
    src/UIMain.cpp \
    src/widgets/CityComboBox.cpp \
    src/Housing.cpp \
    src/widgets/CitySearchWidget.cpp \
    src/interface/AbstractHousingDriver.cpp \
    src/seloger/SeLogerHousingDriver.cpp \
    src/interface/AnnouncementModel.cpp \
    src/interface/Announcement.cpp \
    src/widgets/InputSearchWidget.cpp \
    src/widgets/AnnouncementWidget.cpp \
    src/widgets/pComboBox.cpp \
    src/interface/AnnouncementItemDelegate.cpp \
    src/widgets/AnnouncementView.cpp