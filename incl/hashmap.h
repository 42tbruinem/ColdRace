#ifndef HASHMAP_H
# define HASHMAP_H

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

typedef struct {
	int HashCode;	// -1 if unused, positive otherwise
	int Next;
	char* Key;
	char* Value;
} Entry;

typedef struct
{
	int* Buckets;
	Entry* Entries;
	int HashSize;
	int Count;	// How far the earliest empty Entry is
} HashMap;

bool HashMap_Insert(HashMap* Map, char* Key, char* Value);
char* HashMap_Get(HashMap* Map, char* Key);
HashMap* HashMap_New();
void HashMap_Free(HashMap* Map);

#endif