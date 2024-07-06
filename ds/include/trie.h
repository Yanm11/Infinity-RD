
#ifndef __TRIE_H__
#define __TRIE_H__

typedef struct trie trie_t;
typedef unsigned int bitarr_t;

typedef enum trie_status
{
  TRIE_SUCCESS,	
  TRIE_MEMORY_FALIURE,
  TRIE_FULL,
  TRIE_DOUBLE_FREE
} trie_status_e;

/*
TrieCreate
Descripion: Create the trie data structer.
input: nothing
Return value: a pointer to the structer
time complexity: O(1)
space complexity: O(1) 
*/
trie_t *TrieCreate(size_t hight);

/*
TrieDestroy
Descripion: destroy the trie data structer.
input: trie pointer
Return value: nothing
time complexity: O(n)
space complexity: O(1) 
*/
void TrieDestroy(trie_t *trie);

/*
TrieCount
Descripion: check the number of nodes in the trie
input: trie pointer
Return value: size_t number of nodes
time complexity: O(n)
space complexity: O(1) 
*/
size_t TrieCount(const trie_t *trie);
/*
TrieInsert
Descripion: insert a new sequance of number or return the next big one
input: trie pointer, address and new address to put the new address to
Return value: status
time complexity: O(log n)
space complexity: O(1) 
*/
trie_status_e TrieInsert(trie_t *trie, bitarr_t address, bitarr_t *out_param);

/*
TrieRemove
Descripion: remove a specific sequance of numbers from the trie if already free return double free
input: trie pointer and a sequance of numbers
Return value: status 
time complexity: O(log n)
space complexity: O(1) 
*/
trie_status_e TrieRemove(trie_t *trie, bitarr_t address);



#endif /*__TRIE_H__*/
