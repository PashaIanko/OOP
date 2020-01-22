#pragma once
#include <QtWidgets/QMainWindow>

class Creator {
public:
	virtual QWidget *create_object() = 0;
	virtual ~Creator() {};
};