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

void		erase_map(t_memory *memory, size_t size)
{
	size_t mod_size;

	mod_size = size % getpagesize() == 0 ? size : (size / getpagesize()\
	* getpagesize() + getpagesize());
	munmap((void *)memory, mod_size);
}

void		unlink_memory(t_memory **memory, t_memory *old)
{
	t_memory *cpy;

	cpy = *memory;
	if (*memory == old)
	{
		*memory = old->next;
	}
	else
	{
		while (cpy->next != old)
			cpy = cpy->next;
		cpy->next = old->next;
	}
}

t_memory	*check_valid_memory(void *ptr, t_memory *map)
{
	pthread_mutex_lock(&g_memory_mutex);
	while (map)
	{
		if (ptr == map->data)
			break ;
		map = map->next;
	}
	pthread_mutex_unlock(&g_memory_mutex);
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

void		free(void *ptr)
{
	extern t_index		g_index_memory;
	t_memory			*memory;

	initialize();
	if (!ptr)
	{
		return ;
	}
	memory = (t_memory *)(ptr - sizeof(t_memory));
	if (memory_check(ptr) == 0)
	{
		return ;
	}
	pthread_mutex_lock(&g_memory_mutex);
	memory->free = 1;
	if (memory->id == 3)
	{
		add_history(memory);
		unlink_memory(&g_index_memory.large, memory);
		erase_map(memory, memory->size + sizeof(t_memory));
	}
	pthread_mutex_unlock(&g_memory_mutex);
}
