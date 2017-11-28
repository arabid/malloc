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


void	*nothread_malloc(size_t size)
{
	void						*ret;
	t_identifier				info;

	info = ft_check_size(size);
	if (info.id != 0)
	{
		ret = ft_memory_return(info, size);
	}
	else
		ret = MAP_FAILED;
	if (ret == MAP_FAILED)
	{
		return (NULL);
	}
	return (ret + sizeof(t_memory));

}

void	*malloc(size_t size)
{
	void	*ptr;
	extern pthread_mutex_t		g_memory_mutex;

	pthread_mutex_lock(&g_memory_mutex);
	ptr = nothread_malloc(size);
	pthread_mutex_unlock(&g_memory_mutex);
	return (ptr);
}
