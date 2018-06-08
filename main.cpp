#include "mywin.h"

void readFile(const char* fileName, KeyTool& keytool)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            keytool.addKeySequence(line);
        }
    }
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	KeyTool keytool;
	for (int i = 1; i < argc; i++)
		readFile(argv[i], keytool);

	MyWin window(&keytool);
	return app.exec();
}

