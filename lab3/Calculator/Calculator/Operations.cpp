#include "stdafx.h"
#include "Operations.h"

double Operations::PerfomOperation(Operations::Operation operation, double firstVal, double secValue)
{
	switch (operation)
	{
	case Operations::Operation::ADDITION:
		return Addition(firstVal, secValue);
	case Operations::Operation::SUBSTRACTION:
		return Substraction(firstVal, secValue);
	case Operations::Operation::DIVISION:
		return Division(firstVal, secValue);
	case Operations::Operation::MULTIPLICATION:
		return Operations::Multiplication(firstVal, secValue);
	default:
		return NOT_A_NUMBER;
	}
}

double Operations::Addition(double firstVal, double secondVal)
{
	double s = firstVal + secondVal;
	double d = firstVal - s + secondVal;
	return s + d;
}

double Operations::Substraction(double firstVal, double secondVal)
{
	double s = firstVal - secondVal;
	double d = firstVal - s - secondVal;
	return s + d;
}

double Operations::Division(double firstVal, double secondVal)
{
	if (secondVal == 0)
	{
		return NOT_A_NUMBER;
	}
	double q = firstVal / secondVal;
	if (secondVal == 1 || secondVal == -1 || abs(q) >= DBL_MIN)
	{
		return q;
	}
	double r = firstVal - q * secondVal;
	double t = r + secondVal;
	return q + t / secondVal;
}

double Operations::Multiplication(double firstVal, double secondVal)
{
	double p = firstVal * secondVal;
	if (firstVal == 0 || secondVal == 0 || abs(p) >= DBL_MIN)
	{
		return p;
	}
	double ah = firstVal / 2;
	double bh = secondVal / 2;
	double al = firstVal - ah;
	double bl = secondVal - bh;
	double ph = ah * bh;
	double pm = (ah + al) * (bh + bl) - ph;
	return 2 * (ph - pm) + p;
}
