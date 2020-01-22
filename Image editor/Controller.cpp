#include "Controller.h"
#include "DownloadCmd.h"
#include "BlurCmd.h"
#include "SaveCmd.h"
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

void Controller::SaveImage() {
	std::shared_ptr<Command> cmd_ptr = std::make_shared<SaveCmd>(result_image_name);
	cmd_ptr->execute(image);
}

void Controller::BlurFilterImage(int blur_intensity) {
	std::shared_ptr<Command> cmd_ptr = std::make_shared<BlurCmd>(blur_intensity);
	cmd_ptr->execute(image);
}



void Controller::connect_gui_signals(){

	connect(gui.get(), SIGNAL(Download()), this, SLOT(DownloadImage()));
	connect(gui.get(), SIGNAL(BlurLevel(int)), this, SLOT(BlurFilterImage(int)));
	connect(gui.get(), SIGNAL(Save()), this, SLOT(SaveImage()));
}
