#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vecTime(0), _deqTime(0) {}
PmergeMe::PmergeMe(const PmergeMe & other) { *this = other; }
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
PmergeMe::~PmergeMe() {}

bool PmergeMe::parseArguments(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::string s = argv[i];
		if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos)
			return false;
		int val = std::atoi(s.c_str());
		if (val < 0) return false;
		_vec.push_back(val);
		_deq.push_back(val);
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
	if (c.size() <= 1) return;
	
	T main_chain, pendants;
	for (size_t i = 0; i + 1 < c.size(); i += 2)
	{
		if (c[i] > c[i+1]) { main_chain.push_back(c[i]); pendants.push_back(c[i+1]); }
		else { main_chain.push_back(c[i+1]); pendants.push_back(c[i]); }
	}
	if (c.size() % 2 != 0) pendants.push_back(c.back());

	_mergeInsertionSort(main_chain);
	for (typename T::iterator it = pendants.begin(); it != pendants.end(); ++it)
		_binaryInsert(main_chain, *it);
	c = main_chain;
}

void PmergeMe::run()
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size() && i < 10; i++) std::cout << _vec[i] << " ";
	if (_vec.size() > 10) std::cout << "[...]";
	std::cout << std::endl;

	clock_t start = clock();
	_mergeInsertionSort(_vec);
	_vecTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1e6;

	start = clock();
	_mergeInsertionSort(_deq);
	_deqTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1e6;

	std::cout << "After: ";
	for (size_t i = 0; i < _vec.size() && i < 10; i++) std::cout << _vec[i] << " ";
	if (_vec.size() > 10) std::cout << "[...]";
	std::cout << std::endl;

	std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << _vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque : " << _deqTime << " us" << std::endl;
}
