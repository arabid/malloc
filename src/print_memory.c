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

void			reverse_mem(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = (ft_strlen(str) - 1);
	while (j > i)
	{
		c = str[j];
		str[j] = str[i];
		str[i] = c;
		i++;
		j--;
	}
}

void			number_assign_hexa_ll(char *str, size_t n)
{
	char	c;
	int		i;

	i = 0;
	while ((n / 16) >= 1)
	{
		c = '0';
		if ((n % 16) >= 10 && 16 > 10)
			c = 'a' - 10;
		str[i] = ((n % 16) + c);
		n = (n / 16);
		i++;
	}
	c = '0';
	if (n >= 10 && 16 > 10)
		c = 'a' - 10;
	str[i] = (n + c);
	str[++i] = '\0';
	reverse_mem(str);
}

void			print_addr(void *ptr)
{
	char	buff[32];

	number_assign_hexa_ll(buff, (size_t)ptr);
	ft_putstr("0x");
	ft_putstr(buff);
}

void			ft_print_memory(t_memory *memory)
{
	print_addr((void *)memory + sizeof(t_memory));
	ft_putstr(" - ");
	print_addr((void *)memory + sizeof(t_memory) + memory->size);
	ft_putstr(" : ");
	ft_putnbr(memory->size);
	ft_putstr(" octets\n");
}
