#pragma once

#include <iostream>
#include <istream>
#include <vector>
#include <stack>
#include <memory>
#include <string>


namespace {
	std::stack<std::string> string_buffer;
}

class Document : public std::string {
public:
	Document();
	Document(const std::string& txt);
	Document(std::istream& in); 
	~Document() = default;

	std::string text();
};



class Command {

public:
	virtual void Execute() = 0;
	virtual void unExecute() = 0;
	virtual ~Command() {}

protected:
	bool executed = false;
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

	void execute(std::shared_ptr<Command> cmd);
	void undo();
	void redo();

private:
	std::vector<std::shared_ptr<Command>> commands;
	size_t current_command = 0;
};



class CopyCmd : public Command
{
public:
	CopyCmd(std::shared_ptr<Document> _doc, size_t idx1 = 0, size_t idx2 = 0) :	start(idx1), end(idx2) 
	{
		this->doc = _doc;
	}
	size_t len() const; 
	void Execute() override; 
	

	void unExecute() override;
	virtual ~CopyCmd() {}

private:
	size_t start, end;
};


class PasteCmd : public Command
{
public:
	PasteCmd(std::shared_ptr<Document> doc_,
		size_t idx_) :
		idx(idx_)
	{
		this->doc = doc_;
	}

	void Execute() override; 

	void unExecute() override; 
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
	InsertCmd(std::shared_ptr<Document> _doc,
		std::string _str = "", size_t _idx = 0) :
		str(_str), idx(_idx)
	{
		this->doc = _doc;
	}

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
	DelCmd(std::shared_ptr<Document> _doc,
		size_t idx1 = 0, size_t idx2 = 0) :
		start(idx1), end(idx2)
	{
		this->doc = _doc;
	}
	size_t len() const;
	void Execute() override; 
	void unExecute() override;
	virtual ~DelCmd() {}

private:
	size_t start = 0;
	size_t end = 0;
	std::string deleted{};
};