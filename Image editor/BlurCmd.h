#pragma once
#include "Command.h"

class BlurCmd : public Command {
public:
	BlurCmd() = delete;
	BlurCmd(const cv::Size& kernel_block_size_);
	void execute(std::shared_ptr<Model>&) override;
	void unexecute(std::shared_ptr<Model>&) override;

private:
	cv::Size kernel_block_size{};
};