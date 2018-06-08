#include <QTextStream>
#include "keytool.h"

KeyTool::KeyTool()
{
}

// Make keynum in QKeyEvent equivalent to what's in QKeySequence
// The 0.21 version
int
KeyTool::translateKeynum21(QKeyEvent* e)
{
    int keynum = e->key();

    if (keynum != Qt::Key_Escape &&
        (keynum <  Qt::Key_Shift || keynum > Qt::Key_ScrollLock))
    {
        // if modifiers have been pressed, rebuild keynum
#if QT_VERSION < 0x040000
        Qt::ButtonState modifiers;
        modifiers = e->state();
#else
        Qt::KeyboardModifiers modifiers;
        modifiers = e->modifiers();
#endif
        if (modifiers != 0)
        {
#if QT_VERSION < 0x040000
            int modnum = (((modifiers & Qt::ShiftButton) &&
                           keynum > 0x7f) ? Qt::SHIFT : 0) |
                         ((modifiers & Qt::ControlButton) ? Qt::CTRL : 0) |
                         ((modifiers & Qt::MetaButton) ? Qt::META : 0) |
                         ((modifiers & Qt::AltButton) ? Qt::ALT : 0);
#else
            int modnum = (((modifiers & Qt::ShiftModifier) &&
                           keynum > 0x7f) ? Qt::SHIFT : 0) |
                         ((modifiers & Qt::ControlModifier) ? Qt::CTRL : 0) |
                         ((modifiers & Qt::MetaModifier) ? Qt::META : 0) |
                         ((modifiers & Qt::AltModifier) ? Qt::ALT : 0);
#endif
            modnum &= ~Qt::UNICODE_ACCEL;
            return (keynum |= modnum);
        }
    }

    return keynum;
}

// The 0.22 version
int
KeyTool::translateKeynum22(QKeyEvent* e)
{
    int keynum = e->key();

    if (keynum != Qt::Key_Escape &&
        (keynum <  Qt::Key_Shift || keynum > Qt::Key_ScrollLock))
    {
        Qt::KeyboardModifiers modifiers;
        // if modifiers have been pressed, rebuild keynum
        if ((modifiers = e->modifiers()) != Qt::NoModifier)
        {
            int modnum = (((modifiers & Qt::ShiftModifier) &&
                            (keynum > 0x7f) &&
                            (keynum != Qt::Key_Backtab)) ? Qt::SHIFT : 0) |
                         ((modifiers & Qt::ControlModifier) ? Qt::CTRL : 0) |
                         ((modifiers & Qt::MetaModifier) ? Qt::META : 0) |
                         ((modifiers & Qt::AltModifier) ? Qt::ALT : 0);
            modnum &= ~Qt::UNICODE_ACCEL;
            return (keynum |= modnum);
        }
    }

    return keynum;
}

void
KeyTool::addKeySequence(const char* str)
{
	QString seq = QObject::tr(str);
	QKeySequence keyseq(seq);

	for (unsigned int i = 0; i < keyseq.count(); i++)
	{
		int keynum = keyseq[i];
		keynum &= ~Qt::UNICODE_ACCEL;
		keybindings.insert(keynum, seq);
	}
}

void
KeyTool::findKeySequence(QKeyEvent* ev)
{
	int key21 = translateKeynum21(ev);
	int key22 = translateKeynum22(ev);

	if (key21 != key22)
	{
		QTextStream out(stdout);
		out << hex << showbase;
		out << "0.21 keynum=" << key21 << " does not equal 0.22 keynum=" << key22 << endl;
		findKeySequence(key21);
	}
	findKeySequence(key22);
}

void
KeyTool::findKeySequence(int keynum)
{
	QTextStream out(stdout);
	int count = keybindings.count(keynum);
	out << hex << showbase;
	out << "keynum=" << keynum << " matches " << count << " key sequences:" << endl;
		
	QMultiHash<int, QString>::iterator iter = keybindings.find(keynum);
	int i = 0;
	while (iter != keybindings.end() && iter.key() == keynum)
	{
		out << i << ": sequence=" << iter.value() << endl;
		i++;
		iter++;
	}
}
