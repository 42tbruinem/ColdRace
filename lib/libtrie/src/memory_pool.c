/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_pool.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 22:17:37 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/14 22:54:27 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

#define POOL_SIZE 10000000

void*	get_memory(size_t type_size) {
	static void*	current_pool = NULL;
	static size_t	index = 0;

	if (!current_pool || index + type_size >= POOL_SIZE) {
		current_pool = malloc(POOL_SIZE);
		index = 0;
	}
	void*	memory = current_pool + index;
	index += type_size;
	return memory;
}
