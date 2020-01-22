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
	void SaveImage();
	void BlurFilterImage(int blur_intensity);

private:
	std::shared_ptr<GUI> gui;
	std::shared_ptr<Model> image;
	std::stack<Command> redo_list;
	std::stack<Command> undo_list;
	const QString result_image_name{ "/Result.jpg" };
private:
	void connect_gui_signals();
};
