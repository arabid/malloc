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
	pthread_mutex_lock(&g_memory_mutex);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	pthread_mutex_unlock(&g_memory_mutex);
	return (dst);
}

void			realloc_modif(t_memory **memory, size_t size,\
				void **ret, void *ptr)
{
	(*memory)->size = size;
	*ret = ptr;
	pthread_mutex_unlock(&g_memory_mutex);
}

void			*realloc(void *ptr, size_t size)
{
	void			*ret;
	t_identifier	info_new;
	t_memory		*memory;

	initialize();
	if (!ptr)
		return (malloc(size));
	if (!size || memory_check(ptr) == 0)
		return (NULL); //CHANGE ?
	pthread_mutex_lock(&g_memory_mutex);
	memory = ptr - sizeof(t_memory);
	info_new = ft_check_size(size);
	if (info_new.id == 3 || info_new.id != memory->id)
	{
		pthread_mutex_unlock(&g_memory_mutex);
		ret = malloc(size);
		size = size >= memory->size ? memory->size : size;
		ft_memcpy(ret, ptr, size);
		free(ptr);
	}
	else
		realloc_modif(&memory, size, &ret, ptr);
	return (ret);
}
