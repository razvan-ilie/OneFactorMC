#include "MCBuilder.hpp"

//return the right SDE
SDEPtr MCBuilder::getSDE()
{
	switch (builderSDE) 
	{
	case SDEType::GBM:
		return SDEPtr(new GBM(sdeArgs[0], sdeArgs[1], sdeArgs[2], sdeArgs[3], sdeArgs[4]));

	case SDEType::DriftedBM:
		return SDEPtr(new DriftedBM(sdeArgs[0], sdeArgs[1], sdeArgs[2], sdeArgs[3], sdeArgs[4]));

	default:
		throw Exception("Unknown SDE");
	}
}

FDMPtr MCBuilder::getFDM(SDEPtr sdePtr)
{
	switch (builderFDM) 
	{
	case FDMType::Euler:
		return FDMPtr(new Euler(sdePtr, numSteps));

	case FDMType::Milstein:
		return FDMPtr(new Milstein(sdePtr, numSteps));
	default:
		throw Exception("Unknown FDM");
	}
}

RNGPtr MCBuilder::getRNG()
{
	switch (builderRNG) 
	{
	case RNGType::Normal:
		return RNGPtr(new NormalDist);
	default:
		throw Exception("Unknown RNG");
	}
}

MCBuilder::MCBuilder(	SDEType chooseSDE,
						FDMType chooseFDM,
						RNGType chooseRNG
					) : 
						builderSDE(chooseSDE),
						builderFDM(chooseFDM),
						builderRNG(chooseRNG),
						// flag that arguments are not yet set
						argsSetFlag(false),
						// default arguments
						sdeArgs(),
						numSteps(0),
						rngArgs()
{

}

// here, we check that the number of parameters needed for each respective SDE and RNG is correct
// otherwise print an error message and return without setting anything
void MCBuilder::setArgs	(const std::vector<double>& SDEArgs,
						int numberSteps,
						const std::vector<double>& RNGArgs
						)
{	
	// an alternative to this approach would be to have a static member
	// for each of these classes that contains the number of arguments that should be used
	if  (	(builderSDE == SDEType::GBM) || 
			(builderSDE == SDEType::DriftedBM)
		) 
	{
		if (SDEArgs.size() != 5) 
		{
			std::cout << "Wrong number of parameters for SDE, you need 5, try again\n";
			return;
		}
	}
	// other SDE cases can be added here

	if (builderRNG == RNGType::Normal
		)
	{
		if ((RNGArgs.size() != 0) &&
			(RNGArgs.size() != 1) && 
			(RNGArgs.size() != 2) && 
			(RNGArgs.size() != 3) )
		{
			std::cout << "Wrong number of arguments for RNG, you need 0, 1, 2 or 3, try again\n";
			return;
		}
	}
	// other RNG cases can be added here

	// if everything is ok, set the arguments
	sdeArgs = SDEArgs;
	numSteps = numberSteps;
	rngArgs = RNGArgs;

	// and set the flag to signal they have been set
	argsSetFlag = true;
}

std::tuple<SDEPtr, FDMPtr, RNGPtr> MCBuilder::parts()
{
	if (!argsSetFlag) throw Exception("Arguments are not set");

	// try to get the objects and return the tuple
	try 
	{
		SDEPtr eqn = getSDE();
		FDMPtr fd = getFDM(eqn);
		RNGPtr rand = getRNG();
		return std::make_tuple(eqn, fd, rand);
	}

	// if an exception is thrown, throw it again
	catch (Exception& e) 
	{
		std::cout << e.what() << std::endl;
		throw e;
	}
}