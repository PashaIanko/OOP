#pragma once
#include "Creator.h"
#include "UtilStructs.h"

class ButtonCreator { 
public:
	QWidget* create_object(const ButtonParams& params);
};