/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coldrace.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:16:50 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/16 15:40:57 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_get_next_line.h"
#include "hashmap.h"
#include <unistd.h>
#include <fcntl.h>

int main_with_fd(int fd);
size_t	ft_strlen(const char *str);
HashMap*	get_storage(int fd);
void	search_mode(int fd, HashMap* storage);