#include "Controller.h"
#include "DownloadCmd.h"
#include <opencv2/core/types_c.h>


Controller:: Controller()
	: gui(new GUI), image(new Model) {
}

void Controller::DownloadImage() {
	std::shared_ptr<Command> cmd_ptr = std::make_shared<DownloadCmd>();
	cmd_ptr->execute(image);
	image->update_view();
}

void Controller::launch_GUI() {
	gui->show();
	connect_gui_signals();
}


void Controller::set_model(const std::string &dir) {
	image->set_image(dir);
}

void Controller::connect_gui_signals(){
	connect(gui.get(), SIGNAL(ButtonPushed()), this, SLOT(DownloadImage()));
}
