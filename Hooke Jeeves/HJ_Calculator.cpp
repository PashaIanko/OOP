#include "pch.h"
#include "HJ_Calculator.h"
#include <algorithm>



HJ_Calculator::HJ_Calculator(const Ctor_Params & calc_params) : 
	convergence_param(calc_params.rho),
	accuracy(calc_params.epsilon),
	iterations_lim(calc_params.iterations_limit),
	func(calc_params.func_ptr)
{
	if (calc_params.raw_data.size()) {
		raw_data = calc_params.raw_data;
	}
	domain_dimensions = raw_data.size();
}

std::vector<double> HJ_Calculator::return_min_coordinates() const {
		return coordinates_next;
}

size_t HJ_Calculator::HJ_calc(){

	coordinates_prev = raw_data;
	coordinates_next = raw_data;

	double conv_param = convergence_param;

	double acc = 10e-7;
	for (auto val : raw_data) {
		double res = fabs(val * convergence_param);
		if (fabs(res - 0.0) < acc) {
			res = convergence_param;
		}
		deltas.push_back(res);
	}
		
	
	func_value_prev = func(&coordinates_next[0], domain_dimensions);
	func_value_next = func_value_prev;

	size_t iterations_made = 0;
	double steplength = convergence_param;
	while (iterations_made < iterations_lim && 
		steplength > accuracy)
	{
		iterations_made++;
		coordinates_next = coordinates_prev;

		/* find best new point, one coord at a time */
		func_value_next = best_nearby(func_value_prev);


		/* if we made some improvements, pursue that direction */
		bool keep_moving = true; //line: keep = 1;
		while ((func_value_next < func_value_prev) && keep_moving) {
			/* firstly, arrange the sign of delta[] */
			set_deltas_signs();
			refresh_coordinates();

			func_value_prev = func_value_next;
			func_value_next = best_nearby(func_value_prev);

			/* if the further (optimistic) move was bad.... */
			if (func_value_next > func_value_prev) {
				break;
			}

			/* make sure that the differences between the new */
			/* and the old points are due to actual */
			/* displacements; beware of roundoff errors that */
			/* might cause newf < fbefore */
			keep_moving = check_for_foundoff_errs();
		}
		if (steplength >= accuracy && func_value_next >= func_value_prev) {
			steplength *= convergence_param;
			std::transform(deltas.begin(), deltas.end(), deltas.begin(), 
				[conv_param](const double arg) {
					return arg * conv_param;
				});
		}
	}
	coordinates_next = coordinates_prev;
	return iterations_made;
}

double HJ_Calculator::best_nearby(const double func_val) {
	double min_func_val = func_val;

	std::vector<double> coordinates = coordinates_next;

	/*modify - add little step from the point - z[i] = point[i] + delta[i]*/
	for (size_t i = 0; i < domain_dimensions; ++i) {
		

		/*Вставленный обратно кусок из increment and compare()*/
		bool reached_less_val = false;
		coordinates[i] = coordinates_next[i] + deltas[i];
		double cur_func_val = func(&coordinates[0], domain_dimensions);
		if (cur_func_val < min_func_val) {
			reached_less_val = true;
		}

		if (reached_less_val) {
			min_func_val = func(&coordinates[0], domain_dimensions);
		}

		else {
			/*ещё раз вставленный кусок increment_and_compare*/
			deltas[i] = 0.0 - deltas[i];
			reached_less_val = false;
			coordinates[i] = coordinates_next[i] + deltas[i];
			double cur_func_val = func(&coordinates[0], domain_dimensions);
			if (cur_func_val < min_func_val) {
				reached_less_val = true;
			}
			
			if (reached_less_val) {
				min_func_val = func(&coordinates[0], domain_dimensions);
			}
			else {
				coordinates[i] = coordinates_next[i];
			}
		}
	}
	coordinates_next = coordinates;
	return min_func_val;
}

bool HJ_Calculator::increment_and_compare(
	std::vector<double>& coordinates, 
	double prev_coordinate, 
	double delta, 
	size_t idx, 
	double func_val_to_compare)
{
	coordinates[idx] = prev_coordinate + delta;
	double cur_func_val = func(&coordinates[0], domain_dimensions);
	if (cur_func_val < func_val_to_compare) {
		return true;
	}
	return false;
}

void HJ_Calculator::set_deltas_signs(){
	for (size_t i = 0; i < domain_dimensions; i++) {
		if (coordinates_next[i] <= coordinates_prev[i]) {
			deltas[i] = 0.0 - fabs(deltas[i]);
		}
		else {
			deltas[i] = fabs(deltas[i]);
		}
	}
	return;
}

void HJ_Calculator::refresh_coordinates() {
	for (size_t i = 0; i < domain_dimensions; i++) {
		double temp = coordinates_prev[i];
		coordinates_prev[i] = coordinates_next[i];
		coordinates_next[i] = 2 * coordinates_next[i] - temp;
	}
}

bool HJ_Calculator::check_for_foundoff_errs() const {
	for (size_t i = 0; i < domain_dimensions; i++) {
		if (fabs(coordinates_next[i] - coordinates_prev[i]) >
			(0.5 * fabs(deltas[i])))
			return true;
	}
	return false;
}



