DEPENDPATH *= $${PWD}/fresh.git

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000500
VPATH *= $${PWD}/fresh.git
FILES = $$files($${PWD}/fresh.git/*, true)
for(file, FILES) {
    INCLUDEPATH *= $$dirname(file)
}

include( $${PWD}/fresh.git/fresh.pro )
unset( INSTALLS )
