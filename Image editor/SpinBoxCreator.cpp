#include "SpinBoxCreator.h"

QWidget * SpinBoxCreator::create_object(const SpinBoxParams & params)
{
	QSpinBox* ptr = nullptr;
	try {
		ptr = new QSpinBox(params.parent);
	}
	catch (...) {
		return nullptr;
	}
	ptr->setRange(params.range.first, params.range.second);
	ptr->setValue(params.initial_value);
	return ptr;
}
