#pragma once
#include "Ctor_Params.h"
#include <vector>

class HJ_Calculator {

public:
	HJ_Calculator() = delete;
	HJ_Calculator(const Ctor_Params& calc_parameters);
	const std::vector<double>& get_result() const;
	size_t HJ_calc();

private:
	int domain_dimensions;
	double convergence_param;
	double accuracy;
	int iterations_lim;
	double(*func)(double*, int);

	std::vector<double> raw_data{};
	std::vector<double> cooked_data{};
	
	std::vector<double> coordinates_next{};
	std::vector<double> coordinates_prev{};
	std::vector<double> deltas{};

	double func_value_prev;
	double func_value_next;

	
	double best_nearby(const double func_val);
	inline bool increment_and_compare(
		std::vector<double>& coordinates,
		double prev_coordinate,
		double delta,
		size_t idx,
		double func_val_to_compare);
	inline void set_deltas_signs();
	inline void refresh_coordinates();
	inline bool check_for_foundoff_errs() const;
	
};