#include <QKeyEvent>
#include <QMultiHash>

class KeyTool
{
public:
	KeyTool();

	// Make keynum in QKeyEvent equivalent to what's in QKeySequence
	// The 0.27 version
	int	translateKeynum27(QKeyEvent* ev);

	void	addKeySequence(QString& seq);
	void	findKeySequence(QKeyEvent* ev);
	void	findKeySequence(int keynum);

private:
	QMultiHash<int, QString> keybindings;
};
