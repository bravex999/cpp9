/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:48:26 by chnaranj          #+#    #+#             */
/*   Updated: 2026/04/01 16:48:28 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

double PmergeMe::getTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000.0) + tv.tv_usec;
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
		if (val <= 0 || val > std::numeric_limits<int>::max())
		{
			return false;
		}
		_vec.push_back(static_cast<int>(val));
		_deq.push_back(static_cast<int>(val));
	}
	return true;
}

void PmergeMe::_binaryInsertVec(std::vector<int> & dest, int val)
{
	std::vector<int>::iterator it = std::lower_bound(dest.begin(), dest.end(), val);
	dest.insert(it, val);
}

void PmergeMe::_mergeInsertionSortVec(std::vector<int> & c)
{
	size_t n = c.size();
	if (n < 2)
		return;

	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (c[i] < c[i + 1])
			pairs.push_back(std::make_pair(c[i + 1], c[i]));
		else
			pairs.push_back(std::make_pair(c[i], c[i + 1]));
	}

	int stray = -1;
	bool hasStray = (n % 2 != 0);
	if (hasStray)
		stray = c[n - 1];

	std::vector<int> main_chain;
	for (size_t i = 0; i < pairs.size(); i++)
		main_chain.push_back(pairs[i].first);

	_mergeInsertionSortVec(main_chain);

	std::vector<int> pendants;
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

	if (!pendants.empty())
		main_chain.insert(main_chain.begin(), pendants[0]);

	std::vector<size_t> jacob;
	jacob.push_back(1);
	jacob.push_back(3);
	while (jacob.back() < pendants.size())
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);

	size_t last = 1;
	for (size_t i = 1; i < jacob.size(); i++)
	{
		size_t curr = jacob[i];
		if (curr > pendants.size())
			curr = pendants.size();
		for (size_t j = curr; j > last; j--)
			_binaryInsertVec(main_chain, pendants[j - 1]);
		last = curr;
	}

	if (hasStray)
		_binaryInsertVec(main_chain, stray);
	c = main_chain;
}

void PmergeMe::_binaryInsertDeq(std::deque<int> & dest, int val)
{
	std::deque<int>::iterator it = std::lower_bound(dest.begin(), dest.end(), val);
	dest.insert(it, val);
}

void PmergeMe::_mergeInsertionSortDeq(std::deque<int> & c)
{
	size_t n = c.size();
	if (n < 2)
		return;

	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (c[i] < c[i + 1])
			pairs.push_back(std::make_pair(c[i + 1], c[i]));
		else
			pairs.push_back(std::make_pair(c[i], c[i + 1]));
	}

	int stray = -1;
	bool hasStray = (n % 2 != 0);
	if (hasStray)
		stray = c[n - 1];

	std::deque<int> main_chain;
	for (size_t i = 0; i < pairs.size(); i++)
		main_chain.push_back(pairs[i].first);

	_mergeInsertionSortDeq(main_chain);

	std::deque<int> pendants;
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

	if (!pendants.empty())
		main_chain.insert(main_chain.begin(), pendants[0]);

	std::vector<size_t> jacob;
	jacob.push_back(1);
	jacob.push_back(3);
	while (jacob.back() < pendants.size())
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);

	size_t last = 1;
	for (size_t i = 1; i < jacob.size(); i++)
	{
		size_t curr = jacob[i];
		if (curr > pendants.size())
			curr = pendants.size();
		for (size_t j = curr; j > last; j--)
			_binaryInsertDeq(main_chain, pendants[j - 1]);
		last = curr;
	}

	if (hasStray)
		_binaryInsertDeq(main_chain, stray);
	c = main_chain;
}


void PmergeMe::run()
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (i < 10)
			std::cout << _vec[i] << " ";
		else
		{
			std::cout << "[...]";
			break;
		}
	}
	std::cout << std::endl;

	double start_v = getTime();
	_mergeInsertionSortVec(_vec);
	_vecTime = getTime() - start_v;

	double start_d = getTime();
	_mergeInsertionSortDeq(_deq);
	_deqTime = getTime() - start_d;

	std::cout << "After:  ";
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (i < 10)
			std::cout << _vec[i] << " ";
		else
		{
			std::cout << "[...]";
			break;
		}
	}
	std::cout << std::endl;

	std::cout << "Time to process " << _vec.size() << " elements with std::vector : " << _vecTime << " us" << std::endl;
	std::cout << "Time to process " << _deq.size() << " elements with std::deque  : " << _deqTime << " us" << std::endl;
}
