#include "UpAndOutKnockoutPricer.hpp"

UpAndOutKnockoutPricer::UpAndOutKnockoutPricer(Payoff pOff, std::function<double(double)> disc, double level) : Pricer(pOff, disc), barrier(level)
{
}

void UpAndOutKnockoutPricer::processPath(std::vector<double>& path)
{
	numSims++;
	double level = barrier;
	// if there is an element that is above the barrier, knock out
	if (std::find_if(path.begin(), path.end(), [&level](double x) {return (x > level); }) != path.end()) 
	{
		return;
	}
	else 
	{
		sum += payoff(path[path.size() - 1]);
	}
}
