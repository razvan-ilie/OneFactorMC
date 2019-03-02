// NormalDist
// Class with overloaded () operator that returns one sample of a normal random variable with chosen mean and variance

// Rather than manually creating normal random variables, we can just get one using STL.
// We may need other kinds of RNGs for other random variables with random process that is not Brownian motion

#ifndef NormalDist_HPP
#define NormalDist_HPP

#include "RNG.hpp"

using RNGPtr = std::shared_ptr<RNG>;

class NormalDist : public RNG
{
private:
	double mu;
	double sig;

	std::normal_distribution<double> normDist;

public:
	// N(0, 1) distribution, time seeded engine
	NormalDist();
	// N(0, 1) distribution, seed chose by user
	NormalDist(int seed);

	// N(mu, sigma^2) distribution, time seeded engine
	NormalDist(double mean, double sigma);
	// seed chosen by user
	NormalDist(double mean, double sigma, int seed);

	// getters for mean and variance
	double mean();
	double stdDev();

	// setters for mean and variance
	void mean(double newMu);
	void stdDev(double newSig);

	// return a sample using RNG's random engine
	double operator()() override;

	// copy the object in the RNGPtr and create a new pointer to it 
	RNGPtr copy() const override;
};

#endif