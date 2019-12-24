#pragma once

#include <iostream>
#include <istream>
#include <vector>
#include <stack>
#include <memory>
#include <string>
#include "Parameters.h"

class Document : public std::string {
public:
	Document();
	Document(const std::string& txt);
	Document(std::istream& in); 
	~Document() = default;
	std::string text();

	size_t buf_size() const;
	
	inline void assign_to_buf(const std::string& str);
	inline std::string get_buffer() const;
private:
	std::string buffer_{};
};



class Command {

public:
	virtual void Execute() = 0;
	virtual void unExecute() = 0;
	virtual ~Command() {}
	static std::shared_ptr<Command> create(const std::string& command, std::shared_ptr<Document>& doc);
private:
	static std::shared_ptr<Command> create_internal(const std::string& command);
protected:
	std::shared_ptr<Document> doc{};
};

class UndoCmd : public Command {
public:
	UndoCmd() = default;
	~UndoCmd() = default;
	void Execute() override;
	void unExecute() override;
};

class RedoCmd : public Command {
public:
	RedoCmd() = default;
	void Execute() override;
	void unExecute() override;
};


class LineEditor
{

public:
	LineEditor() {}
	virtual ~LineEditor() {}

	void edit(const std::vector<std::shared_ptr<Command>>& commands);
	void execute(std::shared_ptr<Command> cmd);
	void undo();
	void redo();

private:
	std::vector<std::shared_ptr<Command>> commands;
	std::stack<std::shared_ptr<Command>> UndoList;
	std::stack<std::shared_ptr<Command>> RedoList;
	inline void destroy_redo_list();
};



class CopyCmd : public Command
{
public:
	CopyCmd() {};
	CopyCmd(std::shared_ptr<Document> _doc, size_t idx1 = 0, size_t idx2 = 0) :	start(idx1), end(idx2) 
	{
		this->doc = _doc;
	}
	size_t len() const; 
	void Execute() override; 
	void set_params(const Parameters& params);
	

	void unExecute() override;
	virtual ~CopyCmd() {}

private:
	size_t start, end;
	std::string copied_piece{};
	std::string prev_piece{}; //что лежало в буффере до этого
};


class PasteCmd : public Command
{
public:
	PasteCmd();
	PasteCmd(std::shared_ptr<Document> doc_,
		size_t idx_) :
		idx(idx_)
	{
		this->doc = doc_;
	}

	void Execute() override; 

	void unExecute() override; 
	void set_params(const Parameters& params);
	virtual ~PasteCmd() {}

private:
	size_t idx = 0;
	size_t original_size = 0;
	std::shared_ptr<Document> doc{};
	std::string pasted_str{};
};



class InsertCmd : public Command
{
public:
	InsertCmd();
	InsertCmd(std::shared_ptr<Document> _doc,
		std::string _str = "", size_t _idx = 0) :
		str(_str), idx(_idx)
	{
		this->doc = _doc;
	}
	void set_params(const Parameters& params);
	virtual ~InsertCmd() {}
	void Execute() override;
	void unExecute() override; 
	
private:
	std::string str{};
	size_t idx, original_size = 0;
};

class DelCmd : public Command
{
public:
	DelCmd();
	DelCmd(std::shared_ptr<Document> _doc,
		size_t idx1 = 0, size_t idx2 = 0) :
		start(idx1), end(idx2)
	{
		this->doc = _doc;
	}
	size_t len() const;
	void set_params(const Parameters& params);
	void Execute() override; 
	void unExecute() override;
	virtual ~DelCmd() {}

private:
	size_t start = 0;
	size_t end = 0;
	std::string deleted{};
};