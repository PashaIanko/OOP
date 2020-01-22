#pragma once
#include "Model.h"
#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QSpinBox>
#include "ButtonCreator.h"
#include "SliderCreator.h"
#include "SpinBoxCreator.h"
#include "LayOutCreator.h"
#include "QWidgetCreator.h"



class GUI : public QMainWindow {

	Q_OBJECT

public:
	GUI(QWidget *parent = Q_NULLPTR);

public slots:
	void DownloadButtonPushed();
	void BlurButtonPushed();
	void BlurLevelSet_(int value);

signals: /*signals for controller*/
	void Download();
	void Blur();
	void BlurLevel(int value);

private:
	std::vector<QPushButton*> buttons;
	std::vector<QSlider*> sliders;

	ButtonCreator button_creator;
	SliderCreator slider_creator;
	SpinBoxCreator spinbox_creator;
	LayOutCreator layout_creator;
	QWidgetCreator qwidget_creator;
};