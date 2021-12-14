/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsimonis <jsimonis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:25:34 by jsimonis      #+#    #+#                 */
/*   Updated: 2021/12/14 16:50:11 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line_int.h"
#include <string.h>

/*
**	Using a linked list with both a next and previous
**	we keep track of what buffer is for what fd
**	Since we also have previous clearing out a single element is easy
*/

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (dst == src)
		return (dst);
	i = 0;
	s = (char *)src;
	d = (char *)dst;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

static t_gnl_ll	**get_gnl_ll(void)
{
	static t_gnl_ll	*list = NULL;

	return (&list);
}

t_fd_data		*get_gnl_data(int fd)
{
	t_gnl_ll	**start;
	t_gnl_ll	*current;

	start = get_gnl_ll();
	current = *start;
	while (current != NULL)
	{
		if (current->fd == fd)
			return (&current->data);
		current = current->next;
	}
	current = malloc(sizeof(t_gnl_ll));
	if (current == NULL)
		return (NULL);
	current->data.buffer = NULL;
	current->fd = fd;
	current->next = *start;
	current->previous = NULL;
	if (*start)
		(*start)->previous = current;
	*start = current;
	return (&current->data);
}

bool			clear_gnl_data(int fd)
{
	t_gnl_ll	**start;
	t_gnl_ll	*current;

	start = get_gnl_ll();
	current = *start;
	while (current != NULL)
	{
		if (current->fd == fd)
		{
			if (current == *start)
				*start = current->next;
			if (current->next)
				current->next->previous = current->previous;
			if (current->previous)
				current->previous->next = current->next;
			free(current->data.buffer);
			free(current);
			return (true);
		}
		current = current->next;
	}
	return (false);
}

/*
**	Can optimize the memcpy to only copy from buff_inx to buff_end
**		instead of from 0 to buff_end
**		but every time increase_buffer_size is called buff_index is zero
*/

bool			increase_buffer_size(t_fd_data *data)
{
	char	*new;
	size_t	size;

	size = data->buff_size * 2;
	new = malloc(size);
	if (new == NULL)
		return (false);
	ft_memcpy(new, data->buffer, data->buff_end);
	free(data->buffer);
	data->buffer = new;
	data->buff_size = size;
	return (true);
}

bool			init_buffer(t_fd_data *fd_data)
{
	fd_data->buffer = malloc(BUFFER_SIZE);
	if (fd_data->buffer == NULL)
		return (false);
	fd_data->buff_inx = 0;
	fd_data->buff_end = 0;
	fd_data->buff_size = BUFFER_SIZE;
	return (true);
}
