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
	info_new = ft_check_size(size);
	if ((info_new.id == 3 && memory->size < size) || info_new.id != memory->id)
	{
		ret = malloc(size);
		//MEMCPY
		memcpy(ret, ptr, size);
		free(ptr);
	}
	else
	{
		memory->size = size;
		ret = ptr;
	}
	return (ret);
}
