#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
//#include <string.h>	// temp for strcmp & memcpy

#include "hashmap.h"

// pre-computed primes at nice intervals
static const int Primes[] = { 3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293, 353, 431, 521, 631, 761, 919, 1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591, 17519, 21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437,  187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897, 1162687, 1395263, 1674319, 2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369, 0 };

static bool IsPrime(int candidate)
{
	if ((candidate & 1) != 0)
	{
		for (int divisor = 3; divisor * divisor <= candidate; divisor += 2)
			if ((candidate % divisor) == 0)
				return false;
		return true;
	}
	return (candidate == 2);
}

static int GetNextPrime(int Min)
{
	int i;
	for (i = 0; Primes[i]; i++)
		if (Primes[i] >= Min)
			return Primes[i];

	//ugh, too big, compute the hard way
	for (int i = (Min | 1); i < INT_MAX; i+=2)
		if (IsPrime(i))	// might be a bit slow, but ehhh
			return i;
	return Min;
}

// cant use standards, so just do it yourself
static int ft_strcmp(char* a, char* b)
{
	for (; a[0] != b[0] && a[0]; a++)
		b++;
	return a[0] - b[0];
}

static void ft_memcpy(void* dst, void* src, int chars)
{
	char* cdst = dst;
	char* csrc = src;
	for (int i = 0; i < chars; i++)
		cdst[i] = csrc[i];
}

static int Hash(char* Key)
{
	// Super simple, replace for better one later
	int Hash = 17;
	while (Key[0])
	{
		Hash *= 21;
		Hash ^= Key[0];
		Key++;
	}
	return Hash;
}

void HashMap_Resize(HashMap* Map, int NewSize)
{
	NewSize = GetNextPrime(NewSize);

	int* NewBuckets = malloc(sizeof(*Map->Buckets) * NewSize);
	Entry* NewEntries = malloc(sizeof(*Map->Entries) * NewSize);
	if (!NewBuckets || !NewEntries)
	{
		printf("Error:\nMalloc failure!\n");
		exit(1);
	}

	// Copy entries
	ft_memcpy(NewEntries, Map->Entries, sizeof(*NewEntries) * Map->HashSize);

	// Init buckets to -1
	for (int i = 0; i < NewSize; i++)
		NewBuckets[i] = -1;

	// Re-add all the entries to the buckets
	for (int i = 0; i < Map->Count; i++)
	{
		int Bucket = NewEntries[i].HashCode % NewSize;

		// Add to front of linked list
		NewEntries[i].Next = NewBuckets[Bucket];
		NewBuckets[Bucket] = i;
	}

	free(Map->Buckets);
	free(Map->Entries);
	Map->Buckets = NewBuckets;
	Map->Entries = NewEntries;
	Map->HashSize = NewSize;
}

// Returns true if it inserted successfully
// False if it already existed
bool HashMap_Insert(HashMap* Map, char* Key, char* Value)
{
	int HashCode = Hash(Key) & 0x7FFFFFFF;
	int TargetBucket = HashCode % Map->HashSize;

	// Check for duplicates (can be removed if absolutely sure there will be none)
	for (int i = Map->Buckets[TargetBucket]; i >= 0; i = Map->Entries[i].Next)
		if (Map->Entries[i].HashCode == HashCode && ft_strcmp(Map->Entries[i].Key, Key))
			return false;

	// Get next empty entry
	if (Map->Count == Map->HashSize)	// Too little space, resize is needed
	{
		HashMap_Resize(Map, Map->Count * 2);
		TargetBucket = HashCode % Map->HashSize;	// Also update the target bucket, HashSize changed
	}
	int Index = Map->Count++;

	// Found entry, fill it with data!
	Entry* Entry = &Map->Entries[Index];
	Entry->HashCode = HashCode;
	Entry->Key = Key;
	Entry->Value = Value;

	// Add to start of linked list from the buckets array
	Entry->Next = Map->Buckets[TargetBucket];
	Map->Buckets[TargetBucket] = Index;

	return true;	// Successfully inserted
}

char* HashMap_Get(HashMap* Map, char* Key)
{
	int HashCode = Hash(Key) & 0x7FFFFFFF;
	int TargetBucket = HashCode % Map->HashSize;

	for (int i = Map->Buckets[TargetBucket]; i >= 0; i = Map->Entries[i].Next)
		if (Map->Entries[i].HashCode == HashCode && ft_strcmp(Map->Entries[i].Key, Key) == 0)
			return Map->Entries[i].Value;
	return NULL;
}

HashMap* HashMap_New()
{
	HashMap* Map = malloc(sizeof(HashMap));
	if (!Map)
		return NULL;

	Map->Count = 0;
	Map->HashSize = GetNextPrime(32);
	Map->Buckets = malloc(sizeof(*Map->Buckets) * Map->HashSize);
	Map->Entries = malloc(sizeof(Entry) * Map->HashSize);

	if (!Map->Buckets || !Map->Entries)
	{
		free(Map->Buckets);
		free(Map->Entries);
		return NULL;
	}

	for (int i = 0; i < Map->HashSize; i++) Map->Buckets[i] = -1;

	return Map;
}

void HashMap_Free(HashMap* Map)
{
	free(Map->Buckets);

	for (int i = 0; i < Map->Count; i++)
	{
		free(Map->Entries[i].Key);
		free(Map->Entries[i].Value);
	}

	free(Map->Entries);
	free(Map);
}