/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 13:44:10 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 13:46:36 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_get_next_line.h"
#include "hashmap.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	search_mode(int fd, HashMap* storage) {
	int		res;
	char	*line = NULL;

	while ((res = get_next_line(fd, &line)) != -1) {
		if (!line[0]) {
			free(line);
			break ;
		}
		char *found = HashMap_Get(storage, line);
		if (!found) {
			printf("%s: Not found.\n", line);
		}
		else {
			printf("%s\n", found);
		}
		free(line);
	}
	if (res == -1) {
		printf("Error: error occured in search mode\n");
		exit(1);
	}
}
