#include "SDE.hpp"

SDE::SDE(double init, double mat) : ic(init), exp(mat)
{
}

SDE::~SDE()
{
}

double SDE::expiry()
{
	return exp;
}

double SDE::initial()
{
	return ic;
}

void SDE::expiry(double mat)
{
	exp = mat;
}

void SDE::initial(double init)
{
	ic = init;
}
