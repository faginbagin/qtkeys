#include "mywin.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	KeyTool keytool;
	for (int i = 1; i < argc; i++)
		keytool.addKeySequence(argv[i]);

	MyWin window(&keytool);
	return app.exec();
}

