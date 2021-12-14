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
	char **lines;
	int size;
	int i;
	int fd;
	int result;

	i = 0;
	size = 11;
	if (argc < 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	lines = malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		result = get_next_line(fd, &lines[i]);
		printf("Output: %d\n", result);
		printf("final string: %s\n", lines[i]);
		i++;
		if (result == 0)
			break ;
	}
	lines[i] = 0;
	while (i >= 0)
	{
		free(lines[i]);
		i--;
	}
	free(lines);
/* 	result = get_next_line(42, &lines[i]);
	printf("%d\n", result);
	printf("%s\n", *lines);
	result = get_next_line(44, &lines[i]);
	printf("%d\n", result);
	printf("%s\n", *lines);
	printf("\n\n\n\n"); */
//	put_2d(lines);
	return (0);
}
