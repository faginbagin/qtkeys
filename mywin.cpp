#include <QApplication>
#include <QTextStream>
#include "mywin.h"

MyWin::MyWin(KeyTool* kt) : keytool(kt)
{
	setFocusPolicy(Qt::StrongFocus);
	resize(320, 240);
	show();
	setWindowTitle(QApplication::translate("toplevel", "QT Events"));
}

void
MyWin::keyPressEvent(QKeyEvent* ev)
{
	QTextStream out(stdout);
	out << hex << showbase;
	out << "key=" << ev->key() << " modifiers=" << hex << showbase << ev->modifiers() << endl;
	//out << "   text=" << ev->text();
	out << "   count=" << ev->count() << " isAutoRepeat=" << ev->isAutoRepeat() << endl;
	out << "   nativeModifiers=" << ev->nativeModifiers() << " nativeScanCode=" << ev->nativeScanCode() << " nativeVirtualKey=" << ev->nativeVirtualKey() << endl;
	keytool->findKeySequence(ev);
	QWidget::keyPressEvent(ev);
	out << endl;
}

