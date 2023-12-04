#include "stdafx.h"
#include "task1.h"

std::vector<double> ReadVector(std::istream& in)
{
	std::vector<double> numbers(std::istream_iterator<double>(in), (std::istream_iterator<double>()));

	if (!in.eof() || in.bad())
	{
		return std::vector<double>();
	}

	return numbers;
}

double CalcArithmeticMean(const std::vector<double>& numbers)
{
	double sum = 0;
	//Todo: использовать size_t
	int countPositiveElems = 0;
	//Todo: использовать std::accumulate
	for (double number : numbers)
	{
		if (number > 0)
		{
			sum += number;
			countPositiveElems++;
		}
	}

	if (countPositiveElems == 0)
	{
		return 0;
	}

	//Todo: static_cast изьыточен
	return sum / static_cast<double>(countPositiveElems);
}

void ProcessVector(std::vector<double>& numbers)
{
	double arithmeticMean = CalcArithmeticMean(numbers);

	if (arithmeticMean == 0)
	{
		return;
	}

	//Todo: arithmeticmean, number можно передать по значению и укоротить строку и 
	std::transform(numbers.begin(), numbers.end(), numbers.begin(), [arithmeticMean](double number) {return number + arithmeticMean; });

	return;
}

void PrintVector(std::vector<double>& numbers, std::ostream& out)
{
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(out, " "));
	out << '\n';
}

void SortVector(std::vector<double>& numbers)
{
	std::sort(numbers.begin(), numbers.end());
}
