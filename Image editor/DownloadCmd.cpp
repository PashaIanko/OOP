#include "DownloadCmd.h"
#include <QFileDialog>

void DownloadCmd::execute(std::shared_ptr<Model>& image) {
	QString dir = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.jpg");
	image->set_image(dir.toStdString());
}

void DownloadCmd::unexecute(std::shared_ptr<Model>&) {

}
