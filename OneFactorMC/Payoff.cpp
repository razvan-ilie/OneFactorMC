#include "Payoff.hpp"

Payoff::Payoff(const std::function<double(double)>& pOff) : payoffFunc(pOff)
{
}

double Payoff::operator()(double S)
{
	return payoffFunc(S);
}