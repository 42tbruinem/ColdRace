/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:15:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 13:08:57 by jsimonis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coldrace.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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

int main(void) {
	HashMap*	storage;
	char*	line = NULL;
	int		res;

	// Storage mode
	storage = get_storage(STDIN_FILENO);

	while ((res = get_next_line(STDIN_FILENO, &line)) != -1) {
		if (!line[0]) {
			free(line);
			break ;
		}
		char *found = HashMap_Get(storage, line);
		if (!found) {
			printf("%s: Not Found.\n", line);
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
	exit(0);
}
