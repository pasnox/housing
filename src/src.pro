###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
##
##  Author    : Filipe Azevedo aka Nox PasNox <pasnox@gmail.com>
##  Project   : housing
##  FileName  : src.pro
##  Date      : 2012-11-15T18:57:50
##  License   : GPL3
##  Comment   : Creating using Monkey Studio RAD
##  Home Page : https://github.com/pasnox/housing
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

XUP.TRANSLATIONS_BASENAME = housing
XUP.TRANSLATIONS_DIRECTORY = ../translations

TEMPLATE = app
LANGUAGE = C++/Qt4
TARGET = $$quote(housing)
DESTDIR = ..
CONFIG *= release
CONFIG -= debug debug_and_release
QT *= network xml xmlpatterns
!blackberry:QT *= webkit
BUILD_PATH = ../build

INCLUDEPATH *= .
DEPENDPATH *= . \
    interface \
    seloger \
    objects \
    widgets

CONFIG(debug, debug|release) {
    #Debug
    CONFIG *= console
    unix:TARGET = $$join(TARGET,,,_debug)
    else:TARGET = $$join(TARGET,,,d)
    unix:OBJECTS_DIR = $${BUILD_PATH}/debug/obj/unix
    win32:OBJECTS_DIR = $${BUILD_PATH}/debug/obj/win32
    mac:OBJECTS_DIR = $${BUILD_PATH}/debug/obj/mac
    UI_DIR = $${BUILD_PATH}/debug/ui
    MOC_DIR = $${BUILD_PATH}/debug/moc
    RCC_DIR = $${BUILD_PATH}/debug/rcc
} else {
    #Release
    unix:OBJECTS_DIR = $${BUILD_PATH}/release/obj/unix
    win32:OBJECTS_DIR = $${BUILD_PATH}/release/obj/win32
    mac:OBJECTS_DIR = $${BUILD_PATH}/release/obj/mac
    UI_DIR = $${BUILD_PATH}/release/ui
    MOC_DIR = $${BUILD_PATH}/release/moc
    RCC_DIR = $${BUILD_PATH}/release/rcc
}

isEqual( _PRO_FILE_PWD_, $${OUT_PWD} ) {
    FRESH_BUNDLE_PATH = 3rdparty/fresh.git
    FRESH_BUNDLE_LIB_PATH = 3rdparty/fresh.git
} else {
    FRESH_BUNDLE_PATH = $${_PRO_FILE_PWD_}/3rdparty/fresh.git
    FRESH_BUNDLE_LIB_PATH = $${OUT_PWD}/3rdparty/fresh.git
}

include( ../fresh-bundle.pri )
include( 3rdparty/qjson.pri )
include( installs.pri )

#PRE_TARGETDEPS *= $${FRESH_BUNDLE_PATH}

RESOURCES *= ../resources/housing.qrc

TRANSLATIONS *= \
    ../translations/housing_fr_FR.ts \
    ../translations/housing_en_US.ts

blackberry {
    DEFINES *= MOBILE_UI
    FORMS *= mainwindow/UIMobileMain.ui
    HEADERS *= mainwindow/UIMobileMain.h
    SOURCES *= mainwindow/UIMobileMain.cpp
} else {
    DEFINES *= DESKTOP_UI
    FORMS *= mainwindow/UIDesktopMain.ui
    HEADERS *= mainwindow/UIDesktopMain.h
    SOURCES *= mainwindow/UIDesktopMain.cpp
}

FORMS *=  \
    widgets/CitySearchWidget.ui \
    widgets/InputSearchWidget.ui \
    widgets/AnnouncementWidget.ui \
    widgets/FeedbackWidget.ui \
    widgets/FeedbackDialog.ui

HEADERS *=  \
    mainwindow/UIMain_p.h \
    objects/NetworkManager.h \
    objects/Housing.h \
    interface/City.h \
    interface/CityModel.h \
    interface/Announcement.h \
    interface/AnnouncementModel.h \
    interface/AnnouncementProxyModel.h \
    interface/AnnouncementItemDelegate.h \
    interface/AbstractCityQuery.h \
    interface/AbstractHousingDriver.h \
    interface/Feedback.h \
    interface/FeedbackModel.h \
    interface/FeedbackItemDelegate.h \
    seloger/SeLogerCityQuery.h \
    seloger/SeLogerHousingDriver.h \
    widgets/CityComboBox.h \
    widgets/CitySearchWidget.h \
    widgets/InputSearchWidget.h \
    widgets/AnnouncementWidget.h \
    widgets/AnnouncementView.h \
    widgets/FeedbackWidget.h \
    widgets/FeedbackDialog.h

SOURCES *=  \
    main.cpp \
    objects/NetworkManager.cpp \
    objects/Housing.cpp \
    interface/City.cpp \
    interface/CityModel.cpp \
    interface/Announcement.cpp \
    interface/AnnouncementModel.cpp \
    interface/AnnouncementProxyModel.cpp \
    interface/AnnouncementItemDelegate.cpp \
    interface/AbstractCityQuery.cpp \
    interface/AbstractHousingDriver.cpp \
    interface/Feedback.cpp \
    interface/FeedbackModel.cpp \
    interface/FeedbackItemDelegate.cpp \
    seloger/SeLogerCityQuery.cpp \
    seloger/SeLogerHousingDriver.cpp \
    widgets/CityComboBox.cpp \
    widgets/CitySearchWidget.cpp \
    widgets/InputSearchWidget.cpp \
    widgets/AnnouncementWidget.cpp \
    widgets/AnnouncementView.cpp \
    widgets/FeedbackWidget.cpp \
    widgets/FeedbackDialog.cpp
