/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/09 23:16:26 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/14 15:04:49 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

typedef struct		s_store
{
	int				fd;
	char			*buffer;
	struct s_store	*next;
} t_store;

int			get_next_line(int fd, char **line);

int		get_next_line(int fd, char **line);
void	put_mem(char *str, size_t len);
int		ft_strlen_n(char *str);
void	clean_buffer(char *buffer, int bytes_read, int full);
void	move_buffer(char *buffer, int bytes_read);
char	*ft_realloc(char *str, char *buffer, int bytes_read);
char	*ft_strjoin(char *str, char *buffer, int bytes_read);
int		is_newline(char *buffer, char **line, int bytes_read);

#endif
