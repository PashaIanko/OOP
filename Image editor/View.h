#pragma once
#include "Model.h"

class View {
public:
	void set_model(const std::shared_ptr<Model>& new_model);

private:
	std::shared_ptr<Model> model;
};