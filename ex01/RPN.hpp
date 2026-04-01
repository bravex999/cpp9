/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:48:10 by chnaranj          #+#    #+#             */
/*   Updated: 2026/04/01 16:48:17 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <list>
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
