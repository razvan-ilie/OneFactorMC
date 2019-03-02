#include "RNG.hpp"

RNG::RNG() : randEngine(myClock::now().time_since_epoch().count())
{
}

RNG::RNG(int seed) : randEngine(seed)
{
}
