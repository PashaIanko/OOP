#pragma once
#include "NodeID.h"
#include <vector>

struct raw_data {
	int data;
	NodeID id;
	std::vector<NodeID> neighbours;
};
