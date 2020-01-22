#include "GUI.h"
#include "Controller.h"
#include <QLabel>
#include "UtilStructs.h"

GUI::GUI(QWidget * parent) {
	resize(200, 400);

	QPushButton* download_button = dynamic_cast<QPushButton*>
		( button_creator.create_object (
			{this, "Download Image", QRect(QPoint(0, 0), QSize(100, 25)) }
		  )
		);
	connect(download_button, SIGNAL(clicked()), this, SLOT(DownloadButtonPushed()));
	

	QSpinBox* spinner = dynamic_cast<QSpinBox*>(spinbox_creator.create_object (
		{ this, 0, {0,9} }
	));

	QSlider* slider = dynamic_cast<QSlider*> (slider_creator.create_object
	(
		{ Qt::Horizontal, this, 0, {0,9} }
	));

	connect(spinner,	SIGNAL(valueChanged(int)), slider,	SLOT(setValue(int)));
	connect(slider,		SIGNAL(valueChanged(int)), spinner, SLOT(setValue(int)));
	connect(spinner,	SIGNAL(valueChanged(int)), this,	SLOT(BlurLevelSet_(int)));

	
	QHBoxLayout* layout = layout_creator.create_object
	({ this, {slider, spinner} });
	
	QWidget* layout_win = qwidget_creator.create_object
	({this, QRect(QPoint(0, 200), QSize(200, 100)), layout, QPoint(0,250) });

	
}

void GUI::DownloadButtonPushed() {
	emit Download();
}

void GUI::BlurButtonPushed() {
	emit Blur();
}

void GUI::BlurLevelSet_(int value) {
	emit BlurLevel(value);
}
