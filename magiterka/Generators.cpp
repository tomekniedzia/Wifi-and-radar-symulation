#include "Generators.h"

Generators::Generators()
{
	typedef std::chrono::high_resolution_clock myclock;
	myclock::time_point beginning = myclock::now();

	myclock::duration d = myclock::now() - beginning;
	unsigned seed2 = d.count();

	std::default_random_engine generator;
	generator.seed(seed2);
	std::chi_squared_distribution<double> distribution(4.0);
}

Generators::Generators(std::chi_squared_distribution<double> distribution, std::default_random_engine generator)
{
	generator_ = generator;
	distribution_ = distribution;
}

Generators::Generators(std::gamma_distribution<double> distribution, std::default_random_engine generator)
{
	generator_ = generator;
	gamma_distribution_ = distribution;
}


Generators::~Generators()
{
}

double Generators::GenerateChiSquareDistribution()
{
	return distribution_(generator_);
}

double Generators::GenerateChiSquareDistributionFromGamma()
{
	return gamma_distribution_(generator_);
}
