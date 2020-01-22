#include "BlurCmd.h"

BlurCmd::BlurCmd(const int blur_intensity_) 
	: blur_intensity(blur_intensity_)
{ }

void BlurCmd::execute(std::shared_ptr<Model>& image) {
	
	const cv::Mat& src_image(image->get_initial_image());
	cv::Mat& dest_image = image->get_image();

	/*cv::MedianBlur algorithm requires odd int value as an argument*/
	int odd_intensity = blur_intensity % 2 == 0 ? blur_intensity + 1 : blur_intensity;
	cv::medianBlur(src_image, dest_image, odd_intensity);
	image->update_view();
}

void BlurCmd::unexecute(std::shared_ptr<Model>&) {
}
