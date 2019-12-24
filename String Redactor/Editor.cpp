#include "pch.h"
#include "Editor.h"
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <sstream>
#include "CommandParser.h"
#include <cctype>


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

size_t Document::buf_size() const {
	return buffer_.length();
}

void Document::assign_to_buf(const std::string & str) {
	buffer_.assign(str);
}

inline std::string Document::get_buffer() const {
	return buffer_;
}


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
	/*Любая другая команда -- > RedoList уничтожить*/
	destroy_redo_list();
	cmd->Execute();
	UndoList.push(cmd);
}

void LineEditor::undo() {
	if (UndoList.size()) {
		std::shared_ptr<Command> undo_cmd = UndoList.top();
		UndoList.pop();
		undo_cmd->unExecute();
		RedoList.push(undo_cmd);
	}
}

void LineEditor::redo() {
	if (RedoList.size()) {
		std::shared_ptr<Command> redo_cmd = RedoList.top();
		RedoList.pop();
		redo_cmd->Execute();
		UndoList.push(redo_cmd);
	}
}

inline void LineEditor::destroy_redo_list() {
	while (RedoList.size()) {
		RedoList.pop();
	}
}

void CopyCmd::Execute() {
	size_t ln = len();
	if (ln > 0 && start < doc->length()) {
		/*Запомнили, что лежало в буффере до этого*/
		prev_piece = doc->get_buffer();

		/*Запомнили, что скопировали в команду*/
		copied_piece = doc->substr(start, ln);
		doc->assign_to_buf(copied_piece);
	}
}

void CopyCmd::set_params(const Parameters & params) {
	doc = params.doc.lock();
	start = params.from;
	end = params.to;
}

void CopyCmd::unExecute() {
	if (len() > 0 ) {
		doc->assign_to_buf(prev_piece);
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
	if (doc->buf_size()) {
		if (idx >= doc->size()) {
			doc->resize((idx), ' ');
		}
		pasted_str = doc->get_buffer();
		doc->insert(idx, pasted_str);
	}
}

void PasteCmd::unExecute() {
	doc->erase(idx, pasted_str.length());
	if (original_size > 0)
		doc->resize(original_size);
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
		doc->resize((idx), ' ');
	}
	doc->insert(idx, str);
}

void InsertCmd::unExecute() {
	if (!str.length()) {
		return;
	}
	doc->erase(idx, str.length());
	if (original_size > 0)
		doc->resize(original_size);
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
	}
}

void DelCmd::unExecute() {
	if (len() > 0 && deleted.length() > 0) {
		doc->insert(start, deleted);
	}
}

void UndoCmd::Execute() {}
void UndoCmd::unExecute() {}

void RedoCmd::Execute() {}
void RedoCmd::unExecute() {}

std::shared_ptr<Command> Command::create_internal(const std::string& command)
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

std::shared_ptr<Command> Command::create(const std::string& cmd, std::shared_ptr<Document>& doc)
{
	std::stringstream ss(cmd);
	std::string cur_cmd;
	ss >> cur_cmd;

	std::transform(cur_cmd.begin(), cur_cmd.end(), cur_cmd.begin(), 
		[](unsigned char c) {
			return std::tolower(c); 
	} );
	

	std::shared_ptr<Command> ptr = create_internal(cur_cmd);
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
