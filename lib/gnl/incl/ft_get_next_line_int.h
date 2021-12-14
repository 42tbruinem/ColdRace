/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_next_line_int.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsimonis <jsimonis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:25:36 by jsimonis      #+#    #+#                 */
/*   Updated: 2021/01/31 16:27:48 by jsimonis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_INT_H
# define FT_GET_NEXT_LINE_INT_H

# ifndef BUFFER_SIZE
#  warning no BUFFER_SIZE specified, defaulting to 32
#  define BUFFER_SIZE 32
# elif BUFFER_SIZE <= 0
#  warning BUFFER_SIZE <= 0, defaulting to 32
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef	struct	s_fd_data
{
	char	*buffer;
	size_t	buff_inx;
	size_t	buff_end;
	size_t	buff_size;
}				t_fd_data;

typedef	struct	s_gnl_ll
{
	int				fd;
	t_fd_data		data;
	struct s_gnl_ll	*next;
	struct s_gnl_ll	*previous;
}				t_gnl_ll;

bool			clear_gnl_data(int fd);
t_fd_data		*get_gnl_data(int fd);
bool			increase_buffer_size(t_fd_data *data);
bool			init_buffer(t_fd_data *data);

#endif
