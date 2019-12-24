#pragma once

#include <iostream>
#include <istream>
#include <memory>
#include <vector>
#include "Editor.h"

class CmdParser
{
public:
	CmdParser(std::istream& in, std::shared_ptr<Document> _doc); 
	std::vector<std::shared_ptr<Command>> return_cmds() const;
	~CmdParser() = default;

private:
	std::vector<std::shared_ptr<Command>> commands{};
	std::shared_ptr<Document> doc{};
};