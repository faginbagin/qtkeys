
TEMPLATE = app
CONFIG += qt debug qt$${QT_MAJOR_VERSION}
QMAKE_CLEAN += $(TARGET)

message( "QT_MAJOR_VERSION = $${QT_MAJOR_VERSION}" )

qt4 {
	SOURCES += main.cpp
}

SOURCES += mywin.h mywin.cpp keytool.cpp
