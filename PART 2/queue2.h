#ifndef QUEUE2_H
#define QUEUE2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node and List definitions
typedef struct Node {
    char *word;
    char *relatedWord; // synonym or antonym
    int numChars;
    int numVowels;
    struct Node *next;
    struct Node *prev; // for doubly linked lists, optional
} Node;

typedef Node TList;

// Queue definitions
typedef struct QueueNode {
    TList *data;
    struct QueueNode *next;
} QueueNode;

typedef struct TQueue {
    QueueNode *front;
    QueueNode *rear;
} TQueue;
typedef struct PronunciationQueues {
    TQueue *shortQ;
    TQueue *longQ;
    TQueue *diphthongQ;
} PronunciationQueues;

// Linked list functions
int countVowels(const char *str);
TList* createNode(const char *word, const char *relatedWord);
void appendNode(TList **head, TList *node);
TList *getSynWords(FILE *f);
TList *getAntoWords(FILE *f);
void getInfWord(TList *syn, TList *ant, char *word);
void getInfWord2(TList *syn, TList *ant, char *inf);
TList *sortWord(TList *head);
TList *sortWord2(TList *head);
TList *sortWord3(TList *head);
void swapNodesContent(TList *a, TList *b);
TList *deleteFromList(TList *head, const char *word);
void deleteWordFromFile(const char *filename, const char *word);
TList *deleteWord(const char *filename, TList *syn, TList *ant, char *word);
void updateInList(TList *head, const char *word, const char *newRelated);
void updateWordInFile(const char *filename, const char *word, const char *newSyn, const char *newAnt);
TList *updateWord(const char *filename, TList *syn, TList *ant, char *word, char *syne, char *anton);
double similarity(const char *a, const char *b);
TList *similarWord(TList *syn, char *word, double rate);
int containsSubstring(const char *word, const char *prt);
TList *merge(TList *syn, TList *ant);
TList *merge2(TList *syn, TList *ant);
TList *addWord(TList *syn, TList *ant, const char *word, const char *syne, const char *anton, const char *filename);

// Queue functions
TQueue* createQueue();
void enqueue(TQueue *q, TList *data);
int isEmpty(TQueue *q);
TList* dequeue(TQueue *q);

// Syllable and pronunciation functions
int countSyllables(const char *word);
TQueue* syllable(TList *syn);
int containsDiphthong(const char *word);
int containsLongVowel(const char *word);
PronunciationQueues prounounciation(TList *syn);
TQueue* toQueue(TList* merged);

#endif 

