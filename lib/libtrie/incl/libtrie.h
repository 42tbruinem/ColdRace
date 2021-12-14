/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libtrie.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/21 22:41:53 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/06/21 23:13:33 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTRIE_H
# define LIBTRIE_H

#include <stdbool.h>
#include <sys/types.h>

# define TRIE_CONNECTION_AMOUNT 128

typedef struct Trie Trie;
struct			Trie
{
	Trie*				connections[TRIE_CONNECTION_AMOUNT];
	bool				end;
	void*				value;
};

Trie	*trie_new(void);
void	*trie_insert(Trie **root, char *key, void *val);
void	*trie_find_str(Trie *iter, char *keycode);
void	*trie_find_readchar(Trie *iter, ssize_t fd, int *ret);
void	trie_destroy(Trie *trie);

#endif
