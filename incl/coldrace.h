/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coldrace.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:16:50 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 00:35:36 by jsimonis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_get_next_line.h"
#include "libtrie.h"
#include <unistd.h>
#include <fcntl.h>

int main_with_fd(int fd);
size_t	ft_strlen(const char *str);