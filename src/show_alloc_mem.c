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

size_t		ft_show_large_history(void)
{
	extern t_history	g_history;
	int					i;
	size_t				total;

	total = 0;
	i = 0;
	ft_putstr("\033[31m");
	while (g_history.large_size[i] && i < 1023)
	{
		ft_print_memory(g_history.large_address[i], g_history.large_address[i]\
		+ g_history.large_size[i], g_history.large_size[i]);
		total += g_history.large_size[i];
		++i;
	}
	ft_putstr("\033[0m");
	return (total);
}

size_t		ft_print_history(t_memory *memory)
{
	size_t	total;
	int		i;

	i = 0;
	total = 0;
	if (memory->free == 0)
	{
		ft_putstr("\033[32m");
		ft_print_memory(memory->data, memory->data +\
		memory->size, memory->size);
		total += memory->size;
	}
	ft_putstr("\033[31m");
	while (memory->history_size[i] && i < 1023)
	{
		ft_print_memory(memory->data, memory->data +\
		memory->size, memory->size);
		total += memory->size;
		++i;
	}
	ft_putstr("\033[0m");
	return (total);
}

void		add_history(t_memory *memory)
{
	int i;

	i = 0;
	while (memory->history_size[i] && i < 1023)
		++i;
	memory->history_size[i] = memory->size;
}

size_t		ft_show_memory(void *map, char *str, int history)
{
	t_memory	*memory;
	size_t		total;

	total = 0;
	ft_putstr(str);
	ft_putstr("\n");
	memory = (t_memory *)map;
	while (memory)
	{
		if (history)
			total += ft_print_history(memory);
		else if (memory->free == 0)
		{
			ft_print_memory(memory->data, memory->data +\
			memory->size, memory->size);
			total += memory->size;
		}
		memory = memory->next;
	}
	return (total);
}

void		display_memory(int history)
{
	extern t_index	g_index_memory;
	size_t			total;

	total = 0;
	initialize();
	pthread_mutex_lock(&g_memory_mutex);
	if (g_index_memory.tiny)
		total += ft_show_memory(g_index_memory.tiny, "TINY :", history);
	if (g_index_memory.small)
		total += ft_show_memory(g_index_memory.small, "SMALL :", history);
	if (g_index_memory.large)
		total += ft_show_memory(g_index_memory.large, "LARGE :", history);
	if (history == 1)
		total += ft_show_large_history();
	if (total)
	{
		ft_putstr("Total : ");
		ft_putnbr(total);
		ft_putstr(" octets\n");
	}
	pthread_mutex_unlock(&g_memory_mutex);
}

void		show_history_mem(void)
{
	display_memory(1);
}

void		show_alloc_mem(void)
{
	display_memory(0);
}
