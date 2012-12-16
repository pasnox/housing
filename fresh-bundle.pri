win32_crossbuild {
    exists( "$(QT_WIN32_PATH)/lib/*fresh*" ):CONFIG *= fresh
} else {
    exists( "$$[QT_INSTALL_LIBS]/*fresh*" ):CONFIG *= fresh
}

fresh {
    !build_pass:message( "Using system fresh library." )
} else {
    isEmpty( FRESH_BUNDLE_PATH ) {
        !build_pass:error( "FRESH_BUNDLE_PATH is empty. Please declare this variable before include this file" )
    }

    isEmpty( FRESH_BUNDLE_LIB_PATH ) {
        !build_pass:error( "FRESH_BUNDLE_LIB_PATH is empty. Please declare this variable before include this file" )
    }

    exists( $${FRESH_BUNDLE_PATH}/fresh.pro ) {
        !build_pass:message( "Using bundled fresh library (1)." )

        include( $${FRESH_BUNDLE_PATH}/qmake-extensions.git/qmake-extensions.pri )

        FRESH_SOURCES_PATHS = $$getFolders( $${FRESH_BUNDLE_PATH}/src )
    } else:exists( $${_PRO_FILE_PWD_}/$${FRESH_BUNDLE_PATH}/fresh.pro ) {
        !build_pass:message( "Using bundled fresh library (2)." )

        include( $${_PRO_FILE_PWD_}/$${FRESH_BUNDLE_PATH}/qmake-extensions.git/qmake-extensions.pri )
        
        isShadowBuild() {
            FRESH_SOURCES_PATHS = $$getFolders( $${_PRO_FILE_PWD_}/$${FRESH_BUNDLE_PATH}/src )
        } else {
            FRESH_SOURCES_PATHS = $$getRelativeFolders( $${_PRO_FILE_PWD_}/$${FRESH_BUNDLE_PATH}/src, $${_PRO_FILE_PWD_}/ )
        }
    } else {
        !build_pass:error( "Fresh library not found - Execute: git submodule init && git submodule update." )
    }
    
    DEFINES *= FRESH_CORE_BUILD

    DEPENDPATH *= $${FRESH_SOURCES_PATHS}
    DEPENDPATH *= $${FRESH_BUNDLE_PATH}/include/FreshCore \
        $${FRESH_BUNDLE_PATH}/include/FreshGui

    INCLUDEPATH *= $${FRESH_BUNDLE_PATH}/include
    INCLUDEPATH *= $${FRESH_SOURCES_PATHS}

    QMAKE_RPATHDIR *= $${FRESH_BUNDLE_LIB_PATH}/build
    macx:LIBS *= -F$${FRESH_BUNDLE_LIB_PATH}/build
    LIBS *= -L$${FRESH_BUNDLE_LIB_PATH}/build

    QT *= xml network
    !macx:qtAddLibrary( fresh )
    macx:LIBS *= -lfresh
}