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

size_t		ft_show_memory(void *map, char *str)
{
	t_memory	*memory;
	size_t		total;

	total = 0;
	ft_putstr(str);
	ft_putstr("\n");
	memory = (t_memory *)map;
	while (memory)
	{
		if (memory->free == 0)
		{
			ft_putstr("  ");
			ft_print_memory((void *)memory);
			total += memory->size;
		}
		memory = memory->next;
	}
	return (total);
}

void		show_alloc_mem(void)
{
	extern t_index	g_index_memory;
	size_t			total;

	initialize();
	pthread_mutex_lock(&g_memory_mutex);
	total = 0;
	if (g_index_memory.tiny)
		total += ft_show_memory(g_index_memory.tiny, "TINY :");
	if (g_index_memory.small)
		total += ft_show_memory(g_index_memory.small, "SMALL :");
	if (g_index_memory.large)
		total += ft_show_memory(g_index_memory.large, "LARGE :");
	if (total)
	{
		ft_putstr("Total : ");
		ft_putnbr(total);
		ft_putstr(" octets\n");
	}
	pthread_mutex_unlock(&g_memory_mutex);
}
