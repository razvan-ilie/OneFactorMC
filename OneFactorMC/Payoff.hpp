// Payoff
// Wrapper class for a function that returns the payoff from a given set of parameters

#ifndef Payoff_HPP
#define Payoff_HPP

#include <functional>

class Payoff 
{
private:

	// payoff function as member
	std::function<double(double) > payoffFunc;

public:

	Payoff(const std::function<double(double)>& pOff);

	// overload () operator to compute payoff
	double operator () (double S);
};

#endif