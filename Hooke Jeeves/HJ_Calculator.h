#pragma once
#include "Ctor_Params.h"
#include <vector>

class HJ_Calculator {

public:
	HJ_Calculator() = delete;
	HJ_Calculator(const Ctor_Params& calc_parameters);
	std::vector<double> return_min_coordinates() const;
	size_t HJ_calc();

	//set_function()

private:
	int domain_dimensions;
	double convergence_param;
	double accuracy;
	int iterations_lim;
	double(*func)(double*, int);

	std::vector<double> raw_data{};
	std::vector<double> cooked_data{};
	size_t iterations_made = 0;
	
	std::vector<double> coordinates_next{};
	std::vector<double> coordinates_prev{};
	std::vector<double> deltas{};

	double func_value_prev;
	double func_value_next;

	void initialize_coordinates();
	void initialize_func_values();
	void set_iterations_numb(size_t arg);
	bool exceeded_iter_limit()const;
	bool step_less_accuracy(const double steplength) const;
	double best_nearby(const double func_val);
	bool increment_and_compare(
		std::vector<double>& coordinates,
		double prev_coordinate,
		double delta,
		size_t idx,
		double func_val_to_compare);
	void set_deltas_signs();
	void refresh_coordinates();
	bool check_for_foundoff_errs() const;
	
};