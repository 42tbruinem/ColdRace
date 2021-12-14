/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 15:45:15 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/28 22:52:59 by tbruinem      ########   odam.nl         */
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

void	clean_buffer(char *buffer, int bytes_read, int full)
{
	int i;

	i = 0;
	if (full == 0)
	{
		while (i < bytes_read && buffer[i] != '\n')
		{
			buffer[i] = 0;
			i++;
		}
	}
	else
	{
		while (i < bytes_read)
		{
			buffer[i] = 0;
			i++;
		}
	}
}

char	*ft_realloc(char *str, char *buffer, int bytes_read, int j)
{
	char	*new;
	int		i;

	i = 0;
	if (bytes_read == -1)
		return (NULL);
	if (bytes_read > ft_strlen_n(buffer))
		bytes_read = ft_strlen_n(buffer);
	new = malloc(sizeof(char) * (ft_strlen_n(str) + bytes_read + 1));
	if (str)
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	while (i < (ft_strlen_n(str) + bytes_read))
	{
		new[i] = buffer[j];
		j++;
		i++;
	}
	new[i] = 0;
	free(str);
//	printf("I still work\n");
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

t_store	*item_new(int fd)
{
	t_store *item;

	item = (t_store *)malloc(sizeof(t_store));
	if (!item)
		return (NULL);
	item->fd = fd;
	item->buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!item->buffer)
		return (NULL);
	item->next = NULL;
	clean_buffer(item->buffer, BUFFER_SIZE + 1, 1);
	return (item);
}
