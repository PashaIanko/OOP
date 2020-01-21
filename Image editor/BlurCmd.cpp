#include "BlurCmd.h"

BlurCmd::BlurCmd(const cv::Size& kernel_block_size_) 
	: kernel_block_size(kernel_block_size_)
{

}

void BlurCmd::execute(std::shared_ptr<Model>& image) {
	cv::Mat dest = image->get_image();
	cv::Mat src = dest;
	cv::GaussianBlur(src, dest, kernel_block_size, 7, 7);
	*image = dest;
	image->update_view();
}

void BlurCmd::unexecute(std::shared_ptr<Model>&) {
}
