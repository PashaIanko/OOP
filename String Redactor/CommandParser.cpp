#include "pch.h"
#include <sstream>
#include <algorithm>
#include <memory>
#include "CommandParser.h"
#include "Editor.h"
#include "Parameters.h"



std::shared_ptr<Command> CmdParser::parse_cmd(const std::string &cmd) {
	std::stringstream ss(cmd);
	std::string cur_cmd;
	ss >> cur_cmd;

	std::transform(cur_cmd.begin(), cur_cmd.end(), cur_cmd.begin(), ::tolower);

	std::shared_ptr<Command> ptr = Command::create(cur_cmd);
	if (cur_cmd == "copy" || cur_cmd == "delete") {
		size_t idx1 = 0, idx2 = 0;
		ss >> idx1;
		ss.ignore(100, ',');
		ss >> idx2;
		
		Parameters params{ doc, "", idx1, idx2 };
		if (cur_cmd == "copy") {
			CopyCmd* cmd_ptr = static_cast<CopyCmd*>(ptr.get());
			cmd_ptr->set_params(params);
		}
		else {
			DelCmd* cmd_ptr = static_cast<DelCmd*>(ptr.get());
			cmd_ptr->set_params(params);
		}
	}

	if (cur_cmd == "paste") {
		size_t idx = 0;
		ss >> idx;
		Parameters params{ doc, "", idx, 0 };
		PasteCmd* cmd_ptr = static_cast<PasteCmd*>(ptr.get());
		cmd_ptr->set_params(params);
	}

	if (cur_cmd == "insert") {
		size_t idx = 0;
		std::string text_to_insert = "";
		ss.ignore(100, ',');
		text_to_insert = cmd;
		auto it_begin = text_to_insert.find_first_of('"');
		auto it_end = text_to_insert.find_last_of('"');
		it_begin++;

		text_to_insert = text_to_insert.substr(it_begin, (it_end - it_begin));
		if (text_to_insert.empty()) {
			return nullptr;
		}
		ss >> idx;
		Parameters params{ doc, text_to_insert, idx, 0 };
		InsertCmd* cmd_ptr = static_cast<InsertCmd*>(ptr.get());
		cmd_ptr->set_params(params);
	}
	return ptr;
}

CmdParser::CmdParser(std::istream & in, std::shared_ptr<Document> _doc) {
	doc = _doc;
	std::string line;
	while (std::getline(in, line)) {
		if (line.length() == 0) {
			continue;
		}
		std::shared_ptr<Command> cmd = parse_cmd(line);
		
		if (cmd != nullptr) {
			commands.push_back(cmd);
		}
	}
}

std::vector<std::shared_ptr<Command>> CmdParser::return_cmds() const {
	return commands;
}
