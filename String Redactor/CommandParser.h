#pragma once

#include <iostream>
#include <istream>
#include <memory>
#include "Editor.h"

class CmdParser
{
public:
	CmdParser(std::istream& in, std::shared_ptr<Document> _doc); 
	std::vector<std::shared_ptr<Command>>::iterator begin();
	std::vector<std::shared_ptr<Command>>::iterator end();
	~CmdParser() = default;

private:
	std::vector<std::shared_ptr<Command>> commands{};
	std::shared_ptr<Command> parse_cmd(const std::string& cmd);
	std::shared_ptr<Document> doc{};
};