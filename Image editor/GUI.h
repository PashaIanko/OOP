#pragma once
#include "Model.h"
#include <QtWidgets/QMainWindow>
#include <QPushButton>

#include <QSlider>
#include <QHBoxLayout>
#include <QSpinBox>


class GUI : public QMainWindow {

	Q_OBJECT

public:
	GUI(QWidget *parent = Q_NULLPTR);

public slots:
	void DownloadButtonPushed();
	void BlurButtonPushed();
	//void BlurValueChanged(int value);

signals: /*signals for controller*/
	void Download();
	void Blur();

private:
	std::vector<QPushButton*> buttons;
	std::vector<QSlider*> sliders;
	
};