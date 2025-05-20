#ifndef BINARY_SEARCH_TREES2_H
#define BINARY_SEARCH_TREES2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// -------------------- Structures --------------------

typedef struct WordData {
    char word[50];
    char synonym[50];
    char antonym[50];
    int charCount;
    int vowelCount;
} WordData;

typedef struct TreeNode {
    WordData data;
    struct TreeNode *left, *right;
} TTree;

typedef struct StackNode {
    WordData data;
    struct StackNode *next;
} TStack;

// -------------------- Function Prototypes --------------------

TTree* toTree(TStack *stk);
TTree* fillTree(FILE *f);
TTree* getInfWordTree(TTree *tr, char *word);
TTree* AddWordBST(TTree *tr, char *word, char *syne, char *anton);
TTree* deleteWordBST(TTree *tr, char *word);
TTree* UpdateWordBST(TTree *tr, char *word, char *syne, char *anton);
void TraversalBSTinOrder(TTree *tr);
void TraversalBSTpreOrder(TTree *tr);
void TraversalBSTpostOrder(TTree *tr);
void HighSizeBST(TTree *tr);
TTree *LowestCommonAncestor(TTree *tr, char *word1, char *word2);
int CountNodesRanges(TTree *tr, int l, int h);
TTree *inOrderSuccessor(TTree *tr, char *word);
TTree *BSTMirror(TTree *tr);
bool isBalancedBST(TTree *tr);
TTree *BTSMerge(TTree *tr1, TTree *tr2);
// Utilities
TTree* insertTree(TTree *root, WordData data);
int countVowels(const char *word);
TStack* popStack(TStack **stk);
int compareWords(const char *a, const char *b);

#endif

