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

void		free(void *ptr)
{
	extern t_index		g_index_memory;
	t_memory			*memory;

	memory = (t_memory *)(ptr - sizeof(t_memory));
	memory->free = 1;
	if (memory->id == 3)
	{
		unlink_memory(&g_index_memory.large, memory);
		erase_map(memory, memory->size + sizeof(t_memory));
	}
}
