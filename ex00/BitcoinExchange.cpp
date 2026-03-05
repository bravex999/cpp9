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
	if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;
	int y = std::atoi(date.substr(0, 4).c_str());
	int m = std::atoi(date.substr(5, 2).c_str());
	int d = std::atoi(date.substr(8, 2).c_str());
	if (y < 2008 || m < 1 || m > 12 || d < 1) return false;
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) days[1] = 29;
	return d <= days[m - 1];
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open()) { std::cerr << "Error: could not open database." << std::endl; std::exit(1); }
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
	if (!file.is_open()) { std::cerr << "Error: could not open file." << std::endl; return; }
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t sep = line.find('|');
		if (sep == std::string::npos) { std::cout << "Error: bad input => " << line << std::endl; continue; }
		std::string date = line.substr(0, sep - 1);
		date.erase(date.find_last_not_of(" \n\r\t") + 1);
		if (!_isValidDate(date)) { std::cout << "Error: bad input => " << date << std::endl; continue; }
		double val = std::atof(line.substr(sep + 1).c_str());
		if (val < 0) { std::cout << "Error: not a positive number." << std::endl; continue; }
		if (val > 1000) { std::cout << "Error: too large a number." << std::endl; continue; }
		std::map<std::string, float>::iterator it = _data.lower_bound(date);
		if (it == _data.end() || (it->first != date && it != _data.begin())) --it;
		std::cout << date << " => " << val << " = " << (val * it->second) << std::endl;
	}
}
