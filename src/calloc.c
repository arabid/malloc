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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		((unsigned char*)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	*nothread_calloc(size_t count, size_t size)
{
	void		*ret;
	size_t		len;

	len = count * size;
	ret = nothread_malloc(len);
	if (!ret)
		return (NULL);
	ret = ft_memset(ret, 0, len);
	return (ret);
}

void	*calloc(size_t count, size_t size)
{
	void						*ret;
	extern pthread_mutex_t		g_memory_mutex;

	pthread_mutex_lock(&g_memory_mutex);
	ret = nothread_calloc(count, size);
	pthread_mutex_unlock(&g_memory_mutex);
	return (ret);
}
