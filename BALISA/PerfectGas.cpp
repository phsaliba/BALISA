#pragma once
#include "PerfectGas.hpp"

const double gas_const = 287.052874;
const double volumic_heat = 0.7171;
const double gamma = 1.4;

double get_pressure(double rho, double ts) {
	return rho * gas_const * ts;
}

double get_internal_energy(double ts) {
	return volumic_heat * ts;
}