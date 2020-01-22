#include "GUI.h"
#include "Controller.h"
#include <QLabel>
#include <algorithm>
#include "UtilStructs.h"

GUI::GUI(QWidget * parent) {
	resize(200, 150);
	create_controllers();
}

void GUI::create_controllers() {
	QPushButton* download_button = dynamic_cast<QPushButton*>
		(
		button_creator.create_object
		(
			{ this, "Download Image", QRect(QPoint(0, 0), QSize(100, 25)) }
		)
		);
	objects.push_back(download_button);

	QPushButton* save_button = dynamic_cast<QPushButton*>
		(
		button_creator.create_object
		(
			{ this, "Save Image", QRect(QPoint(0, 30), QSize(100, 25)) }
		)
		);
	objects.push_back(save_button);

	QSpinBox* spinner = dynamic_cast<QSpinBox*>(spinbox_creator.create_object
		(
			{ this, 0, {0,9} }
		));
	objects.push_back(spinner);

	QSlider* slider = dynamic_cast<QSlider*> (slider_creator.create_object
		(
			{ Qt::Horizontal, this, 0, {0,9} }
		));
	objects.push_back(slider);

	QHBoxLayout* layout = layout_creator.create_object
		({ this, {slider, spinner} });
	objects.push_back(layout);

	QWidget* layout_win = qwidget_creator.create_object
		({ this, QRect(QPoint(0, 200), QSize(200, 100)), layout, QPoint(0,50) });
	objects.push_back(layout_win);


	/*Creators are responsible for the memory allocation. In case no throw was
	detected during the memory allocation for objects (which means, none of them is nullptr),
	we can connect reaction signals of the GUI controllers to the signal handlers*/

	if (std::all_of(objects.cbegin(), objects.cend(),
		[](QObject* ptr) {return ptr != nullptr; })) 
	{
		connect(download_button, SIGNAL(clicked()), this,	SLOT(DownloadButtonPushed()));
		connect(save_button, SIGNAL(clicked()),		this,	SLOT(SaveButtonPushed()));
		connect(spinner, SIGNAL(valueChanged(int)), slider,	SLOT(setValue(int)));
		connect(slider, SIGNAL(valueChanged(int)),	spinner,SLOT(setValue(int)));
		connect(spinner, SIGNAL(valueChanged(int)),	this,	SLOT(BlurLevelSet(int)));
	}


}

void GUI::DownloadButtonPushed() {
	emit Download();
}

GUI::~GUI(){
	std::for_each(objects.begin(), objects.end(), 
		[](QObject* obj) 
		{
		if (obj)
			delete obj;
		}
	);
}

void GUI::SaveButtonPushed() {
	emit Save();
}

void GUI::BlurLevelSet(int value) {
	emit BlurLevel(value);
}
