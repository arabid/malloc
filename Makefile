
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SRC =	memory.c\
		identifier.c\
		malloc.c\
		show_alloc_mem.c\
		free.c\
		realloc.c\
		valloc.c\
		reallocf.c\
		calloc.c\
		malloc_size.c\
		print_memory.c\
		ft_strlen.c\
		ft_putstr.c\
		ft_putnbr.c\

PATH_OBJ	= obj
PATH_SRC	= src
PATH_INC	= includes

NAME		= libft_malloc_$(HOSTTYPE).so
CFLAGS		= -Wall -Wextra -Werror
DLFLAGS		= -shared -fPIC
OBJECTS		= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))
CC			= gcc

.PHONY: all

all: $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(DLFLAGS) -o $@ $(OBJECTS)
	@rm -f libft_malloc.so
	@ln -s $(NAME) libft_malloc.so

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	$(CC) -c -o $@ $(CFLAGS) $^ -O0 -g  -I $(PATH_INC)/

clean:
	@rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(PATH_OBJ)
	rm -f libft_malloc.so

re: fclean $(NAME)
