#include "View.h"

#include "Controller.h"

View::View(QWidget * parent) {
	download_button = new QPushButton("Download", this);
	download_button->setGeometry(QRect(QPoint(0, 0), QSize(100, 25)));
}

void View::set_model(const std::shared_ptr<Model>& new_model) {
	model = new_model;
}

QPushButton * View::get_button()
{
	return download_button;
}
