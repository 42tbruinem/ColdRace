/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coldrace.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:16:50 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/14 16:14:36 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_get_next_line.h"
#include "libtrie.h"
Trie		*get_storage(int fd);
#include <unistd.h>
#include <fcntl.h>