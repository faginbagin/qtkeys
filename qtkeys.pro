
CONFIG += qt debug qt$${QT_MAJOR_VERSION}

message( "QT_MAJOR_VERSION = $${QT_MAJOR_VERSION}" )

qt4 {
	SOURCES += main.cpp
}

SOURCES += mywin.h mywin.cpp keytool.cpp
