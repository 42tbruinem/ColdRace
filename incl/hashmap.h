#ifndef HASHMAP_H
# define HASHMAP_H

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

typedef struct {
	int hashCode;	// -1 if unused, positive otherwise
	int next;
	char* key;
	char* value;
} Entry;

typedef struct
{
	int* buckets;
	Entry* entries;
	int hashSize;
	int count;	// How far the earliest empty Entry is
} HashMap;

bool HashMap_Insert(HashMap* map, char* key, char* value);
char* HashMap_Get(HashMap* map, char* key);
HashMap* HashMap_New();
void HashMap_Free(HashMap* map);
void					*ft_memset(void *b, int c, size_t len);

#endif