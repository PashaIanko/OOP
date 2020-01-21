#include "Model.h"

void Model::set_image(const std::string & dir) {
	image = cv::imread(dir);
}

const cv::Mat & Model::get_image() const {
	return image;
}
