#pragma once
#include "Model.h"
#include <QtWidgets/QMainWindow>
#include <QPushButton>

class GUI : public QMainWindow {

	Q_OBJECT

public:
	GUI(QWidget *parent = Q_NULLPTR);

public slots:
	void DownloadButtonPushed();

signals:
	void ButtonPushed();

private:
	std::vector<QPushButton*> buttons;
};