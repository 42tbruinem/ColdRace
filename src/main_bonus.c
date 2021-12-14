/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:15:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 00:36:34 by jsimonis      ########   odam.nl         */
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

int main(int argc, char **argv) {
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

	return main_with_fd(storage_fd);	// Copy and pasting is the root of all evil, ive removed it :)
}
