#ifndef __DICT_H__
#define __DICT_H__

void SpellChecker(char *file_name);
static int CompareWords(const void *key1, const void *key2);
static size_t HashFuncDict(void *key);
static char *strdup(const char *src);

#endif /* __DICT_H__ */
