###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
##
##  Author    : Filipe Azevedo aka Nox PasNox <pasnox@gmail.com>
##  Project   : housing
##  FileName  : installs.pri
##  Date      : 2012-11-15T18:57:50
##  License   : GPL3
##  Comment   : Creating using Monkey Studio RAD
##  Home Page : https://github.com/pasnox/housing
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

unix {
	PACKAGE_PREFIX = $${PREFIX}
	isEmpty( PACKAGE_PREFIX ) {
		macx:PACKAGE_PREFIX	= /Applications
		else:PACKAGE_PREFIX = /usr/local
	}
	
	!build_pass {
		unix:!macx:CAN_INSTALL	= 1
		else:macx:isEqual( MAC_FULL_INSTALL, 1 ):CAN_INSTALL	= 1
		
		isEqual( CAN_INSTALL, 1 ) {
			message( "The application will be installed to $${PACKAGE_PREFIX}" )
			message( "You can overwrite the prefix calling qmake with parameter: qmake PREFIX=/usr" )
		} else:macx {
			message( "The application bundle will not be installed into $${PACKAGE_PREFIX}." )
			message( "Call: 'qmake MAC_FULL_INSTALL=1' for install the bundle." )
		}
	}
	
	macx:application_translations.path	= $${DESTDIR}/$${TARGET}.app/Contents/Resources/translations
	else:application_translations.path	=	$$[QT_INSTALL_TRANSLATIONS]
	application_translations.files	= $${PWD}/../translations/*.qm
	
	INSTALLS	= application_translations
	
	exists( $${PWD}/3rdparty/fresh.git/fresh.pro ) {
		FRESH_LIBRARY_PATH = $${PWD}/3rdparty/fresh.git
	}
	
	!isEmpty( FRESH_LIBRARY_PATH ) {
		macx:fresh_translations.path	= $${DESTDIR}/$${TARGET}.app/Contents/Resources/translations
		else:fresh_translations.path	=	$$[QT_INSTALL_TRANSLATIONS]
		fresh_translations.files	= $${FRESH_LIBRARY_PATH}/translations/*.qm
		
		INSTALLS	*= fresh_translations
	}
	
	macx {
		application_qt_translations.path	= $${DESTDIR}/$${TARGET}.app/Contents/Resources/qt/translations
		application_qt_translations.files	= $$[QT_INSTALL_TRANSLATIONS]/qt_??.qm
		application_qt_translations.files	*= $$[QT_INSTALL_TRANSLATIONS]/qt_??_??.qm
		
		INSTALLS	*= application_qt_translations
	}
}

unix:!macx {
	# binary
	application_target.path	= $${PACKAGE_PREFIX}/bin
	isShadowBuild():application_target.files	= $${OUT_PWD}/$${DESTDIR}/$${TARGET}
	else:application_target.files	= $${DESTDIR}/$${TARGET}
	application_target.CONFIG *= no_check_exist
	
	message( $$application_target.files )

	# desktop file
	application_desktop.path	= $${PACKAGE_PREFIX}/share/applications
	application_desktop.files	= ../packaging/$${TARGET}.desktop

	# desktop icon file
	#application_desktopicon.path	= $${PACKAGE_PREFIX}/share/icons/hicolor/256x256/apps
	#application_desktopicon.files	= $$PWD/resources/$${TARGET}.png

	INSTALLS	*= application_target application_desktop application_desktopicon
}

macx {
	# binary
	application_target.path	= $${PACKAGE_PREFIX}
	application_target.files	= $${DESTDIR}/$${TARGET}.app
	application_target.CONFIG *= no_check_exist
	
	isEqual( MAC_FULL_INSTALL, 1 ):INSTALLS	*= application_target
}
