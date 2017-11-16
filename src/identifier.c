/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applying.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 19:39:50 by darabi            #+#    #+#             */
/*   Updated: 2016/02/22 19:41:02 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_identifier	*initialize_identifier(t_identifier *identifier,\
									size_t id, size_t size)
{
	identifier->id = id;
	identifier->size = size;
	return (identifier);
}

t_identifier	ft_check_size(size_t size)
{
	t_identifier	identifier;

	if (!size)
		return (*initialize_identifier(&identifier, 0, 0));
	else if (size <= TINY)
		return (*initialize_identifier(&identifier, 1, TINY));
	else if (size > SMALL)
		return (*initialize_identifier(&identifier, 3, size));
	return (*initialize_identifier(&identifier, 2, SMALL));
}
