#include <QTextStream>
#include "keytool.h"

KeyTool::KeyTool()
{
}

// Make keynum in QKeyEvent equivalent to what's in QKeySequence
// The 0.27 version
int
KeyTool::translateKeynum27(QKeyEvent* e)
{
    int keynum = e->key();

    if ((keynum != Qt::Key_Shift  ) && (keynum !=Qt::Key_Control   ) &&
        (keynum != Qt::Key_Meta   ) && (keynum !=Qt::Key_Alt       ) &&
        (keynum != Qt::Key_Super_L) && (keynum !=Qt::Key_Super_R   ) &&
        (keynum != Qt::Key_Hyper_L) && (keynum !=Qt::Key_Hyper_R   ) &&
        (keynum != Qt::Key_AltGr  ) && (keynum !=Qt::Key_CapsLock  ) &&
        (keynum != Qt::Key_NumLock) && (keynum !=Qt::Key_ScrollLock ))
    {
        Qt::KeyboardModifiers modifiers;
        // if modifiers have been pressed, rebuild keynum
        if ((modifiers = e->modifiers()) != Qt::NoModifier)
        {
            int modnum = (((modifiers & Qt::ShiftModifier) &&
                            (keynum > 0x7f) &&
                            (keynum != Qt::Key_Backtab)) ? (int)Qt::SHIFT : 0) |
                         ((modifiers & Qt::ControlModifier) ? (int)Qt::CTRL : 0) |
                         ((modifiers & Qt::MetaModifier) ? (int)Qt::META : 0) |
                         ((modifiers & Qt::AltModifier) ? (int)Qt::ALT : 0);
            modnum &= ~Qt::UNICODE_ACCEL;
            return (keynum |= modnum);
        }
    }

    return keynum;
}

void
KeyTool::addKeySequence(QString& seq)
{
	QKeySequence keyseq(seq);

	QTextStream out(stdout);
    out << "add: \"" << seq << "\" keynums:";
    out << hex << showbase;

	for (int i = 0; i < keyseq.count(); i++)
	{
		int keynum = keyseq[i];
		keynum &= ~Qt::UNICODE_ACCEL;
		keybindings.insert(keynum, seq);
        out << " " << keynum;
	}
    out << endl;
}

void
KeyTool::findKeySequence(QKeyEvent* ev)
{
	int key27 = translateKeynum27(ev);

	findKeySequence(key27);
}

void
KeyTool::findKeySequence(int keynum)
{
	QTextStream out(stdout);
	int count = keybindings.count(keynum);
	out << hex << showbase;
	out << "keynum=" << keynum << "," << QKeySequence(keynum).toString() <<
        " matches " << count << " key sequences:" << endl;
		
	QMultiHash<int, QString>::iterator iter = keybindings.find(keynum);
	int i = 0;
	while (iter != keybindings.end() && iter.key() == keynum)
	{
		out << i << ": sequence=" << iter.value() << endl;
		i++;
		iter++;
	}
}
