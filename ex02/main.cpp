/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:48:33 by chnaranj          #+#    #+#             */
/*   Updated: 2026/04/01 16:48:34 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	PmergeMe pm;
	if (!pm.parseArguments(argc, argv))
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	pm.run();
	return 0;
}
