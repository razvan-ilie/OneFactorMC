// Razvan Ilie
// Test for Monte Carlo option pricing framework
// Framework allows us to pick any one factor SDE, FDM, RNG, payoff and pricing method

#include "DriftedBM.hpp"
#include "GBM.hpp"

#include "EuropeanPricer.hpp"
#include "AsianPricer.hpp"
#include "UpAndOutKnockoutPricer.hpp"

#include "Euler.hpp"
#include "Milstein.hpp"

#include "NormalDist.hpp"

#include "Exception.hpp"
#include "MCBuilder.hpp"
#include "MCMediator.hpp"

int main() 
{
	/****************************************************

	The test case that is used here is:

	GBM
	Milstein discretization: 1000 subdivisions
	European Call
	100,000 simulations

	S0 = 100
	r = 0.02
	vol = 0.2
	q = 0
	T = 1

	If you want to change any of:
	Builder
	Payoff
	Pricing Method

	there are a few other test cases here that are commented
	so just comment out the current builder/payoff/pricer and put remove the comment from another one

	****************************************************/

	// create builder
	//MCBuilder builder(SDEType::GBM, FDMType::Euler, RNGType::Normal);
	MCBuilder builder(SDEType::GBM, FDMType::Milstein, RNGType::Normal);
	//MCBuilder builder(SDEType::DriftedBM, FDMType::Euler, RNGType::Normal);
	//MCBuilder builder(SDEType::DriftedBM, FDMType::Milstein, RNGType::Normal);


	// set arguments
	std::vector<double> SDEArgs(5);
	SDEArgs[0] = 0.02;				// rf
	SDEArgs[1] = 0.2;				// sig
	SDEArgs[2] = 0.;				// div yield
	SDEArgs[3] = 100.;				// S0
	SDEArgs[4] = 1.;				// maturity

	int numberOfSteps = 1000;

	std::vector<double> RNGArgs(0);	// left empty for default Normal RNG

	builder.setArgs(SDEArgs, numberOfSteps, RNGArgs);

	// create payoff
	Payoff payoff ([](double S) { return std::max(S - 100, 0.); });
	//Payoff payoff([](double S) { return std::max(100 - S, 0.); });

	// crate discounting function
	auto disc = [](double t) {return std::exp(-0.02 * t); };

	// create pricer
	PricerPtr pricer(new EuropeanPricer(payoff, disc));
	//PricerPtr pricer(new AsianPricer(payoff, disc));
	//PricerPtr pricer(new UpAndOutKnockoutPricer(payoff, disc, 120));

	MCMediator mediator(builder.parts(), 100000, pricer);

	mediator.runSim();

	return 0;
}