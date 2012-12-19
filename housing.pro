###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
##
##  Author    : Filipe Azevedo aka Nox PasNox <pasnox@gmail.com>
##  Project   : housing
##  FileName  : housing.pro
##  Date      : 2012-11-15T18:57:50
##  License   : GPL3
##  Comment   : Creating using Monkey Studio RAD
##  Home Page : https://github.com/pasnox/housing
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

XUP.QT_VERSION = Qt System (4.8.3)
XUP.OTHERS_PLATFORM_TARGET_DEFAULT = /ramdisk/housing/housing

TEMPLATE = subdirs
CONFIG *= ordered

FRESH_BUNDLE_PATH = src/3rdparty/fresh.git
include( fresh-bundle-check.pri )

SUBDIRS *= src/src.pro