#include "pch.h"
#include "Editor.h"
#include <string>
#include <iterator>
#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include "CommandParser.h"


Document::Document() {
}

Document::Document(const std::string & txt) {
	this->assign(txt);
}

Document::Document(std::istream & in) {
	std::string text(std::istreambuf_iterator<char>(in), {});
	this->assign(text);
}

std::string Document::text()
{
	return std::string(*this);
}

/*void LineEditor::edit(const CmdParser& commands) {
	for (auto cmd : commands) {
		execute(cmd);
	}
}*/

void LineEditor::edit(const std::vector<std::shared_ptr<Command>>& cmds){
	for (auto cmd : cmds) {
		execute(cmd);
	}
}

void LineEditor::execute(std::shared_ptr<Command> cmd) {
	
	/*добавление и исполнение команды*/
	if (RedoCmd* redo_ptr = dynamic_cast<RedoCmd*>(cmd.get())) {
		redo();
		return;
	}
	if (UndoCmd* unredo_ptr = dynamic_cast<UndoCmd*>(cmd.get())) {
		undo();
		return;
	}

	size_t cmds_sz = commands.size();
	if (cmds_sz > 0 &&
		current_command < (cmds_sz - 1)) {
		commands.erase((commands.begin() + current_command), commands.end());
	}
	commands.push_back(cmd);
	cmd->Execute();
	current_command++;
}

void LineEditor::undo() {
	if (current_command > 0) {
		commands[--current_command]->unExecute();
	}
}

void LineEditor::redo() {
	if (!commands.size()) {
		return;
	}
	if (current_command <= (commands.size() - 1)) {
		commands[current_command++]->Execute();
	}
}

void CopyCmd::Execute() {
	size_t ln = len();
	if (ln > 0 && start < doc->length()) {
		std::string cp = doc->substr(start, ln);
		string_buffer.push(std::move(cp));
		executed = true;
	}
}

void CopyCmd::set_params(const Parameters & params) {
	doc = params.doc.lock();
	start = params.from;
	end = params.to;
}

void CopyCmd::unExecute() {
	if (len() > 0 && executed) {
		string_buffer.pop();
		executed = false;
	}
}

size_t CopyCmd::len() const
{
	if (start >= end || end < 1) {
		return 0;
	}
	return (end - start);
}

PasteCmd::PasteCmd() {
}

void PasteCmd::Execute() {
	if (string_buffer.size() > 0) {
		pasted_str = string_buffer.top();
		if (idx >= doc->size()) {
			original_size = doc->length();
			doc->resize((idx), ' ');//doc->resize((idx), '\n');
		}
		doc->insert(idx, pasted_str);
		string_buffer.pop();
		executed = true;
	}
}

void PasteCmd::unExecute() {
	if (executed) {
		doc->erase(idx, pasted_str.length());
		string_buffer.push(pasted_str);
		if (original_size > 0)
			doc->resize(original_size);
		executed = false;
	}
}

void PasteCmd::set_params(const Parameters & params) {
	doc = params.doc.lock();
	idx = params.from;
}

InsertCmd::InsertCmd(){
}

void InsertCmd::set_params(const Parameters & params)
{
	doc = params.doc.lock();
	idx = params.from;
	str = params.str;
}

void InsertCmd::Execute() {
	if (!str.length()) {
		return;
	}
	if (doc->size() <= idx) {
		original_size = doc->length();
		doc->resize((idx), ' ');//doc->resize((idx), '\n');
	}
	doc->insert(idx, str);
	executed = true;
}

void InsertCmd::unExecute() {
	if (!str.length()) {
		return;
	}
	doc->erase(idx, str.length());
	if (original_size > 0)
		doc->resize(original_size);
	executed = false;
}

DelCmd::DelCmd(){
}

size_t DelCmd::len() const
{
	if (start >= end || end == 0) {
		return 0;
	}
	return (end - start);
}

void DelCmd::set_params(const Parameters & params) {
	doc = params.doc.lock();
	start = params.from;
	end = params.to;
}

void DelCmd::Execute() {
	size_t ln = len();
	if (ln > 0 && start < doc->length()) {
		deleted = doc->substr(start, ln);
		doc->erase(start, ln);
		executed = true;
	}
}

void DelCmd::unExecute() {
	if (len() > 0 && deleted.length() > 0) {
		doc->insert(start, deleted);
		executed = false;
	}
}

void UndoCmd::Execute() {}
void UndoCmd::unExecute() {}

void RedoCmd::Execute() {}
void RedoCmd::unExecute() {}

std::shared_ptr<Command> Command::create(const std::string command)
{
	Command* ptr = nullptr;
	if (command == "undo") {
		ptr = new UndoCmd();
	}
	if (command == "redo") {
		ptr = new RedoCmd();
	}
	if (command == "copy") {
		ptr = new CopyCmd();
	}
	if (command == "paste") {
		ptr = new PasteCmd();
	}
	if (command == "insert") {
		ptr = new InsertCmd();
	}
	if (command == "delete") {
		ptr = new DelCmd();
	}
	return std::shared_ptr<Command>(ptr);
}
