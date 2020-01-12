#pragma once
#include "Model.h"
#include <QtWidgets/QMainWindow>
#include <QPushButton>

class View : public QMainWindow {

	Q_OBJECT

public:
	View(QWidget *parent = Q_NULLPTR);
	void set_model(const std::shared_ptr<Model>& new_model);
	QPushButton* get_button();

private:
	std::shared_ptr<Model> model;
	QPushButton* download_button;
};