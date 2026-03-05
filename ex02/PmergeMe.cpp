#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vecTime(0), _deqTime(0)
{
}

PmergeMe::PmergeMe(const PmergeMe & other)
{
	*this = other;
}

PmergeMe & PmergeMe::operator=(const PmergeMe & other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
		_vecTime = other._vecTime;
		_deqTime = other._deqTime;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

bool PmergeMe::parseArguments(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::string s = argv[i];
		if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos)
		{
			return false;
		}
		long val = std::atol(s.c_str());
		if (val <= 0)
		{
			return false;
		}
		_vec.push_back(static_cast<int>(val));
		_deq.push_back(static_cast<int>(val));
	}
	return true;
}

template <typename T>
void PmergeMe::_binaryInsert(T & dest, int val)
{
	typename T::iterator it = std::lower_bound(dest.begin(), dest.end(), val);
	dest.insert(it, val);
}

template <typename T>
void PmergeMe::_mergeInsertionSort(T & c)
{
	if (c.size() <= 1)
	{
		return;
	}
	T main_chain, pendants;
	for (size_t i = 0; i + 1 < c.size(); i += 2)
	{
		if (c[i] > c[i+1])
		{
			main_chain.push_back(c[i]);
			pendants.push_back(c[i+1]);
		}
		else
		{
			main_chain.push_back(c[i+1]);
			pendants.push_back(c[i]);
		}
	}
	int stray = (c.size() % 2 != 0) ? c.back() : -1;
	_mergeInsertionSort(main_chain);
	main_chain.insert(main_chain.begin(), pendants[0]);
	size_t jacob[] = { 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366 };
	size_t last_inserted = 1;
	for (int i = 0; i < 10; i++)
	{
		size_t target = jacob[i];
		if (target >= pendants.size())
		{
			target = pendants.size() - 1;
		}
		for (size_t k = target; k > last_inserted; k--)
		{
			_binaryInsert(main_chain, pendants[k]);
		}
		if (target == pendants.size() - 1)
		{
			break;
		}
		last_inserted = target;
	}
	if (stray != -1)
	{
		_binaryInsert(main_chain, stray);
	}
	c = main_chain;
}

void PmergeMe::run()
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size() && i < 10; i++)
	{
		std::cout << _vec[i] << " ";
	}
	if (_vec.size() > 10)
	{
		std::cout << "[...]";
	}
	std::cout << std::endl;
	clock_t start = clock();
	_mergeInsertionSort(_vec);
	_vecTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1e6;
	start = clock();
	_mergeInsertionSort(_deq);
	_deqTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1e6;
	std::cout << "After: ";
	for (size_t i = 0; i < _vec.size() && i < 10; i++)
	{
		std::cout << _vec[i] << " ";
	}
	if (_vec.size() > 10)
	{
		std::cout << "[...]";
	}
	std::cout << std::endl;
	std::cout << "Time to process " << _vec.size() << " elements with std::vector : " << _vecTime << " us" << std::endl;
	std::cout << "Time to process " << _deq.size() << " elements with std::deque : " << _deqTime << " us" << std::endl;
}
