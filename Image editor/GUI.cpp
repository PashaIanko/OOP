#include "GUI.h"
#include "Controller.h"
#include <QLabel>

GUI::GUI(QWidget * parent) {
	resize(200, 400);
	QPushButton* download_button = new QPushButton("Download", this);
	download_button->setGeometry(QRect(QPoint(0, 0), QSize(100, 25)));
	connect(download_button, SIGNAL(clicked()), this, SLOT(DownloadButtonPushed()));

	buttons.push_back(download_button);


	QPushButton* download_button_ = new QPushButton("Blur", this);
	download_button->setGeometry(QRect(QPoint(0, 150), QSize(100, 25)));
	connect(download_button_, SIGNAL(clicked()), this, SLOT(BlurButtonPushed()));



	QSpinBox *spinner = new QSpinBox(this);
	spinner->setRange(1, 10);
	QSlider *slider = new QSlider(Qt::Horizontal, this);
	slider->setSliderPosition(5);
	slider->setRange(1, 10);

	connect(spinner, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
	connect(slider, SIGNAL(valueChanged(int)), spinner, SLOT(setValue(int)));

	spinner->setValue(5);
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

/*void GUI::BlurValueChanged(int) {
	int v = 5;
}*/


void GUI::BlurButtonPushed() {
	emit Blur();
}
