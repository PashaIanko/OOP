#include "pch.h"
#include <sstream>
#include <algorithm>
#include <memory>
#include "CommandParser.h"
#include "Editor.h"

CmdParser::CmdParser(std::istream & in, std::shared_ptr<Document> _doc) {
	doc = _doc;
	std::string line;
	while (std::getline(in, line)) {
		if (line.length() == 0) {
			continue;
		}
		std::shared_ptr<Command> cmd_ = Command::create(line, _doc);
		if (cmd_ != nullptr) {
			commands.push_back(cmd_);
		}
	}
}

std::vector<std::shared_ptr<Command>> CmdParser::return_cmds() const {
	return commands;
}
