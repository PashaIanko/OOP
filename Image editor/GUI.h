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
	~GUI();
public slots:
	void DownloadButtonPushed();
	void SaveButtonPushed();
	void BlurLevelSet(int value);

signals: /*signals for controller*/
	void Download();
	void BlurLevel(int value);
	void Save();

private:
	std::vector<QObject*> objects;
	void create_controllers();

	ButtonCreator button_creator;
	SliderCreator slider_creator;
	SpinBoxCreator spinbox_creator;
	LayOutCreator layout_creator;
	QWidgetCreator qwidget_creator;
};