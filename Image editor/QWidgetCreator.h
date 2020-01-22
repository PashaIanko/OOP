#pragma once
#include "UtilStructs.h"

class QWidgetCreator {
public:
	QWidget* create_object(const QWidgetParams& params);
};