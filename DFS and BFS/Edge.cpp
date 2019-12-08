#include "pch.h"
#include "Edge.h"

bool Edge::operator==(const Edge & rhs) const
{
	return (from == rhs.from && to == rhs.to) ||
		(id_from == rhs.id_from && id_to == rhs.id_to);
}
