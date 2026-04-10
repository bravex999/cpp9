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
 
double PmergeMe::getTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000.0 + tv.tv_usec;
}
 
bool PmergeMe::parseArguments(int argc, char **argv)
{
	_vecTime = 0;
	_deqTime = 0;
	for (int i = 1; i < argc; i++)
	{
		std::string s = argv[i];
		if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos)
			return false;
		long val = std::atol(s.c_str());
		if (val <= 0 || val > std::numeric_limits<int>::max())
			return false;
		double t = getTime();
		_vec.push_back(static_cast<int>(val));
		_vecTime += getTime() - t;
		t = getTime();
		_deq.push_back(static_cast<int>(val));
		_deqTime += getTime() - t;
	}
	return true;
}
 
/* ========================== VECTOR ========================== */
 
void PmergeMe::_sortVec(std::vector<int> & c)
{
	if (c.size() < 2)
		return;
 
	
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < c.size(); i += 2)
	{
		if (c[i] > c[i + 1])
			pairs.push_back(std::make_pair(c[i], c[i + 1]));
		else
			pairs.push_back(std::make_pair(c[i + 1], c[i]));
	}
	bool hasStray = (c.size() % 2 != 0);
	int stray = hasStray ? c.back() : -1;
 
	
	std::vector<int> main_chain;
	for (size_t i = 0; i < pairs.size(); i++)
		main_chain.push_back(pairs[i].first);
	std::vector<std::pair<int, int> > savedPairs = pairs;
	_sortVec(main_chain);
 
	
	std::vector<int> pend;
	std::vector<std::pair<int, int> > tmp = savedPairs;
	for (size_t i = 0; i < main_chain.size(); i++)
	{
		for (size_t j = 0; j < tmp.size(); j++)
		{
			if (main_chain[i] == tmp[j].first)
			{
				pend.push_back(tmp[j].second);
				tmp.erase(tmp.begin() + j);
				break;
			}
		}
	}
 
	
	if (!pend.empty())
		main_chain.insert(main_chain.begin(), pend[0]);
 
	
	std::vector<size_t> pos(pend.size());
	for (size_t i = 0; i < pend.size(); i++)
		pos[i] = i + 1;
 
	
	std::vector<size_t> jacob;
	jacob.push_back(1);
	jacob.push_back(3);
	while (jacob.back() < pend.size())
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
 
	
	size_t last = 1;
	for (size_t i = 1; i < jacob.size(); i++)
	{
		size_t curr = jacob[i];
		if (curr > pend.size())
			curr = pend.size();
		for (size_t j = curr; j > last; j--)
		{
			size_t bound = pos[j - 1];
			std::vector<int>::iterator it = std::lower_bound(
				main_chain.begin(), main_chain.begin() + bound, pend[j - 1]);
			size_t ins = it - main_chain.begin();
			main_chain.insert(it, pend[j - 1]);
			for (size_t k = 0; k < pos.size(); k++)
			{
				if (pos[k] >= ins)
					pos[k]++;
			}
		}
		last = curr;
	}
 
	
	if (hasStray)
	{
		std::vector<int>::iterator it = std::lower_bound(
			main_chain.begin(), main_chain.end(), stray);
		main_chain.insert(it, stray);
	}
	c = main_chain;
}
 
/* ========================== DEQUE ========================== */
 
void PmergeMe::_sortDeq(std::deque<int> & c)
{
	if (c.size() < 2)
		return;
 
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < c.size(); i += 2)
	{
		if (c[i] > c[i + 1])
			pairs.push_back(std::make_pair(c[i], c[i + 1]));
		else
			pairs.push_back(std::make_pair(c[i + 1], c[i]));
	}
	bool hasStray = (c.size() % 2 != 0);
	int stray = hasStray ? c.back() : -1;
 
	std::deque<int> main_chain;
	for (size_t i = 0; i < pairs.size(); i++)
		main_chain.push_back(pairs[i].first);
	std::vector<std::pair<int, int> > savedPairs = pairs;
	_sortDeq(main_chain);
 
	std::deque<int> pend;
	std::vector<std::pair<int, int> > tmp = savedPairs;
	for (size_t i = 0; i < main_chain.size(); i++)
	{
		for (size_t j = 0; j < tmp.size(); j++)
		{
			if (main_chain[i] == tmp[j].first)
			{
				pend.push_back(tmp[j].second);
				tmp.erase(tmp.begin() + j);
				break;
			}
		}
	}
 
	if (!pend.empty())
		main_chain.insert(main_chain.begin(), pend[0]);
 
	std::vector<size_t> pos(pend.size());
	for (size_t i = 0; i < pend.size(); i++)
		pos[i] = i + 1;
 
	std::vector<size_t> jacob;
	jacob.push_back(1);
	jacob.push_back(3);
	while (jacob.back() < pend.size())
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
 
	size_t last = 1;
	for (size_t i = 1; i < jacob.size(); i++)
	{
		size_t curr = jacob[i];
		if (curr > pend.size())
			curr = pend.size();
		for (size_t j = curr; j > last; j--)
		{
			size_t bound = pos[j - 1];
			std::deque<int>::iterator it = std::lower_bound(
				main_chain.begin(), main_chain.begin() + bound, pend[j - 1]);
			size_t ins = it - main_chain.begin();
			main_chain.insert(it, pend[j - 1]);
			for (size_t k = 0; k < pos.size(); k++)
			{
				if (pos[k] >= ins)
					pos[k]++;
			}
		}
		last = curr;
	}
 
	if (hasStray)
	{
		std::deque<int>::iterator it = std::lower_bound(
			main_chain.begin(), main_chain.end(), stray);
		main_chain.insert(it, stray);
	}
	c = main_chain;
}
 
/* ========================== RUN ========================== */
 
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
 
	double t = getTime();
	_sortVec(_vec);
	_vecTime += getTime() - t;

	t = getTime();
	_sortDeq(_deq);
	_deqTime += getTime() - t;
 
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
 
	std::cout << "Time to process " << _vec.size()
		<< " elements with std::vector : " << _vecTime << " us" << std::endl;
	std::cout << "Time to process " << _deq.size()
		<< " elements with std::deque  : " << _deqTime << " us" << std::endl;
}
 
