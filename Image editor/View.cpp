#include "GUI.h"
#include "Controller.h"
#include <QLabel>

GUI::GUI(QWidget * parent) {
	resize(200, 200);
	QPushButton* download_button = new QPushButton("Download", this);
	download_button->setGeometry(QRect(QPoint(0, 0), QSize(100, 25)));
	connect(download_button, SIGNAL(clicked()), this, SLOT(DownloadButtonPushed()));

}

void GUI::DownloadButtonPushed() {
	emit ButtonPushed();
}
