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

void	*valloc(size_t size)
{
	t_identifier	info;
	void			*ret;

	if (!size)
		return (NULL);
	info.size = size;
	info.id = 3;
	pthread_mutex_lock(&g_memory_mutex);
	ret = ft_memory_return(info, size);
	pthread_mutex_unlock(&g_memory_mutex);
	if (ret == MAP_FAILED)
		return (NULL);
	return (ret + sizeof(t_memory));
}
