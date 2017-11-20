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

void	initialize(void)
{
	static	int			toggle = 0;
	extern t_index		g_index_memory;

	if (toggle == 0)
	{
		g_index_memory.tiny = NULL;
		g_index_memory.small = NULL;
		g_index_memory.large = NULL;
		pthread_mutex_init(&g_memory_mutex, NULL);
		++toggle;
	}
}

void	*malloc(size_t size)
{
	void			*ret;
	t_identifier	info;

	initialize();
	info = ft_check_size(size);
	pthread_mutex_lock(&g_memory_mutex);
	if (size == 0)
		ft_putstr("NAMEHO\n");
	if (info.id != 0)
	{
		ret = ft_memory_return(info, size);
	}
	else
		ret = MAP_FAILED;
	pthread_mutex_unlock(&g_memory_mutex);
	if (ret == MAP_FAILED)
	{
		return (NULL);
	}
	return (ret + sizeof(t_memory));
}
