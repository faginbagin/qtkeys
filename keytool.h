#include <QKeyEvent>
#include <QMultiHash>

class KeyTool
{
public:
	KeyTool();

	// Make keynum in QKeyEvent equivalent to what's in QKeySequence
	// The 0.21 version
	int	translateKeynum21(QKeyEvent* ev);
	// The 0.22 version
	int	translateKeynum22(QKeyEvent* ev);

	void	addKeySequence(const char* seq);
	void	findKeySequence(QKeyEvent* ev);
	void	findKeySequence(int keynum);

private:
	QMultiHash<int, QString> keybindings;
};
