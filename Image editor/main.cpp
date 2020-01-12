#include "Controller.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Controller w;
	w.show();
	
	return a.exec();
}
