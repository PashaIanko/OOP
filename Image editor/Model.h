#pragma once
#include <iostream>
#include <opencv2\opencv.hpp>

class Model {
public:
	void set_image(const std::string& dir);

private:
	cv::Mat image;
};