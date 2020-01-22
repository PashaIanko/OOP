#include "SaveCmd.h"
#include <QFileDialog>

SaveCmd::SaveCmd(const QString & filename_) : filename(filename_) {
}

void SaveCmd::execute(std::shared_ptr<Model>& model) {
	QString dir = QFileDialog::getExistingDirectory(0, "Open Dialog", "");
	dir += filename;
	model->save_image(dir.toStdString());
}

void SaveCmd::unexecute(std::shared_ptr<Model>&) {
}
