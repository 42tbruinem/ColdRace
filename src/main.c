/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:15:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/14 18:12:48 by tbruinem      ########   odam.nl         */
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

int main(void) {
	Trie*	storage = trie_new();
	char*	line = NULL;
	int		res;

	// Storage mode
	storage = get_storage(STDIN_FILENO);
	if (storage == NULL) {
		printf("Error: error occured while reading storage\n");
		return 1;
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
