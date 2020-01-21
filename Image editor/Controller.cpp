#include "Controller.h"
#include "DownloadCmd.h"
#include <opencv2/core/types_c.h>
//#include <cv.h>

Controller:: Controller()
	: GUI(new View), image(new Model)
{
	GUI->set_model(image);
}

void Controller::DownloadImage() {
	std::shared_ptr<Command> cmd_ptr = std::make_shared<DownloadCmd>();
	cmd_ptr->execute(image);
	GUI->update();
}

void Controller::launch_GUI() {
	GUI->show();
	cv::namedWindow("Your Image");
	connect_view_signals();
}


void Controller::set_model(const std::string &dir) {
	image->set_image(dir);
}

void Controller::connect_view_signals(){
	connect(GUI.get(), SIGNAL(ButtonPushed()), this, SLOT(DownloadImage()));
}
