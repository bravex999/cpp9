#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN & other) { *this = other; }
RPN & RPN::operator=(const RPN & other) { (void)other; return *this; }
RPN::~RPN() {}

void RPN::calculate(const std::string & expression)
{
	std::stack<int> stack;
	for (size_t i = 0; i < expression.length(); i++)
	{
		char c = expression[i];
		if (std::isspace(c)) continue;
		if (std::isdigit(c))
		{
			stack.push(c - '0');
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (stack.size() < 2)
			{
				std::cout << "Error" << std::endl;
				return;
			}
			int b = stack.top(); stack.pop();
			int a = stack.top(); stack.pop();
			if (c == '+') stack.push(a + b);
			else if (c == '-') stack.push(a - b);
			else if (c == '*') stack.push(a * b);
			else if (c == '/')
			{
				if (b == 0) { std::cout << "Error" << std::endl; return; }
				stack.push(a / b);
			}
		}
		else
		{
			std::cout << "Error" << std::endl;
			return;
		}
	}
	if (stack.size() != 1) std::cout << "Error" << std::endl;
	else std::cout << stack.top() << std::endl;
}
