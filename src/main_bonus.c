/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:15:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/14 18:27:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coldrace.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define KEY true
#define VALUE false

Trie*	get_storage(int fd) {
	bool	type = KEY;
	char	*key = NULL;
	int		res;
	Trie*	storage = trie_new();
	char	*line = NULL;

	while ((res = get_next_line(fd, &line)) != -1) {
		// Break if we encounter an empty line, end of storage mode
		if (!ft_strlen(line)) {
			break;
		}
		// Store the line as the 'key'
		if (type == KEY) {
			key = line;
		}
		// Insert the value at 'key'
		else {
			trie_insert(&storage, key, line);
			free(key);
		}
		type = !type;
	}
	if (type == VALUE) {
		free(key);
	}
	if (res == -1) {
		trie_destroy(storage);
		return NULL;
	}
	return storage;
}

int	open_file(char *filename) {
	ssize_t ret = open(filename, O_RDONLY);
	if (ret == -1 || read(ret, NULL, 0) == -1) {
		return -1;
	}
	return ret;
}

int main(int argc, char **argv) {
	Trie*	storage = trie_new();
	char*	line = NULL;
	int		res;
	int		storage_fd = STDIN_FILENO;

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

	// Storage mode
	storage = get_storage(storage_fd);
	if (storage == NULL) {
		printf("Error: error occured while reading storage\n");
		return 1;
	}
	if (storage_fd != STDIN_FILENO) {
		close(storage_fd);
	}

	while ((res = get_next_line(STDIN_FILENO, &line)) != -1) {
		if (!ft_strlen(line)) {
			break ;
		}
		char *found = trie_find_str(storage, line);
		if (!found) {
			printf("%s: Not Found.\n", line);
		}
		else {
			printf("%s\n", found);
		}
	}
	if (res == -1) {
		printf("Error: error occured in search mode\n");
		trie_destroy(storage);
		return 1;
	}
	trie_destroy(storage);
	return 0;
}