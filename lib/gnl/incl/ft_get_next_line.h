/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_next_line.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsimonis <jsimonis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:25:36 by jsimonis      #+#    #+#                 */
/*   Updated: 2021/01/31 16:27:31 by jsimonis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

typedef enum	e_gnl_out
{
	gnl_success = 1,
	gnl_eof = 0,
	gnl_err = -1
}				t_gnl_out;

t_gnl_out		get_next_line(int fd, char **line);
bool			clear_gnl_data(int fd);

#endif
