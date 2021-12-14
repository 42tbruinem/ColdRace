/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putmem.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 14:03:24 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/27 14:03:24 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	put_mem(char *str, size_t len)
{
	size_t	i;

	i = 0;
	write(1, "MEM:", 4);
	while (i < len)
	{
		if (str[i] == 0)
			write(1, "0", 1);
		else
			write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}
