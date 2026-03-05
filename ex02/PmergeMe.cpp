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
		if (val <= 0 || val > 2147483647)
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
	size_t n = c.size();
	if (n <= 1)
	{
		return;
	}

	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (c[i] < c[i + 1])
		{
			pairs.push_back(std::make_pair(c[i + 1], c[i]));
		}
		else
		{
			pairs.push_back(std::make_pair(c[i], c[i + 1]));
		}
	}
	
	int stray = (n % 2 != 0) ? c.back() : -1;

	T main_chain;
	for (size_t i = 0; i < pairs.size(); i++)
	{
		main_chain.push_back(pairs[i].first);
	}

	_mergeInsertionSort(main_chain);

	T pendants;
	for (size_t i = 0; i < main_chain.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (main_chain[i] == pairs[j].first)
			{
				pendants.push_back(pairs[j].second);
				pairs.erase(pairs.begin() + j);
				break;
			}
		}
	}

	main_chain.insert(main_chain.begin(), pendants[0]);

	size_t jacob[] = {2, 6, 10, 22, 42, 86, 170, 342, 682, 1366, 2730, 5462, 10922};
	size_t last_idx = 1;
	for (size_t i = 0; i < 13; i++)
	{
		size_t target = jacob[i];
		if (target >= pendants.size())
		{
			target = pendants.size() - 1;
		}
		for (size_t k = target; k > last_idx; k--)
		{
			_binaryInsert(main_chain, pendants[k]);
		}
		if (target == pendants.size() - 1)
		{
			break;
		}
		last_idx = target;
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
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (i < 10)
		{
			std::cout << _vec[i] << " ";
		}
		else
		{
			std::cout << "[...] ";
			break;
		}
	}
	std::cout << std::endl;

	clock_t v_start = clock();
	_mergeInsertionSort(_vec);
	_vecTime = static_cast<double>(clock() - v_start) / CLOCKS_PER_SEC * 1e6;

	clock_t d_start = clock();
	_mergeInsertionSort(_deq);
	_deqTime = static_cast<double>(clock() - d_start) / CLOCKS_PER_SEC * 1e6;

	std::cout << "After:  ";
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (i < 10)
		{
			std::cout << _vec[i] << " ";
		}
		else
		{
			std::cout << "[...] ";
			break;
		}
	}
	std::cout << std::endl;

	std::cout << "Time to process " << _vec.size() << " elements with std::vector : " << _vecTime << " us" << std::endl;
	std::cout << "Time to process " << _deq.size() << " elements with std::deque  : " << _deqTime << " us" << std::endl;
}
