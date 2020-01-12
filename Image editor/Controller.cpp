#include "Controller.h"
#include "DownloadCmd.h"

Controller:: Controller(QWidget *parent)
	: QMainWindow(parent), GUI(new View), image(new Model)
{
	QPushButton* downld_button = new QPushButton("Download", this);
	downld_button->setGeometry(QRect(QPoint(0, 0), QSize(100, 25)));
	connect(downld_button, SIGNAL(clicked()), this, SLOT(DownloadImage()));
	buttons.push_back(downld_button);

	GUI->set_model(image);
}

void Controller::DownloadImage() {
	std::shared_ptr<Command> cmd_ptr = std::make_shared<DownloadCmd>();
	cmd_ptr->execute(image);
}

void Controller::set_model(const std::string &dir) {
	image->set_image(dir);
}
