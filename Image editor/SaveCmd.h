#pragma once
#include "Command.h"


class SaveCmd : public Command {
public:
	SaveCmd(const QString& filename);
	void execute(std::shared_ptr<Model>&) override;
	void unexecute(std::shared_ptr<Model>&) override;

private:
	QString filename;
};