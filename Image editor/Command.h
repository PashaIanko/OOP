#pragma once
#include "Model.h"

class Command {
public:
	virtual void execute(std::shared_ptr<Model>&) = 0;
	virtual void unexecute(std::shared_ptr<Model>&) = 0;
	virtual ~Command() {}
};