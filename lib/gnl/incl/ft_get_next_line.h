/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_next_line.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsimonis <jsimonis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:25:36 by jsimonis      #+#    #+#                 */
/*   Updated: 2021/12/14 16:14:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

#include <stdbool.h>

typedef enum	e_gnl_out
{
	gnl_success = 1,
	gnl_eof = 0,
	gnl_err = -1
}				t_gnl_out;

t_gnl_out		get_next_line(int fd, char **line);
bool			clear_gnl_data(int fd);

#endif
