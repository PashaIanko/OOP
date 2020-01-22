#include "ButtonCreator.h"
#include <QPushButton>


QWidget * ButtonCreator::create_object(const ButtonParams& params)
{
	QWidget* ptr = nullptr;
	try {
		ptr = new QPushButton(params.button_name, params.parent);
	}
	catch (...) {
		return nullptr;
	}
	ptr->setGeometry(params.size);
	return ptr;
}
