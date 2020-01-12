#include "Model.h"

void Model::set_image(const std::string & dir_) {
	cv::String dir(dir_);
	image = cv::imread(dir);
}
