/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_free_test.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 14:01:46 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/28 14:30:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	write_mem(char **str)
{
	static char 	*buf = NULL;
	int				i;
	static int		start = 1;

	i = 0;
	if (buf == NULL)
		printf("this is null: %s\n", buf);
	buf = malloc(5 + 1);
	printf("this is the string: %s\n", buf);
	if (start)
	{
		while ((*str)[i])
		{
			buf[i] = (*str)[i];
			i++;
		}
		buf[i] = 0;
		start = 0;
	}
	free(buf);
}

int		main(void)
{
	char *str;
	char *lala;

	str = strdup("12345");
	write_mem(&str);
	str = "234345";
	lala = strdup("NEE STEVEN");
	write_mem(&str);
	return (0);
}
