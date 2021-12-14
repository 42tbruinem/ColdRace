/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trie.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 17:19:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/06/21 23:28:36 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libtrie.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

Trie	*trie_new(void)
{
	Trie	*trie;

	trie = malloc(sizeof(Trie));
	if (!trie)
		return (NULL);
	memset(trie->connections, 0, TRIE_CONNECTION_AMOUNT * sizeof(Trie*));
	trie->end = false;
	trie->value = NULL;
	return (trie);
}

static bool	end_found(Trie* trie, unsigned char key)
{
	return (trie && key == '\0');
}

static Trie*	add_value_to_key(Trie* trie, void *val)
{
	if (trie->end)
		free(trie->value);
	trie->value = val;
	trie->end = true;
	return (trie);
}

void	*trie_insert(Trie **root, char *key, void *val)
{
	size_t			i = 0;
	Trie*			iter;
	unsigned char*	unsigned_key;

	if (*root == NULL && (*root = trie_new()) == NULL)
		return (NULL);
	iter = *root;
	unsigned_key = (unsigned char*)key;
	while (iter && unsigned_key[i])
	{
		Trie**	child = &iter->connections[(int)unsigned_key[i]];
		if (unsigned_key[i] > TRIE_CONNECTION_AMOUNT - 1)
			return (NULL);
		if (*child == NULL && (*child = trie_new()) == NULL)
			return (NULL);
		iter = *child;
		i++;
	}
	if (end_found(iter, unsigned_key[i]))
		add_value_to_key(iter, val);
	return (NULL);
}

void	*trie_find_str(Trie *iter, char *keycode)
{
	size_t	i = 0;
	unsigned char *key;

	key = (unsigned char*)keycode;
	while (iter && key[i])
	{
		Trie**	child = &iter->connections[(int)key[i]];
		if (*child == NULL)
			break ;
		iter = *child;
		i++;
	}
	if (end_found(iter, key[i]) && iter->end)
		return (iter->value);
	return (NULL);
}

void	*trie_find_readchar(Trie *iter, ssize_t fd, int *ret)
{
	char	c;
	int		read_bytes;

	if (!ret)
		ret = &read_bytes;
	while (iter && !iter->end)
	{
		*ret = read(fd, &c, 1);
		if (*ret == -1)
			return (NULL);
		if (!*ret)
			break ;
		iter = iter->connections[(int)c];
	}
	if (iter)
		return (iter->value);
	return (NULL);
}

void	trie_destroy(Trie *trie)
{
	size_t	i = 0;

	if (trie && trie->end)
		free(trie->value);
	while (trie && i < TRIE_CONNECTION_AMOUNT)
	{
		if (trie->connections[i])
			trie_destroy(trie->connections[i]);
		i++;
	}
	free(trie);
}
