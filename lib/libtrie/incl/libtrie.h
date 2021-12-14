/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libtrie.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/21 22:41:53 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/12/14 22:33:40 by tbruinem      ########   odam.nl         */
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
	void*				value;
};

Trie		*trie_new(void);
void		*trie_insert(Trie **root, char *key, void *val);
void		*trie_find_str(Trie *iter, char *keycode);
void		*trie_find_readchar(Trie *iter, ssize_t fd, int *ret);
void		trie_destroy(Trie *trie);
void		*ft_memset(void *b, int c, size_t len);

void*	get_memory(size_t type_size);

#endif
