#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include "GUI.h"
#include "Command.h"
#include <vector>
#include <string>
#include <stack>

class Controller : public QObject
{
	Q_OBJECT

public:
	Controller();
	void launch_GUI();

public slots:
	void DownloadImage();
	void ApplyBlurFilter();
	void Apply(int level);

private:
	std::shared_ptr<GUI> gui;
	std::shared_ptr<Model> image;
	
	std::stack<Command> redo_list;
	std::stack<Command> undo_list;

private:
	void connect_gui_signals();
};
