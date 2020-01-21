#include "View.h"
#include "Controller.h"
#include <QLabel>

View::View(QWidget * parent) {
	resize(200, 200);
	QPushButton* download_button = new QPushButton("Download", this);
	download_button->setGeometry(QRect(QPoint(0, 0), QSize(100, 25)));
	connect(download_button, SIGNAL(clicked()), this, SLOT(DownloadButtonPushed()));

}

void View::set_model(const std::shared_ptr<Model>& new_model) {
	model = new_model;
}

void View::update(){
	cv::imshow("Your Image", model->get_image());
}

void View::DownloadButtonPushed() {
	emit ButtonPushed();
}
