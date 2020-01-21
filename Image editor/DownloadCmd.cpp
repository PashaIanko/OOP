#include "DownloadCmd.h"
#include <QFileDialog>

void DownloadCmd::execute(std::shared_ptr<Model>& image) {
	QString dir = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.jpg");
	image->download_image(dir.toStdString());
	image->update_view();
}

void DownloadCmd::unexecute(std::shared_ptr<Model>&) {

}
