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
