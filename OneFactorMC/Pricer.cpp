#include "Pricer.hpp"

Pricer::Pricer(Payoff pOff, std::function<double(double)> disc) : payoff(pOff), discountFunc(disc), price(0.), sum(0.), numSims(0) 
{
}

void Pricer::printDetails()
{
	// print price and number of simulations
	std::cout << "Price of option: " << price << std::endl;
	std::cout << "Number of paths used in Montecarlo simulation: " << numSims << std::endl;
}

double Pricer::discountFactor(double t)
{
	// return the discounting factor from the discounting functions
	return discountFunc(t);
}

double Pricer::calcPrice(double t)
{
	// calculate and return the price
	price = discountFunc(t) * sum / numSims;
	return price;
}

void Pricer::reset()
{
	numSims = 0;
	price = 0.;
	sum = 0.;
}
