#include "SliderCreator.h"

QWidget * SliderCreator::create_object(const SliderParams & params) {
	QSlider* ptr = nullptr;
	try {
		ptr = new QSlider(params.orientation, params.parent);
	}
	catch (...) {
		return nullptr;
	}
	ptr->setSliderPosition(params.start_position);
	ptr->setRange(params.range.first, params.range.second);
	return ptr;
}
