#pragma once
#include <iostream>
#include <opencv2\opencv.hpp>
#include <QPixmap>

class Model {
public:
	Model();
	void download_image(const std::string& dir);
	void save_image(const std::string& dir);

	const cv::Mat& get_image() const;
	cv::Mat& get_image();
	const cv::Mat& get_initial_image() const;
	void update_view();


private:
	cv::Mat image;
	cv::Mat initial_image;
};