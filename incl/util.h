/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 01:48:21 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 01:56:47 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(const char *str);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int	ft_min(int x, int y);