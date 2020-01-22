#include "Model.h"

Model::Model() {
	cv::namedWindow(view_window_name);
}

void Model::download_image(const std::string & dir) {
	image = cv::imread(dir);
	initial_image = image.clone();
}

void Model::save_image(const std::string & dir) {
	cv::imwrite(dir, image);
}

const cv::Mat & Model::get_image() const {
	return image;
}

cv::Mat & Model::get_image() {
	return image;
}

const cv::Mat & Model::get_initial_image() const {
	return initial_image;
}

void Model::update_view() const {
	if(image_is_valid())
		cv::imshow(view_window_name, image);
}

inline bool Model::image_is_valid() const {
	return image.size != 0 && image.data != nullptr;
}
