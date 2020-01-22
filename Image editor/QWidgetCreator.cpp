#include "QWidgetCreator.h"

QWidget * QWidgetCreator::create_object(const QWidgetParams & params) {
	QWidget* ptr = nullptr;
	try {
		ptr = new QWidget(params.parent);
	}
	catch (...) {
		return nullptr;
	}
	ptr->setGeometry(params.size);
	if(params.layout)
		ptr->setLayout(params.layout);
	ptr->move(params.position);
	return ptr;
}
