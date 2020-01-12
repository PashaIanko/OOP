#include "Controller.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Controller w;
	w.launch_GUI();
	//w.show();
	
	return a.exec();
}
