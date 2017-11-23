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

#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <errno.h>
# define TINY 1024
# define SMALL 4096
# define NB_BY_MAP 100

typedef struct		s_memory
{
	size_t			size;
	int				free;
	int				id;
	void			*data;
	struct s_memory	*next;
}					t_memory;

typedef struct		s_index
{
	t_memory		*tiny;
	t_memory		*small;
	t_memory		*large;
}					t_index;

typedef	struct		s_history
{
	size_t			size[4096];
	void			*address[4096];
}					t_history;

typedef struct		s_identifier
{
	size_t			size;
	int				id;
}					t_identifier;

pthread_mutex_t		g_memory_mutex;

t_identifier		ft_check_size(size_t size);
void				initialize();
void				*ft_memory_return(t_identifier identifier, size_t size);
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t count, size_t size);
void				show_alloc_mem();
void				show_history_mem();
size_t				ft_strlen(const char *str);
void				ft_putstr(char const *s);
void				ft_print_memory(void *beginning, void *end, size_t size);
void				ft_putnbr(size_t n);
int					memory_check(void *ptr);
void				*new_malloc(void *size);
void				*new_free(void *ptr);
void				print_addr(void *ptr);
void				mutex_init(pthread_mutex_t *mutex);
void				add_history(t_memory *map);
size_t				malloc_size(const void *ptr);
#endif
