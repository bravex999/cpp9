/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:48:45 by chnaranj          #+#    #+#             */
/*   Updated: 2026/04/01 16:48:47 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:48:45 by chnaranj          #+#    #+#             */
/*   Updated: 2026/04/01 16:48:47 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <algorithm>
# include <iterator>
# include <utility>
# include <cstdlib>
# include <limits>
# include <sys/time.h>

class PmergeMe
{
private:
	std::vector<int> _vec;
	std::deque<int> _deq;
	double _vecTime;
	double _deqTime;

	void _mergeInsertionSortVec(std::vector<int> & c);
	void _binaryInsertVec(std::vector<int> & dest, int val);
	void _mergeInsertionSortDeq(std::deque<int> & c);
	void _binaryInsertDeq(std::deque<int> & dest, int val);

	static double getTime();

public:
	PmergeMe();
	PmergeMe(const PmergeMe & other);
	PmergeMe & operator=(const PmergeMe & other);
	~PmergeMe();

	bool parseArguments(int argc, char **argv);
	void run();
};

#endif
