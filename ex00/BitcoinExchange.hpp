/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:47:06 by chnaranj          #+#    #+#             */
/*   Updated: 2026/04/01 16:47:08 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <string>
# include <fstream>
# include <sstream>
# include <cstdlib>

class BitcoinExchange
{
private:
	std::map<std::string, float> _data;
	bool _isValidDate(const std::string & date) const;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange & other);
	BitcoinExchange & operator=(const BitcoinExchange & other);
	~BitcoinExchange();

	void loadDatabase(const std::string & filename);
	void processInput(const std::string & filename);
};

#endif
