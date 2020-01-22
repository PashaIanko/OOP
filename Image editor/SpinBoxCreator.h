#pragma once
#include "UtilStructs.h"
#include <QSpinBox>

class SpinBoxCreator {
public:
	QWidget* create_object(const SpinBoxParams& params);
};