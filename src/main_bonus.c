/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:15:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 02:03:51 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coldrace.h"
#include <stdio.h>
#include <stdlib.h>

int	open_file(char *filename) {
	ssize_t ret = open(filename, O_RDONLY);
	if (ret == -1 || read(ret, NULL, 0) == -1) {
		return -1;
	}
	return ret;
}

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
			HashMap_Insert(storage, key, line);
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

int main(int argc, char **argv) {
	int		storage_fd = STDIN_FILENO;
	HashMap*	storage;
	char*	line = NULL;
	int		res;

	if (argc == 2) {
		storage_fd = open_file(argv[1]);
		if (storage_fd == -1) {
			printf("Error, cant open requested file for reading.\n");
			return 1;
		}
	}
	else if (argc != 1 && argc != 2) {
		printf("Error, too many arguments to program!\n");
		return 1;
	}
	storage = get_storage(storage_fd);

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
