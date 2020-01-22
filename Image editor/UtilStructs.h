#pragma once
#include <QtWidgets/QMainWindow>
#include <string>


struct ButtonParams {
	QMainWindow* parent;
	QString button_name;
	QRect size;
};

struct SliderParams {
	enum Qt::Orientation orientation;
	QMainWindow* parent;
	int start_position;
	std::pair<int, int> range;
};
