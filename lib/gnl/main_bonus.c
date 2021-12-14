/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/09 23:17:24 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/09 23:17:24 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	put_2d(char **lines)
{
	int y;

	y = 0;
	while (lines[y])
	{
		printf("%s\n", lines[y]);
		y++;
	}
}

int		main(int argc, char **input)
{
	char *st;
	int fd;
	int	fd2;

	if (argc < 3)
		return (0);
	fd = open(input[1], O_RDONLY);
	fd2 = open(input[2], O_RDONLY);
	printf("Output: %d | String: %s\n", get_next_line(fd, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd2, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd2, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd2, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd2, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd2, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd2, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd2, &st), st);
	printf("Output: %d | String: %s\n", get_next_line(fd2, &st), st);
	return (0);
}
