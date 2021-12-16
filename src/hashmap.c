#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "util.h"
#include "hashmap.h"

// pre-computed primes at nice intervals
static const int primes[] = {2,5,11,23,47,97,197,397,797,1597,3203,6421,12853,25717,51437,102877,205759,411527,823117,1646237,3292489,6584983,13169977,26339969,52679969,105359939,210719881,421439783,842879579,1685759167};
static int GetNextPrime(int min)
{
	static int i = 0;
	for (; primes[i]; i++)
		if (primes[i] >= min)
			return primes[i];
	return primes[i];
}

static void ft_memcpy(void* dst, void* src, int chars)
{
	char* cdst = dst;
	char* csrc = src;
	for (int i = 0; i < chars; i++)
		cdst[i] = csrc[i];
}

static int hash(char* key)
{
	// Super simple, replace for better one later
	int hash = 17;
	while (key[0])
	{
		hash *= 21;
		hash ^= key[0];
		key++;
	}
	return hash;
}

void HashMap_Resize(HashMap* map, int newSize)
{
	newSize = GetNextPrime(newSize);

	int* newBuckets = malloc(sizeof(*map->buckets) * newSize);
	Entry* newEntries = malloc(sizeof(*map->entries) * newSize);
	if (!newBuckets || !newEntries)
	{
		printf("Error:\nMalloc failure!\n");
		exit(1);
	}

	// Copy entries
	ft_memcpy(newEntries, map->entries, sizeof(*newEntries) * map->hashSize);

	ft_memset(newBuckets, -1, sizeof(int) * newSize);

	// Re-add all the entries to the buckets
	for (int i = 0; i < map->count; i++)
	{
		int Bucket = newEntries[i].hashCode % newSize;

		// Add to front of linked list
		newEntries[i].next = newBuckets[Bucket];
		newBuckets[Bucket] = i;
	}

	free(map->buckets);
	free(map->entries);
	map->buckets = newBuckets;
	map->entries = newEntries;
	map->hashSize = newSize;
}

// Returns true if it inserted successfully
// False if it already existed
bool HashMap_Insert(HashMap* map, char* key, char* value)
{
	int hashCode = hash(key) & 0x7FFFFFFF;
	int targetBucket = hashCode % map->hashSize;

	// Check for duplicates (can be removed if absolutely sure there will be none)
	for (int i = map->buckets[targetBucket]; i >= 0; i = map->entries[i].next)
		if (map->entries[i].hashCode == hashCode && ft_strcmp(map->entries[i].key, key) == 0)
			return false;

	if (map->count == map->hashSize)	// Too little space, resize is needed
	{
		HashMap_Resize(map, map->count * 2);
		targetBucket = hashCode % map->hashSize;	// Also update the target bucket, hashSize changed
	}
	int index = map->count++;

	// Found entry, fill it with data!
	Entry* entry = map->entries + index;
	entry->hashCode = hashCode;
	entry->key = key;
	entry->value = value;

	// Add to start of linked list from the buckets array
	map->entries[index].next = map->buckets[targetBucket];
	map->buckets[targetBucket] = index;

	return true;	// Successfully inserted
}

char* HashMap_Get(HashMap* map, char* key)
{
	int hashCode = hash(key) & 0x7FFFFFFF;
	int targetBucket = hashCode % map->hashSize;

	for (int i = map->buckets[targetBucket]; i >= 0; i = map->entries[i].next)
		if (map->entries[i].hashCode == hashCode && ft_strcmp(map->entries[i].key, key) == 0)
			return map->entries[i].value;
	return NULL;
}

HashMap* HashMap_New()
{
	HashMap* map = malloc(sizeof(HashMap));
	if (!map)
		return NULL;

	map->count = 0;
	map->hashSize = GetNextPrime(32);
	map->buckets = malloc(sizeof(*map->buckets) * map->hashSize);
	map->entries = malloc(sizeof(Entry) * map->hashSize);

	if (!map->buckets || !map->entries)
		exit(1);

	ft_memset(map->buckets, -1, sizeof(int) * map->hashSize);

	return map;
}
