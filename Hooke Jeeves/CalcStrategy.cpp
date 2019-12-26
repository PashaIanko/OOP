#include "pch.h"
#include "CalcStrategy.h"

size_t CalcStrategy::get_iterations_numb() const
{
	return iterations_numb;
}

void CalcStrategy::set_iterations_numb(size_t numb) {
	iterations_numb = numb;
}
