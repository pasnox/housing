###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
##
##  Author    : Filipe Azevedo aka Nox PasNox <pasnox@gmail.com>
##  Project   : housing
##  FileName  : housing.pro
##  Date      : 2012-11-15T18:57:50
##  License   : GPL
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

win32_crossbuild {
    exists( "$(QT_WIN32_PATH)/lib/*fresh*" ):CONFIG *= fresh
} else {
    exists( "$$[QT_INSTALL_LIBS]/*fresh*" ):CONFIG *= fresh
}

fresh {
    !build_pass:message( "Using system fresh library." )
} else {
    exists( src/3rdparty/fresh.git/fresh.pro ) {
        SUBDIRS *= src/3rdparty/fresh.git/fresh.pro
        !build_pass:message( "Using bundled fresh library." )
    } else {
        !build_pass:error( "Fresh library not found - Execute: git submodule init && git submodule update." )
    }
}

SUBDIRS *= src/src.pro