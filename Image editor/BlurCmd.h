#pragma once
#include "Command.h"

class BlurCmd : public Command {
public:
	BlurCmd() = delete;
	~BlurCmd() = default;
	BlurCmd(const int blur_intensity);
	void execute(std::shared_ptr<Model>&) override;
	void unexecute(std::shared_ptr<Model>&) override;

private:
	int blur_intensity;
};