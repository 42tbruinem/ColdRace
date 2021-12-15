/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 14:15:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/15 13:43:59 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coldrace.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void) {
	HashMap*	storage;

	storage = get_storage(STDIN_FILENO);
	search_mode(STDIN_FILENO, storage);
	exit(0);
}
