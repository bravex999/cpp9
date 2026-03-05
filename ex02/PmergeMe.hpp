#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <ctime>
# include <algorithm>
# include <iterator>

class PmergeMe
{
private:
	std::vector<int> _vec;
	std::deque<int> _deq;
	double _vecTime;
	double _deqTime;

	template <typename T>
	void _mergeInsertionSort(T & container);
	template <typename T>
	void _binaryInsert(T & dest, int val);

public:
	PmergeMe();
	PmergeMe(const PmergeMe & other);
	PmergeMe & operator=(const PmergeMe & other);
	~PmergeMe();

	bool parseArguments(int argc, char **argv);
	void run();
};

#endif
