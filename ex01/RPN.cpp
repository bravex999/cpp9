/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:47:57 by chnaranj          #+#    #+#             */
/*   Updated: 2026/04/01 16:47:58 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN & other)
{
	(void)other;
}

RPN & RPN::operator=(const RPN & other)
{
	(void)other;
	return *this;
}

RPN::~RPN()
{
}

void RPN::calculate(const std::string & expression)
{
	std::stack<int, std::list<int> > stack;

	for (size_t i = 0; i < expression.length(); i++)
	{
		char c = expression[i];
		if (std::isspace(c))
		{
			continue;
		}
		if (c == '-' && i + 1 < expression.length() && std::isdigit(expression[i + 1]))
		{
			i++;
			stack.push(-(expression[i] - '0'));
			continue;
		}
		if (std::isdigit(c))
		{
			stack.push(c - '0');
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (stack.size() < 2)
			{
				std::cerr << "Error" << std::endl;
				return;
			}
			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();
			if (c == '+')
			{
				if ((b > 0 && a > 2147483647 - b) || (b < 0 && a < -2147483647 - 1 - b))
				{
					std::cerr << "Error" << std::endl;
					return;
				}
				stack.push(a + b);
			}
			else if (c == '-')
			{
				if ((b < 0 && a > 2147483647 + b) || (b > 0 && a < -2147483647 - 1 + b))
				{
					std::cerr << "Error" << std::endl;
					return;
				}
				stack.push(a - b);
			}
			else if (c == '*')
			{
				if (a != 0 && b != 0)
				{
					if ((a > 0 && b > 0 && a > 2147483647 / b) || (a > 0 && b < 0 && b < (-2147483647 - 1) / a) || (a < 0 && b > 0 && a < (-2147483647 - 1) / b) || (a < 0 && b < 0 && a < 2147483647 / b))
					{
						std::cerr << "Error" << std::endl;
						return;
					}
				}
				stack.push(a * b);
			}
			else
			{
				if (b == 0)
				{
					std::cerr << "Error" << std::endl;
					return;
				}
				if (a == -2147483647 - 1 && b == -1)
				{
					std::cerr << "Error" << std::endl;
					return;
				}
				stack.push(a / b);
			}
		}
		else
		{
			std::cerr << "Error" << std::endl;
			return;
		}
	}
	if (stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
	}
	else
	{
		std::cout << stack.top() << std::endl;
	}
}
