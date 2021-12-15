/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   storage.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 13:43:17 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 13:46:26 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"
#include <stdio.h>
#include "hashmap.h"
#include <stdlib.h>
#define KEY true
#define VALUE false

HashMap*	get_storage(int fd) {
	bool	type = KEY;
	char	*key = NULL;
	int		res;
	HashMap*	storage = HashMap_New();
	char	*line = NULL;

	while ((res = get_next_line(fd, &line)) != -1) {
		// Break if we encounter an empty line, end of storage mode
		if (!line[0]) {
			free(line);
			break;
		}
		// Store the line as the 'key'
		if (type == KEY) {
			key = line;
		}
		// Insert the value at 'key'
		else {
			if (!HashMap_Insert(storage, key, line))
			{
				//printf("duplicate key: %s\n", key);
				free(key);
				free(line);
			}
		}
		type = !type;
	}
	if (type == VALUE) {
		free(key);
	}
	if (res == -1) {
		printf("Error: error occured while reading storage\n");
		exit(1);
	}
	return storage;
}
