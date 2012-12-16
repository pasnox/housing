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

    exists( $${FRESH_BUNDLE_PATH}/fresh.pro ) {
        SUBDIRS *= $${FRESH_BUNDLE_PATH}/fresh.pro
        !build_pass:message( "Using bundled fresh library (1)." )
    } else:exists( $${_PRO_FILE_PWD_}/$${FRESH_BUNDLE_PATH}/fresh.pro ) {
        SUBDIRS *= $${_PRO_FILE_PWD_}/$${FRESH_BUNDLE_PATH}/fresh.pro
        !build_pass:message( "Using bundled fresh library (2)." )
    } else {
        !build_pass:error( "Fresh library not found - Execute: git submodule init && git submodule update." )
    }
}