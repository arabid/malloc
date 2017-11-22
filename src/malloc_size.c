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

size_t	malloc_size(const void *ptr)
{
	t_memory	*memory;

	initialize();
	if (!ptr)
		return (-1);
	memory = (t_memory *)(ptr - sizeof(t_memory));
	if (memory_check((void*)ptr) == 0)
		return (-1);
	return (memory->size);
}
