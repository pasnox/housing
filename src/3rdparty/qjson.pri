QJSON_LIB	= $$PWD/qjson.git
win32:DEFINES *= QJSON_EXPORT=

INCLUDEPATH	*= $${QJSON_LIB}/src
DEPENDPATH	*= $${QJSON_LIB}/src

HEADERS	*= $${QJSON_LIB}/src/json_parser.hh \
	$${QJSON_LIB}/src/json_scanner.h \
	$${QJSON_LIB}/src/location.hh \
	$${QJSON_LIB}/src/parser_p.h \
	$${QJSON_LIB}/src/parser.h \
	$${QJSON_LIB}/src/parserrunnable.h \
	$${QJSON_LIB}/src/position.hh \
	$${QJSON_LIB}/src/qjson_debug.h \
	$${QJSON_LIB}/src/qjson_export.h \
	$${QJSON_LIB}/src/qobjecthelper.h \
	$${QJSON_LIB}/src/serializer.h \
	$${QJSON_LIB}/src/serializerrunnable.h \
	$${QJSON_LIB}/src/stack.hh

SOURCES	*= $${QJSON_LIB}/src/json_parser.cc \
	$${QJSON_LIB}/src/json_scanner.cpp \
	$${QJSON_LIB}/src/parser.cpp \
	$${QJSON_LIB}/src/parserrunnable.cpp \
	$${QJSON_LIB}/src/qobjecthelper.cpp \
	$${QJSON_LIB}/src/serializer.cpp \
	$${QJSON_LIB}/src/serializerrunnable.cpp
