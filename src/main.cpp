#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("CP1251"));

	MainWindow w;
	w.show();

	return a.exec();
}
