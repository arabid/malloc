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

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

void			realloc_second_part(t_memory **memory, size_t size,\
				void *ptr, void **ret)
{
	add_history(*memory);
	(*memory)->size = size;
	*ret = ptr;
}

void			*nothread_realloc(void *ptr, size_t size)
{
	void			*ret;
	t_identifier	info_new;
	t_memory		*memory;

	if (!ptr)
		return (nothread_malloc(size));
	if (!size)
		size = TINY;
	if (memory_check(ptr) == 0)
		return (NULL);
	memory = ptr - sizeof(t_memory);
	info_new = ft_check_size(size);
	if (info_new.id == 3 || info_new.id != memory->id)
	{
		ret = nothread_malloc(size);
		if (!ret)
			return (NULL);
		size = size >= memory->size ? memory->size : size;
		ft_memcpy(ret, ptr, size);
		nothread_free(ptr);
	}
	else
		realloc_second_part(&memory, size, ptr, &ret);
	return (ret);
}

void			*realloc(void *ptr, size_t size)
{
	void						*ret;
	extern pthread_mutex_t		g_memory_mutex;

	pthread_mutex_lock(&g_memory_mutex);
	ret = nothread_realloc(ptr, size);
	pthread_mutex_unlock(&g_memory_mutex);
	return (ret);
}
