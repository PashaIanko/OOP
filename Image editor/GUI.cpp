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
	

	QSpinBox *spinner = new QSpinBox(this);
	spinner->setRange(0, 9);
	spinner->setValue(0);
	QSlider* slider = dynamic_cast<QSlider*> (slider_creator.create_object
	(
		{ Qt::Horizontal, this, 0, {0, 9} }
	));

	connect(spinner, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
	connect(slider, SIGNAL(valueChanged(int)), spinner, SLOT(setValue(int)));
	connect(spinner, SIGNAL(valueChanged(int)), this, SLOT(BlurLevelSet_(int)));

	
	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->addWidget(slider);
	layout->addWidget(spinner);
	
	QWidget* layout_win = new QWidget(this);
	layout_win->setGeometry(QRect(QPoint(0, 200), QSize(200, 100)));
	layout_win->setLayout(layout);
	layout_win->move(QPoint(0, 250));

	
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
