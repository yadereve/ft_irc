/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:19:02 by yadereve          #+#    #+#             */
/*   Updated: 2025/03/06 09:19:03 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server()
{ }

Server::Server(const Server& other)
{
	(void)other;
}

Server& Server::operator=(const Server& other)
{
	(void)other;
	return *this;
}

Server::~Server()
{ }
