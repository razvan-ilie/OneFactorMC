#include "EuropeanPricer.hpp"

EuropeanPricer::EuropeanPricer(Payoff pOff, std::function<double(double)> disc) : Pricer(pOff, disc)
{
}

void EuropeanPricer::processPath(std::vector<double>& path)
{
	// compute the payoff of the price at maturity and add it to the rolling sum
	sum += payoff(path[path.size() - 1]);

	// increment number of paths that were used
	numSims++;
}