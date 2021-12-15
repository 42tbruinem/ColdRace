/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_with_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:15:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 00:57:07 by jsimonis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coldrace.h"
#include "hashmap.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define KEY true
#define VALUE false

//#define USE_TRIE

#ifdef USE_TRIE
#define Structure Trie
#define CreateFunc trie_new
#define FreeFunc trie_destroy
//#define FreeFunc (void)
#define GetFunc trie_find_str
#else
#define CreateFunc HashMap_New
#define Structure HashMap
#define FreeFunc HashMap_Free
#define GetFunc HashMap_Get
#endif

Structure*	get_storage(int fd) {
	bool	type = KEY;
	char	*key = NULL;
	int		res;
	Structure*	storage = CreateFunc();
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
			#ifdef USE_TRIE
			trie_insert(&storage, key, line);
			free(key);
			#else
			HashMap_Insert(storage, key, line);
			#endif
		}
		type = !type;
	}
	if (type == VALUE) {
		free(key);
	}
	if (res == -1) {
		FreeFunc(storage);
		return NULL;
	}
	return storage;
}

int main_with_fd(int fd) {
	Structure*	storage;
	char*	line = NULL;
	int		res;

	// Storage mode
	storage = get_storage(fd);
	if (storage == NULL) {
		printf("Error: error occured while reading storage\n");
		exit(1);
	}

	while ((res = get_next_line(fd, &line)) != -1) {
		if (!line[0]) {
			free(line);
			break ;
		}
		char *found = GetFunc(storage, line);
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
		FreeFunc(storage);
		exit(1);
	}
	FreeFunc(storage);
	exit(0);
}
