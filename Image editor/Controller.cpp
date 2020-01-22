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
	std::shared_ptr<Command> cmd_ptr = std::make_shared<SaveCmd>("/Result.jpg");
	cmd_ptr->execute(image);
}

void Controller::Apply(int level) {
	std::shared_ptr<Command> cmd_ptr = std::make_shared<BlurCmd>(level);
	cmd_ptr->execute(image);
}



void Controller::connect_gui_signals(){

	connect(gui.get(), SIGNAL(Download()), this, SLOT(DownloadImage()));
	connect(gui.get(), SIGNAL(BlurLevel(int)), this, SLOT(Apply(int)));
	connect(gui.get(), SIGNAL(Save()), this, SLOT(SaveImage()));
}
