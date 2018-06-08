#include <QWidget>
#include "keytool.h"

class MyWin : public QWidget
{
public:
	MyWin(KeyTool* keytool);
	void keyPressEvent(QKeyEvent* ev);
private:
	KeyTool* keytool;
};

