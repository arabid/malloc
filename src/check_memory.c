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

#include "malloc.h"

t_memory	*check_valid_memory(void *ptr, t_memory *map)
{
	extern pthread_mutex_t		g_memory_mutex;

	while (map)
	{
		if (ptr == map->data)
			break ;
		map = map->next;
	}
	return (map);
}

int			memory_check(void *ptr)
{
	extern t_index		g_index_memory;

	if (check_valid_memory(ptr, g_index_memory.tiny))
		return (1);
	if (check_valid_memory(ptr, g_index_memory.small))
		return (1);
	if (check_valid_memory(ptr, g_index_memory.large))
		return (1);
	return (0);
}
