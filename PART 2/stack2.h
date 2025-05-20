#ifndef STACK2_H
#define STACK2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Singly linked list node (source list)
typedef struct TSList {
    char *word;
    char *synonym;
    char *antonym;
    struct TSList *next;
} TSList;

// Stack node
typedef struct TStack {
    char *word;
    char *synonym;
    char *antonym;
    struct TStack *next;
} TStack;

// Struct to return word information
typedef struct {
    char *word;
    char *synonym;
    char *antonym;
    int charCount;
    int vowelCount;
} TWordInfo;

// Queue node
typedef struct TQueue {
    char *word;
    char *synonym;
    char *antonym;
    struct TQueue *next;
} TQueue;

// Doubly linked list node
typedef struct TDList {
    char *word;
    char *synonym;
    char *antonym;
    struct TDList *prev;
    struct TDList *next;
} TDList;

// Struct to hold 3 stacks for pronunciation categories
typedef struct {
    TStack *shortVowels;
    TStack *longVowels;
    TStack *diphthongs;
} TPronunciationStacks;

/* ---------- Function Prototypes ---------- */
TStack *toStack(TSList *merged);
TWordInfo *getInfWordStack(TStack *stk, const char *word);
void freeWordInfo(TWordInfo *info);
TStack *sortWordStack(TStack *syn);
TStack *deleteWordStack(TStack *stk, const char *word);
TStack *updateWordStack(TStack *stk, char *word, char *syne, char *anton);
TQueue *stackToQueue(TStack *stk);
TDList *StacktoList(TStack *stk);
TStack *addWordStack(TStack *stk, char *word, char *syne, char *anton);
TStack *syllableStack(TStack *stk);
TPronunciationStacks prounounciationStack(TStack *stk);
char *getSmallest(TStack *stk);
void cycleSearch(TStack *stk);
bool isPalindromeStack(char *word);
TStack *StackRev(TStack *stk);
void freeStack(TStack *stk);
void freeQueue(TQueue *q);
void freeList(TDList *list);
int countSyllables(const char *word);
TStack *inputStackFromUser();


#endif