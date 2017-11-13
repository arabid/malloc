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

size_t	ft_show_memory(void *map) {
	t_memory 	*memory;
	int i;
	size_t total;

	total = 0;
	i = 0;
	memory = (t_memory *)map;
	printf("%p\n", memory);
	while (memory) {
		if (memory->free == 0) {
			//printf("%p - %p : %zu octets\n", (void *)memory + sizeof(t_memory), (void *)memory + sizeof(t_memory) + memory->size, memory->size);
			total += memory->size;
		}
		memory = memory->next;
	}
	return total;

}

void show_alloc_mem() {
	extern t_index g_index_memory;
	size_t total;

	total = 0;
	if (g_index_memory.tiny) {
		printf("TINY : ");
		total += ft_show_memory(g_index_memory.tiny);
	}
	if (g_index_memory.small) {
		printf("SMALL : ");
		total += ft_show_memory(g_index_memory.small);
	}
	if (g_index_memory.large) {
		printf("LARGE : ");
		total += ft_show_memory(g_index_memory.large);
	}
	if (total)
	{
		printf("Total : %zu octets\n", total);
	}
}

