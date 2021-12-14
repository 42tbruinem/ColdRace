/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 13:11:34 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/28 17:50:40 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen_n(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int		parse(int result, char **line, char **str)
{
	if (result == 0 || result == 1)
		*line = *str;
	else
		free(*str);
	return (result);
}

void	clean_buffer(char *buffer, int bytes_read, int full)
{
	int i;

	i = 0;
	if (full == 0)
		while (i < bytes_read && buffer[i] != '\n')
		{
			buffer[i] = 0;
			i++;
		}
	else
		while (i < bytes_read)
		{
			buffer[i] = 0;
			i++;
		}
}
