#pragma once
#include <iostream>
#include <random>
#include <chrono>
class Generators
{
public:
	Generators();
	Generators(std::chi_squared_distribution<double> distribution, std::default_random_engine generator);
	Generators(std::gamma_distribution<double> distribution, std::default_random_engine generator);
	~Generators();

	double GenerateChiSquareDistribution();
	double GenerateChiSquareDistributionFromGamma();

private:
	std::default_random_engine generator_;
	std::chi_squared_distribution<double> distribution_;
	std::gamma_distribution<double> gamma_distribution_;
};

