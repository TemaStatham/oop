#include "EratosthenesSieve.h"

void PrintSet(std::set<int>& set, std::ostream& out)
{
	for (auto el : set)
	{
		out << el << " ";
	}
	out << '\n';
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	//������ +10
	std::vector<bool> sieve(upperBound + 10, true);

	for (int i = MIN_PRIME_NUMBER; i <= static_cast<int>(sqrt(upperBound) + 1); i++)
	{
		if (sieve[i])
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				sieve[j] = false;
			}
		}
	}

	std::set<int> result;

	for (int i = MIN_PRIME_NUMBER; i <= upperBound; i++)
	{
		//������ ����� ������� ����� ������
		std::set<int>::iterator it = result.lower_bound(static_cast<int>(sqrt(upperBound) + 1));
		if (sieve[i])
		{
			//��� ������ �� ���������
			result.insert(result.end(), i);
		}
	}

	return result;
}