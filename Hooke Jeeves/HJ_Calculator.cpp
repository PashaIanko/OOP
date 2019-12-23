#include "pch.h"
#include "HJ_Calculator.h"
#include <algorithm>



/*class step_incrementer {
public:
	step_incrementer(double converge_param_) : converge_param(converge_param_) {}
	bool operator() (const double arg) {
		double res = arg * converge_param;
		if (res == 0.0) {
			return converge_param;
		}
		return res;
	}
private:
	double converge_param;
};*/

/*class step_multiplier {
public:
	step_multiplier(double converge_param_) : converge_param(converge_param_) {}
	bool operator() (const double arg) {
		return arg * converge_param;
	}
private:
	double converge_param;
};*/

HJ_Calculator::HJ_Calculator(const Ctor_Params & calc_params) : 
	domain_dimensions(calc_params.dimensions),
	convergence_param(calc_params.rho),
	accuracy(calc_params.epsilon),
	iterations_lim(calc_params.iterations_limit),
	func(calc_params.func_ptr)
{
	if (calc_params.raw_data) {
		raw_data.assign(calc_params.raw_data, calc_params.raw_data + calc_params.dimensions);
	}
	if (calc_params.cooked_data) {
		cooked_data.assign(calc_params.cooked_data, calc_params.cooked_data + calc_params.data_size);
	}
}

std::vector<double> HJ_Calculator::return_min_coordinates() const
{
	if (coordinates_next.size())
		return coordinates_next;
	else
		return std::vector<double>();
}

size_t HJ_Calculator::HJ_calc(){
	initialize_coordinates();
	double conv_param = convergence_param;
	std::transform(
		raw_data.begin(),
		raw_data.end(), 
		std::back_inserter(deltas), 
		[conv_param](const double arg) { // Ранее было через функтор, некорректно почему-то std::back_inserter(deltas), step_incrementer(convergence_param));
		double res = arg * conv_param;
		if (res == 0.0) {
			return conv_param;
		}
		return res;
	});
		
	
	initialize_func_values();
	set_iterations_numb(0);


	double steplength = convergence_param;
	while (!exceeded_iter_limit() && !step_less_accuracy(steplength)) {
		iterations_made++;
		coordinates_next = coordinates_prev;
		func_value_next = best_nearby(func_value_prev);

		bool keep_moving = true; //line: keep = 1;
		while ((func_value_next < func_value_prev) && keep_moving) {
			set_deltas_signs();
			refresh_coordinates();

			func_value_prev = func_value_next;
			func_value_next = best_nearby(func_value_prev);

			if (func_value_next > func_value_prev) {
				break;
			}

			keep_moving = check_for_foundoff_errs();
		}
		if (steplength >= accuracy && func_value_next >= func_value_prev) {
			steplength *= convergence_param;
			std::transform(deltas.begin(), deltas.end(), deltas.begin(), 
				[conv_param](const double arg) {
					return arg * conv_param;
				});/*step_multiplier(convergence_param)*/
		}
	}
	coordinates_next = coordinates_prev;
	return iterations_made;

}

void HJ_Calculator::initialize_coordinates() {
	coordinates_prev = raw_data;
	coordinates_next = raw_data;
}

void HJ_Calculator::initialize_func_values() {
	func_value_prev = func(&coordinates_next[0], domain_dimensions);
	func_value_next = func_value_prev;
}

void HJ_Calculator::set_iterations_numb(size_t arg) {
	iterations_made = arg;
}

bool HJ_Calculator::exceeded_iter_limit() const {
	return iterations_made > iterations_lim; /*Да, знаю,
											 знаковое с беззнаковым, это плохо,
											 но в исходном коде у них лимит итераций был интовый,
											 я конструируя объект, должен преобразовывать интовое в сайз т?
											 (Ctor_Params хранит лимит как инт, для совместимости со старой версией.
											 А новый ООП объект - в конструкторе инт в сайз т преобразовать?*/
}

bool HJ_Calculator::step_less_accuracy(const double steplength) const {
	return steplength < accuracy;
}

double HJ_Calculator::best_nearby(const double func_val) {
	double min_func_val = func_val;
	//double cur_func_val;

	std::vector<double> coordinates = coordinates_next;

	/*modify - add little step from the point - z[i] = point[i] + delta[i]*/
	for (size_t i = 0; i < domain_dimensions; ++i) {
		bool reached_less_val = increment_and_compare (coordinates, coordinates_next[i], 
														deltas[i], i, min_func_val);
		if (reached_less_val) {
			min_func_val = func(&coordinates[0], domain_dimensions);
		}

		else {
			deltas[i] = 0.0 - deltas[i];
			reached_less_val = increment_and_compare (coordinates, coordinates_next[i],	
														deltas[i], i, min_func_val	);
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
	bool result = false;
	for (size_t i = 0; i < domain_dimensions; i++) {
		result = true;
		if (fabs(coordinates_next[i] - coordinates_prev[i]) >
			(0.5 * fabs(deltas[i])))
			break;
		else
			result = false;
	}
	return result;
}



