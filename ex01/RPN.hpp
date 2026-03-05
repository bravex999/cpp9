#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <string>

class RPN
{
public:
	RPN();
	RPN(const RPN & other);
	RPN & operator=(const RPN & other);
	~RPN();

	static void calculate(const std::string & expression);
};

#endif
