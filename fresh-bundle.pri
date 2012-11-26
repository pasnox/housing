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
        !build_pass:message( "Using bundled fresh library." )

        include( $${FRESH_BUNDLE_PATH}/qmake-extensions.git/qmake-extensions.pri )

        Q_PWD = $${PWD}
        Q_ENV_PWD = $$(PWD)
        !isEqual( Q_PWD, $${Q_ENV_PWD} ):FRESH_BUNDLE_PATH = "$${PWD}/$${FRESH_BUNDLE_PATH}"
        FRESH_SOURCES_PATHS = $$getFolders( $${FRESH_BUNDLE_PATH}/src )

        DEFINES *= FRESH_CORE_BUILD

        DEPENDPATH *= $${FRESH_SOURCES_PATHS}
        DEPENDPATH *= $${FRESH_BUNDLE_PATH}/include/FreshCore \
            $${FRESH_BUNDLE_PATH}/include/FreshGui

        INCLUDEPATH *= $${FRESH_BUNDLE_PATH}/include
        INCLUDEPATH *= $${FRESH_SOURCES_PATHS}

        PRE_TARGETDEPS *= $${FRESH_BUNDLE_PATH}

        QMAKE_RPATHDIR *= $${FRESH_BUNDLE_LIB_PATH}/build
        macx:LIBS *= -F$${FRESH_BUNDLE_LIB_PATH}/build
        LIBS *= -L$${FRESH_BUNDLE_LIB_PATH}/build

        QT *= xml network
        !macx:qtAddLibrary( fresh )
        macx:LIBS *= -lfresh
    } else {
        !build_pass:error( "Fresh library not found - Execute: git submodule init && git submodule update." )
    }
}