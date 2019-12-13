#include "pch.h"
#include "NodeID.h"




/*bool NodeID::operator==(const NodeID & rhs)
{
	return id == rhs.id;
}*/

bool NodeID::operator==(const NodeID & rhs) const
{
	return id == rhs.id;
}

bool NodeID::operator<(const NodeID & rhs) const
{
	return id < rhs.id;
}
