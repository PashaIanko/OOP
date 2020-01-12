#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include "View.h"
#include "Command.h"
#include <vector>
#include <string>
#include <stack>

class Controller : public QMainWindow
{
	Q_OBJECT

public:
	Controller(QWidget *parent = Q_NULLPTR);

public slots:
	void DownloadImage();

private:
	std::vector<QPushButton*> buttons{};
	std::shared_ptr<View> GUI;
	std::shared_ptr<Model> image;
	std::stack<Command> redo_list;
	std::stack<Command> undo_list;

private:
	void set_model(const std::string&);
};
