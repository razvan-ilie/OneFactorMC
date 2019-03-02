#include "AsianPricer.hpp"

AsianPricer::AsianPricer(Payoff pOff, std::function<double(double)> disc) : Pricer(pOff, disc)
{
}

void AsianPricer::processPath(std::vector<double>& path)
{
	// find the average price over the life of the underlying
	double avgPrice = (std::accumulate(path.begin(), path.end(), 0.0) / path.size());

	sum += payoff(avgPrice);

	numSims++;
}