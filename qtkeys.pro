
TEMPLATE = app
CONFIG += qt debug qt$${QT_MAJOR_VERSION}
QMAKE_CLEAN += $(TARGET)

message( "QT_MAJOR_VERSION = $${QT_MAJOR_VERSION}" )

qt5 {
    QT += widgets
}

SOURCES += main.cpp mywin.h mywin.cpp keytool.cpp
