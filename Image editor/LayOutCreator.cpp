#include "LayOutCreator.h"

QHBoxLayout* LayOutCreator::create_object(const LayOutParams & params) {

	QHBoxLayout* ptr = nullptr;
	try {
		ptr = new QHBoxLayout(params.parent);
	}
	catch (...) {
		return nullptr;
	}
	for (auto it : params.widgets) {
		if (it != nullptr) {
			ptr->addWidget(it);
		}
	}
	return ptr;
}
