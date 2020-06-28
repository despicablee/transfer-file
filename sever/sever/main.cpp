#include "severdialog.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForTr( QTextCodec::codecForName("gb2312"));
	SeverDialog w;
	w.show();
	return a.exec();
}
