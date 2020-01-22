#pragma once
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <string>
#include <vector>


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

struct SpinBoxParams {
	QMainWindow* parent;
	int initial_value;
	std::pair<int, int> range;
};

struct QWidgetParams {
	QMainWindow* parent;
	QRect size;
	QHBoxLayout* layout; /*layout with widgets*/
	QPoint position;
};

struct LayOutParams {
	QMainWindow* parent;
	std::vector<QWidget*> widgets;
};


