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

void	*nothread_reallocf(void *ptr, size_t size)
{
	void	*ret;

	ret = nothread_realloc(ptr, size);
	if (ret == NULL)
		nothread_free(ptr);
	return (ret);
}

void	*reallocf(void *ptr, size_t size)
{
	void						*ret;
	extern pthread_mutex_t		g_memory_mutex;

	pthread_mutex_lock(&g_memory_mutex);
	ret = nothread_reallocf(ptr, size);
	pthread_mutex_unlock(&g_memory_mutex);
	return (ret);
}
