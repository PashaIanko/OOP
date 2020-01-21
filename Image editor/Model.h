#pragma once
#include <iostream>
#include <opencv2\opencv.hpp>
#include <QPixmap>

class Model {
public:
	void set_image(const std::string& dir);
	const cv::Mat& get_image() const;
private:
	cv::Mat image;
};