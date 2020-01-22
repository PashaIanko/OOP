#pragma once
#include "UtilStructs.h"
#include <QSlider>

class SliderCreator {
public:
	QWidget* create_object(const SliderParams& params);
};