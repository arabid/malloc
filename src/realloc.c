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

#include "../includes/malloc.h"

void	*ft_cpy(void *dst, const void *src, size_t n)
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

void			*realloc(void *ptr, size_t size)
{
	void			*ret;
	t_identifier 	info_new;
	t_memory		*memory;

	if (!ptr)
	{
		return (malloc(size));
	}
	if (!size)
		return (NULL);
	memory = ptr - sizeof(t_memory);
	if (memory->data != ptr)
		return NULL;
	info_new = ft_check_size(size);
	if ((info_new.id == 3 && memory->size < size) || info_new.id != memory->id)
	{
		ret = malloc(size);
		printf("ID DU REALLOC = %d\n", memory->id);
		ft_cpy(ret, ptr, memory->size);
		free(ptr);
	}
	else
	{
		memory->size = size;
		ret = ptr;
	}
	return (ret);
}
