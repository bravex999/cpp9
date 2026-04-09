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
# include <utility>
# include <cstdlib>
# include <limits>
# include <sys/time.h>
 
class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;
	double				_vecTime;
	double				_deqTime;
 
	void	_sortVec(std::vector<int> & c);
	void	_sortDeq(std::deque<int> & c);
	static double	getTime();
 
public:
	PmergeMe();
	PmergeMe(const PmergeMe & other);
	PmergeMe & operator=(const PmergeMe & other);
	~PmergeMe();
 
	bool	parseArguments(int argc, char **argv);
	void	run();
};
 
#endif
 
