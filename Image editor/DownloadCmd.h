#pragma once
#include "Command.h"

class DownloadCmd : public Command {
public:
	void execute(std::shared_ptr<Model>&) override;
	void unexecute(std::shared_ptr<Model>&) override;
};