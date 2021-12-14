/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 11:12:48 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/14 15:03:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *str, char *buffer, int bytes_read)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen_n(str) + bytes_read + 1));
	if (!new)
		return (NULL);
	if (str)
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	while (i < (ft_strlen_n(str) + bytes_read))
	{
		new[i] = *buffer;
		buffer++;
		i++;
	}
	new[i] = 0;
	return (new);
}

char	*ft_realloc(char *str, char *buffer, int bytes_read)
{
	char	*new;

	if (bytes_read == -1)
	{
		free(str);
		return (NULL);
	}
	if (bytes_read > ft_strlen_n(buffer))
		bytes_read = ft_strlen_n(buffer);
	new = ft_strjoin(str, buffer, bytes_read);
	free(str);
	clean_buffer(buffer, bytes_read, 0);
	return (new);
}

void	move_buffer(char *buffer, int bytes_read)
{
	int start;
	int i;

	i = 0;
	start = 0;
	while (start < bytes_read && buffer[start] != '\n')
		start++;
	if (buffer[start] == '\n')
		start++;
	while (i < (bytes_read - start))
	{
		buffer[i] = buffer[start + i];
		i++;
	}
	while (i < bytes_read)
	{
		buffer[i] = 0;
		i++;
	}
}

int		is_newline(char *buffer, char **line, int bytes_read)
{
	int i;

	i = 0;
	while (buffer[i] && i < bytes_read)
	{
		if (buffer[i] == '\n')
		{
			*line = ft_realloc(*line, buffer, bytes_read);
			if (line == NULL)
				return (-1);
			move_buffer(buffer, bytes_read);
			return (1);
		}
		i++;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		buffer[BUFFER_SIZE + 1];
	int				bytes_read;
	int				result;

	bytes_read = BUFFER_SIZE;
	*line = NULL;
	while (bytes_read > 0)
	{
		result = is_newline(buffer, line, bytes_read);
		if (result != 0)
			return (result);
		*line = ft_realloc(*line, buffer, bytes_read);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	*line = ft_realloc(*line, buffer, bytes_read);
	return (bytes_read);
}
