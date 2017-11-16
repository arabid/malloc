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

t_index g_index_memory;

void			initialize_memory(t_memory *memory, size_t size, int id)
{
	if (!memory)
		return ;
	memory->next = NULL;
	memory->free = 0;
	memory->size = size;
	memory->id = id;
	memory->data = (void *)memory + sizeof(t_memory);
}

void			*ft_get_memory(t_memory *memory, int size,\
				t_identifier identifier, int i)
{
	while (memory)
	{
		if (memory->free)
		{
			memory->free = 0;
			memory->size = size;
			break ;
		}
		if (!memory->next)
		{
			if (!memory->free && i % NB_BY_MAP != 0)
			{
				memory->next = (void*)memory +\
				identifier.size + sizeof(t_memory);
				initialize_memory(memory->next, size, identifier.id);
				memory = memory->next;
				break ;
			}
		}
		memory = memory->next;
		++i;
	}
	return (void *)memory;
}

void			*create_map(size_t size)
{
	size_t		mod_size;
	void		*ret;

	mod_size = size % getpagesize() == 0 ? size :\
	(size / getpagesize() * getpagesize() + getpagesize());
	ret = mmap(0, mod_size, PROT_READ | PROT_WRITE,\
				MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ret == MAP_FAILED)
	{
		return (NULL);
	}
	return (ret);
}

void			associate_new_map(t_memory *memory, void *map)
{
	while (memory && memory->next)
		memory = memory->next;
	memory->next = (t_memory *)map;
}

void			*ft_memory_return(t_identifier identifier, size_t size)
{
	void		*ret;
	t_memory	**map;

	if (identifier.id == 3)
	{
		map = &g_index_memory.large;
		ret = create_map(size + sizeof(t_memory));
	}
	else
	{
		map = identifier.id == 1 ? &g_index_memory.tiny : &g_index_memory.small;
		if (*map && (ret = ft_get_memory(*map, size, identifier, 1)))
			return (ret);
		ret = create_map((identifier.size + sizeof(t_memory)) * 100);
	}
	if (*map)
		associate_new_map(*map, ret);
	else
		*map = (t_memory *)ret;
	initialize_memory((t_memory *)ret, size, identifier.id);
	return (ret);
}
