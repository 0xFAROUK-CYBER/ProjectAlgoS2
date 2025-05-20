#ifndef RECURSION_H
#define RECURSION_H

#include <stdbool.h>

typedef struct Node {
    char *word;
    struct Node *next;
} File;

int countWordOccurence(File *f, char *word);
File *removeWordOccurence(File *f, char *word);
File *replaceWordOccurence(File *f, char *word, char *rep);
void wordPermutation(char *word);
void subseqWord(char *word);
int longestSubseqWord(char *word1, char *word2);
int distinctSubseqWord(char *word);
bool isPalindromWord(char *word);

#endif

