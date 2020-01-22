#include "Model.h"

Model::Model() {
	cv::namedWindow("Your Image");
}

void Model::download_image(const std::string & dir) {
	image = cv::imread(dir);
	initial_image = image.clone();
}

//Model & Model::operator=(const cv::Mat & image_) {
//	this->image = image_;
//	return *this;
//}

const cv::Mat & Model::get_image() const {
	return image;
}

cv::Mat & Model::get_image() {
	return image;
}

const cv::Mat & Model::get_initial_image() const {
	return initial_image;
}

void Model::update_view() {
	cv::imshow("Your Image", image);
}
