#include "MCMediator.hpp"

MCMediator::MCMediator	(	std::tuple<SDEPtr, FDMPtr, RNGPtr> parts,
							int numSimulations,
							PricerPtr pricerPtr
						) :
							sde(std::get<0>(parts)),
							fdm(std::get<1>(parts)),
							rng(std::get<2>(parts)),
							numSims(numSimulations),
							pricer(pricerPtr),
							mediatorMutex()
{
}

void MCMediator::runSubSim(std::vector<double>& path, int numSubSims, int threadNum) 
{
	// shared resources will be used ahead, so lock the common mutex
	mediatorMutex.lock();

	// copy the rng to avoid using a common RNG in all threads
	// this way, threads don't have to wait to use the common RNG and can use their own
	RNGPtr rngCopy = rng->copy();
	FDMPtr fdmCopy = fdm->copy();

	// variables to hold temporary values in the path
	double vOld, vNew;
	double init = sde->initial();
	vOld = init;

	// can now unlock mutex
	mediatorMutex.unlock();

	// get number of steps and step size from common FDM
	int steps = fdmCopy->numberOfSteps();
	double stepSize = fdmCopy->sizeOfSteps();

	// set the initial value of the common SDE
	path[0] = vOld;

	for (int j = 0; j < numSubSims; ++j) 
	{
		if (((j / 5000) * 5000) == j) 
		{
			mediatorMutex.lock();
			std::cout << "Thread " << threadNum << " is at simulation number " << j << std::endl;
			mediatorMutex.unlock();
		}
		
		vOld = init;
		for (int i = 1; i < steps + 1; ++i)
		{
			// simulate a brownian increment using the RNG (copy)
			double brownianIncrement = ((*rngCopy)() * std::sqrt(stepSize));
			// calculate the next step in the FDM
			vNew = fdmCopy->advance(vOld, i * stepSize, brownianIncrement);
			// insert it in the path
			path[i] = vNew;

			vOld = vNew;
		}

		// lock the mutex
		mediatorMutex.lock();
		// allow common pricer to process the path
		pricer->processPath(path);
		// unlock mutex
		mediatorMutex.unlock();
	}

}

void MCMediator::runSim()
{
	// reset the pricer in case we are using it again
	pricer->reset();

	// a vector that holds the path vectors for each thread
	std::vector< std::vector<double> > pathHolder(NUM_THREADS);

	// round the number of simulations per thread
	int simsPerThread = numSims / NUM_THREADS;
	int simsLastThread = numSims - ((NUM_THREADS - 1) * simsPerThread);

	// insert path vectors with appropiate size for quick insertion
	for (int i = 0; i < NUM_THREADS; ++i) 
	{
		pathHolder[i] = std::vector<double>( fdm->numberOfSteps() + 1 );
	}
	
	// vector of threads that run simulations
	std::vector<std::thread> threadHolder(NUM_THREADS);
	for (int i = 0; i < NUM_THREADS; ++i) 
	{
		if (i == (NUM_THREADS - 1)) 
		{
			threadHolder[i] = std::thread(&MCMediator::runSubSim, this, pathHolder[i], simsLastThread, i);
		}
		else 
		{
			threadHolder[i] = std::thread(&MCMediator::runSubSim, this, pathHolder[i], simsPerThread, i);
		}
	}

	// join the threads
	for (int i = 0; i < NUM_THREADS; ++i) threadHolder[i].join();

	// calculate and print price
	pricer->calcPrice(sde->expiry());
	// print details
	pricer->printDetails();
}
