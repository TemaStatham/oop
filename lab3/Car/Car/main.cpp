#include "CarControl.h"
#include <iostream>

int main()
{
	Car car;
	CarControl control(std::cin, std::cout, car);
	control.StartTrip();
	return 0;
}
