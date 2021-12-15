/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strcmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 01:47:30 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 01:59:24 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	return (ft_memcmp(s1, s2, ft_min(ft_strlen(s1), ft_strlen(s2)) + 1));
}
