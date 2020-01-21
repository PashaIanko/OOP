#include "Controller.h"
#include "DownloadCmd.h"
#include "BlurCmd.h"
#include <opencv2/core/types_c.h>


Controller:: Controller()
	: gui(new GUI), image(new Model) {
}

void Controller::DownloadImage() {
	std::shared_ptr<Command> cmd_ptr = std::make_shared<DownloadCmd>();
	cmd_ptr->execute(image);
}

void Controller::launch_GUI() {
	gui->show();
	connect_gui_signals();
}

void Controller::ApplyBlurFilter() {
	std::shared_ptr<Command> cmd_ptr = std::make_shared<BlurCmd>(cv::Size(5, 5));
	cmd_ptr->execute(image);
}



void Controller::connect_gui_signals(){
	connect(gui.get(), SIGNAL(Download()), this, SLOT(DownloadImage()));
	connect(gui.get(), SIGNAL(Blur()), this, SLOT(ApplyBlurFilter()));
}
