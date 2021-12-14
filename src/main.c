/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:15:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/14 14:49:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coldrace.h"
#include <string.h>
#include <stdbool.h>

#define KEY true
#define VALUE false

int main(void) {
	Trie*	storage = trie_new();
	char*	line = NULL;
	bool	type = KEY;
	char	*key = NULL;

	// Storage mode
	do {
		// Break if we encounter an empty line, end of storage mode
		if (!strlen(line)) {
			break;
		}
		// Store the line as the 'key'
		if (type == KEY) {
			free(key);
			key = line;
		}
		// Insert the value at 'key'
		else {
			trie_insert(&storage, key, line);
			free(line);
		}
		type = !type;
	}
	while (get_next_line(STDIN_FILENO, &line) != -1);

	// Search mode

	return 0;
}
