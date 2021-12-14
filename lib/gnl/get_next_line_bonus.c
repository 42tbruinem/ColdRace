/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/09 22:38:51 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/28 22:55:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		is_newline(char *buffer, char **line, int bytes_read)
{
	int i;

	i = 0;
	while (buffer[i] && i < bytes_read)
	{
		if (buffer[i] == '\n')
		{
			*line = ft_realloc(*line, buffer, bytes_read, 0);
			if (line == NULL)
				return (-1);
			move_buffer(buffer, bytes_read);
			return (1);
		}
		i++;
	}
	return (0);
}

t_store	*get_store(t_store **fd_store, int fd)
{
	t_store *list;
	t_store *last;

	list = *fd_store;
	last = *fd_store;
	if (!list)
	{
		*fd_store = item_new(fd);
		return (*fd_store);
	}
	while (list)
	{
		last = list;
		if (list->fd == fd)
		{
//			list->buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
			return (list);
		}
		list = list->next;
	}
	last->next = item_new(fd);
	return (last->next);
}

void	ft_lstclear(t_store **lst, void (*del)(char *, int, int))
{
	t_store	*last;
	t_store	**begin;

	if (lst == NULL || *lst == NULL)
		return ;
	begin = lst;
	while (*lst)
	{
		last = *lst;
		*lst = (*lst)->next;
		del(last->buffer, BUFFER_SIZE, 1);
		free(last->buffer);
		free(last);
		last = NULL;
	}
	*begin = NULL;
}

int		memory_leak_prevention_squad(char **line, t_store **store,
		t_store *current, int result)
{
	t_store *temp;

	temp = *store;
	if (result == -1)
	{
		ft_lstclear(store, &clean_buffer);
		*line = NULL;
		*store = NULL;
		return (result);
	}
	if (result == 0)
	{
		while (temp && temp != current)
		{
			*store = temp;
			temp = temp->next;
		}
		(*store)->next = current->next;
		clean_buffer(current->buffer, BUFFER_SIZE, 1);
		free(current->buffer);
		free(current);
	}
	return (result);
}

int		get_next_line(int fd, char **line)
{
	static t_store		*fd_store = NULL;
	t_store				*current;
	int					bytes_read;
	int					result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	bytes_read = BUFFER_SIZE;
	current = get_store(&fd_store, fd);
	*line = NULL;
	while (bytes_read > 0)
	{
//		printf("string: %s\n", *line);
//		printf("buffer: %s\n", current->buffer);
		result = is_newline(current->buffer, line, bytes_read);
		if (result != 0)
			break ;
//		printf("I AM BROKEN\n");
		*line = ft_realloc(*line, current->buffer, bytes_read, 0);
		bytes_read = read(fd, current->buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1 || bytes_read == 0)
		*line = ft_realloc(*line, current->buffer, bytes_read, 0);
	else
		bytes_read = result;
	return (memory_leak_prevention_squad(line, &fd_store, current, bytes_read));
}
