#include "Model.h"

Model::Model() {
	cv::namedWindow("Your Image");
}

void Model::set_image(const std::string & dir) {
	image = cv::imread(dir);
}

const cv::Mat & Model::get_image() const {
	return image;
}

void Model::update_view() {
	cv::imshow("Your Image", image);
}
