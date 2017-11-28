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

void		add_history(t_memory *memory)
{
	extern t_history	g_history;
	int					i;

	i = 0;
	while (i < 4096 - 1 && g_history.size[i])
		++i;
	g_history.size[i] = memory->size;
	g_history.address[i] = memory->data;
}

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
			ft_print_memory(memory->data, memory->data +\
			memory->size, memory->size);
			total += memory->size;
		}
		memory = memory->next;
	}
	return (total);
}

void		show_history_mem(void)
{
	extern t_history	g_history;
	int					i;
	size_t				total;

	total = 0;
	i = 0;
	ft_putstr("\033[31m");
	while (i < 4096 - 1 && g_history.size[i])
	{
		ft_print_memory(g_history.address[i], g_history.address[i]\
		+ g_history.size[i], g_history.size[i]);
		total += g_history.size[i];
		++i;
	}
	ft_putstr("\033[0m");
}

void		show_alloc_mem(void)
{
	extern t_index	g_index_memory;
	extern pthread_mutex_t		g_memory_mutex;
	size_t			total;

	total = 0;
	pthread_mutex_lock(&g_memory_mutex);
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
