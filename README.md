# OneFactorMC
Library in C++11 that allows a user to price a derivative using any one factor SDE, discretization method, RNG and payoff function.
Monte Carlo simulations are multi-threaded.

The emphasis in this project was not so much on speed as it was on creating an elegant product that is easily portable, modifiable and extendable.
Many calls to virtual functions are made. To improve efficiency, one could modify the structure of the library by minimizing the amount of calls to virtual functions.

# Testing
There is a general test case in Test.cpp. Be sure to run in Release mode.

# Adding classes

Anytime a new SDE, FDM or RNG derived class is added, it should be added to its respective enum class in MCBuilder.hpp.
It should also be accounted for in the methods in MCBuilder.cpp.

## iSDE and iFDM
iSDE is an interface class for the one factor SDEs.
SDE is the base class.
More SDEs can be added by deriving from SDE.

iFDM is similar.

## RNG and Pricer
RNG and Pricer do not have interface classes. They are base classes which can also be derived from.

## How it works

- Create a builder for a specific type of SDE, FDM and RNG.
e.g.
```
MCBuilder builder(SDEType::GBM, FDMType::Milstein, RNGType::Normal);
```

- Set the arguments for SDE and RNG as well as the number of steps for the FDM. Number of elements in vectors depends on the type of SDE or RNG
e.g.
```
std::vector<double> SDEArgs(5);
SDEArgs[0] = 0.02;				// rf
SDEArgs[1] = 0.2;				  // sig
SDEArgs[2] = 0.;				  // div yield
SDEArgs[3] = 100.;				// S0
SDEArgs[4] = 1.;				  // maturity

int numberOfSteps = 1000;

std::vector<double> RNGArgs(0);	// left empty for default Normal RNG

builder.setArgs(SDEArgs, numberOfSteps, RNGArgs);
```
- Create a payoff function, discount function and a Pricer object that takes the payoff and discount functions
e.g.
```
Payoff payoff ([](double S) { return std::max(S - 100, 0.); });

// std::function<double (double)>
auto disc = [](double t) {return std::exp(-0.02 * t); };

PricerPtr pricer(new EuropeanPricer(payoff, disc));
```
- Create a MCMediator object that takes the parts that the builder creates, the number of simulations and the pricer

```
MCMediator mediator(builder.parts(), 100000, pricer);
```

- Run the simulation!
```
mediator.runSim();
```
