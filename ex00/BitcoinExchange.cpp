/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:46:58 by chnaranj          #+#    #+#             */
/*   Updated: 2026/04/01 16:46:59 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
 
BitcoinExchange::BitcoinExchange() {}
 
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) { *this = other; }
 
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		this->_data = other._data;
	return *this;
}
 
BitcoinExchange::~BitcoinExchange() {}
 
bool BitcoinExchange::_isValidDate(const std::string& date) const
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}
	int y = std::atoi(date.substr(0, 4).c_str());
	int m = std::atoi(date.substr(5, 2).c_str());
	int d = std::atoi(date.substr(8, 2).c_str());
	if (y < 1 || m < 1 || m > 12 || d < 1)
		return false;
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
		days[1] = 29;
	return d <= days[m - 1];
}
 
 
void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database." << std::endl;
		std::exit(1);
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t sep = line.find(',');
		if (sep != std::string::npos)
			_data[line.substr(0, sep)] = std::atof(line.substr(sep + 1).c_str());
	}
}
 
void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t sep = line.find('|');
		if (sep == std::string::npos || sep == 0)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string date = line.substr(0, sep);
		date.erase(date.find_last_not_of(" \t") + 1);
		date.erase(0, date.find_first_not_of(" \t"));
		if (!_isValidDate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		std::string valStr = line.substr(sep + 1);
		char *end;
		double val = std::strtod(valStr.c_str(), &end);
		while (*end && std::isspace(*end))
			end++;
		if (*end || end == valStr.c_str())
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (val < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (val > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		std::map<std::string, float>::iterator it = _data.lower_bound(date);
		if (it != _data.end() && it->first == date)
			std::cout << date << " => " << val << " = " << (val * it->second) << std::endl;
		else if (it == _data.begin())
			std::cout << "Error: bad input => " << date << std::endl;
		else
		{
			--it;
			std::cout << date << " => " << val << " = " << (val * it->second) << std::endl;
		}
	}
}
