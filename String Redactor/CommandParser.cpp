#include "pch.h"
#include <sstream>
#include <algorithm>
#include "CommandParser.h"


std::shared_ptr<Command> CmdParser::parse_cmd(const std::string &cmd) {
	std::stringstream ss(cmd);
	std::string cur_cmd;
	ss >> cur_cmd;

	std::transform(cur_cmd.begin(), cur_cmd.end(), cur_cmd.begin(), ::tolower);

	if (cur_cmd == "undo") {
		/*Command* ptr = new UnRedoCmd();
		return std::shared_ptr<Command>(ptr);*/
		Command* ptr = new UndoCmd();
		return std::shared_ptr<Command>(ptr);
	}

	if (cur_cmd == "redo") {
		/*Command* ptr = new UnRedoCmd(true);
		return std::shared_ptr<Command>(ptr);*/
		Command* ptr = new RedoCmd();
		return std::shared_ptr<Command>(ptr);
	}

	if (cur_cmd == "copy" || cur_cmd == "delete") {
		size_t idx1 = 0, idx2 = 0;
		ss >> idx1;
		ss.ignore(100, ',');
		ss >> idx2;
		Command *command = nullptr;
		if (cur_cmd == "copy") {
			command = new CopyCmd(doc, idx1, idx2);
		}
		else {
			command = new DelCmd(doc, idx1, idx2);
		}
		return std::shared_ptr<Command>(command);
	}

	if (cur_cmd == "paste") {
		size_t idx = 0;
		ss >> idx;
		Command* ptr = new PasteCmd(doc, idx);
		return std::shared_ptr<Command>(ptr);
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
		Command* ptr = new InsertCmd(doc, text_to_insert, idx);
		return std::shared_ptr<Command>(ptr);
	}
	return nullptr;
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

std::vector<std::shared_ptr<Command>>::iterator CmdParser::begin() {
	return commands.begin();
}

std::vector<std::shared_ptr<Command>>::iterator CmdParser::end() {
	return commands.end();
}
