#ifndef MALLOC_H
# define MALLOC_H
# include "../libft/libft.h"
# include <sys/mman.h>
# define TINY 1024 
# define SMALL 4096
# define NB_BY_MAP 100

typedef struct		s_memory
{
	size_t			size;
	int				free;
	int 			id;
	struct s_memory	*next;
}					t_memory;

typedef struct		s_index
{
	t_memory		*tiny;
	t_memory		*small;
	t_memory		*large;
}					t_index;

typedef struct		s_identifier
{
	size_t			size;
	int				id;
}					t_identifier;


t_identifier 	ft_check_size(size_t size);
void 			*ft_memory_return(t_identifier identifier, size_t size);
void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void 			show_alloc_mem();

#endif