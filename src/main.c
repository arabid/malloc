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


void			*ft_get_memory(t_memory *memory, int size)
{
	void	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (memory)
	{
		++i;
		if (memory->free)
		{
			memory->free = 0;
			memory->size = size;
			break ;
		}
		memory = memory->next;
	}
	return (void *)memory;
}

void			hash_memory(void *map, size_t length, int id)
{
	int			i;
	t_memory	*memory;

	if (!map || (int)map == -1)
		return ;
	i = 0;
	memory = (t_memory *)map;
	while (1)
	{
		memory->size = length;
		memory->free = 1;
		memory->data = (void*)memory + sizeof(t_memory);
		memory->id = id;
		if (i < NB_BY_MAP - 1)
		{
			memory->next = (t_memory *)(map + i *\
				(sizeof(t_memory) + length));
		}
		else
		{
			memory->next = NULL;
			break ;
		}
		memory = memory->next;
		++i;
	}
}

void			*create_map(size_t size)
{
	size_t		mod_size;
	void		*ret;

	mod_size = size % getpagesize() == 0 ? size :\
	(size / getpagesize() * getpagesize() + getpagesize());
	ret = mmap(0, mod_size, PROT_READ | PROT_WRITE,\
				MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ret == MAP_FAILED) {
		printf("MALLOC ERROR\n");
		return NULL;
	}
	return (ret);
}

void			initialize_memory(t_memory *memory, size_t size, int id)
{
	if (!memory)
		return ;
	memory->free = 0;
	memory->size = size;
	memory->id = id;
	memory->data = (void *)memory + sizeof(t_memory);
}

void			associate_new_map(t_memory *memory, void *map)
{
	while (memory && memory->next)
	{
		memory = memory->next;
	}
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
		if (*map && (ret = ft_get_memory(*map, size)))
			return (ret);
		ret = create_map((identifier.size + sizeof(t_memory)) * 100);
		hash_memory(ret, identifier.size, identifier.id);
	}
	if (*map)
		associate_new_map(*map, ret);
	else
		*map = (t_memory *)ret;
	initialize_memory((t_memory *)ret, size, identifier.id);
	return (ret);
}

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
