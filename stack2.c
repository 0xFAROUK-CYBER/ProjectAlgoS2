#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "stack2.h"

//---------*STACKS PART 2 FUNCTIONS*-----------------



/* ==================== HELPER FUNCTIONS ==================== */


static int countVowels(const char *word) {
    int count = 0;
    // Iterate through each character
    for (int i = 0; word[i]; i++) {
        // Convert to lowercase for case-insensitive comparison
        char ch = tolower(word[i]);
        // Check if vowel
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
    }
    return count;
}


static TStack *copyNode(TStack *node) {
    // Check for NULL input
    if (!node) return NULL;
    
    // Allocate new node
    TStack *newNode = malloc(sizeof(TStack));
    if (!newNode) return NULL;
    
    // Duplicate all string fields
    newNode->word = strdup(node->word);
    newNode->synonym = node->synonym ? strdup(node->synonym) : NULL;
    newNode->antonym = node->antonym ? strdup(node->antonym) : NULL;
    newNode->next = NULL;
    
    return newNode;
}

/* ==================== STACK FUNCTIONS ==================== */

// 1)  FUNCTION CONVERTS LINKED LIST INTO A STACK:
TStack *toStack(TSList *merged) {
    TStack *stack = NULL;
    
    // Process each node in the input list
    while (merged != NULL) {
        // Allocate new stack node
        TStack *newNode = malloc(sizeof(TStack));
        if (!newNode) {
            fprintf(stderr, "Memory allocation failed in toStack()\n");
            return stack; // Return partial stack if allocation fails
        }
        
        // Duplicate string data
        newNode->word = strdup(merged->word);
        newNode->synonym = strdup(merged->synonym);
        newNode->antonym = strdup(merged->antonym);
        
        // Push onto stack (LIFO order)
        newNode->next = stack;
        stack = newNode;
        
        // Move to next list node
        merged = merged->next;
    }
    return stack;
}

// 2) FUNCTION RETURNS INFO ABOUT A WORD :
TWordInfo *getInfWordStack(TStack *stk, const char *word) {
    // Search through stack
    while (stk != NULL) {
        // Check for word match
        if (strcmp(stk->word, word) == 0) {
            // Allocate result struct
            TWordInfo *info = malloc(sizeof(TWordInfo));
            if (!info) return NULL;
            
            // Duplicate word data
            info->word = strdup(stk->word);
            info->synonym = strdup(stk->synonym);
            info->antonym = strdup(stk->antonym);
            
            // Calculate metrics
            info->charCount = strlen(stk->word);
            info->vowelCount = countVowels(stk->word);
            
            return info;
        }
        stk = stk->next;
    }
    return NULL; // Word not found
}


//
void freeWordInfo(TWordInfo *info) {
    if (info) {
        // Free all string fields
        free(info->word);
        free(info->synonym);
        free(info->antonym);
        
        free(info);
    }
}

// 3)FUNCTION TO SORT ALPHABETICALLY A  STACK:

static int compareWords(const void *a, const void *b) {
    // Cast and compare word fields
    TStack *nodeA = *(TStack **)a;
    TStack *nodeB = *(TStack **)b;
    return strcmp(nodeA->word, nodeB->word);
}

TStack *sortWordStack(TStack *syn) {
    // Handle empty or single-node stack
    if (!syn || !syn->next) return syn;
    
    // Count nodes in stack
    int count = 0;
    TStack *temp = syn;
    while (temp) { 
        count++; 
        temp = temp->next; 
    }
    
    // Create array of node pointers
    TStack **nodeArray = malloc(count * sizeof(TStack *));
    if (!nodeArray) return syn;
    
    // Populate array
    temp = syn;
    for (int i = 0; i < count; i++) {
        nodeArray[i] = temp;
        temp = temp->next;
    }
    
    // Sort array using qsort
    qsort(nodeArray, count, sizeof(TStack *), compareWords);
    
    // Rebuild linked list from sorted array
    for (int i = 0; i < count - 1; i++) {
        nodeArray[i]->next = nodeArray[i + 1];
    }
    nodeArray[count - 1]->next = NULL;
    
    // Get new head and free array
    TStack *sortedStack = nodeArray[0];
    free(nodeArray);
    
    return sortedStack;
}

// 4) FUNCTION DELETES A WORD FROM A STACK :
TStack *deleteWordStack(TStack *stk, const char *word) {
    TStack *current = stk, *prev = NULL;
    
    // Search for word in stack
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            // Handle head node deletion
            if (prev == NULL) {
                stk = current->next;
            } 
            // Handle middle/end node deletion
            else {
                prev->next = current->next;
            }
            
            // Free node resources
            free(current->word);
            free(current->synonym);
            free(current->antonym);
            free(current);
            
            return stk;
        }
        prev = current;
        current = current->next;
    }
    return stk; // Word not found
}

// 5) FUNCTION UPDATES A WORD'S SYNONYM AND ANTONYM :
TStack *updateWordStack(TStack *stk, char *word, char *syne, char *anton) {
    // Search for word in stack
    for (TStack *current = stk; current != NULL; current = current->next) {
        if (strcmp(current->word, word) == 0) {
            // Free old strings
            free(current->synonym);
            free(current->antonym);
            
            // Duplicate new strings if provided
            current->synonym = syne ? strdup(syne) : NULL;
            current->antonym = anton ? strdup(anton) : NULL;
            
            break;
        }
    }
    return stk;
}

// 6) FUNCTION CONVERTS STACK OF FUNCTION TOSTACK INTO A QUEUE:
TQueue *stackToQueue(TStack *stk) {
    TQueue *front = NULL, *rear = NULL;
    
    // Sort stack first
    stk = sortWordStack(stk);
    
    // Process each stack node
    while (stk != NULL) {
        // Create new queue node
        TQueue *newNode = malloc(sizeof(TQueue));
        if (!newNode) {
            // Cleanup on allocation failure
            while (front != NULL) {
                TQueue *temp = front;
                front = front->next;
                free(temp->word);
                free(temp->synonym);
                free(temp->antonym);
                free(temp);
            }
            return NULL;
        }
        
        // Duplicate string data
        newNode->word = strdup(stk->word);
        newNode->synonym = stk->synonym ? strdup(stk->synonym) : NULL;
        newNode->antonym = stk->antonym ? strdup(stk->antonym) : NULL;
        newNode->next = NULL;
        
        // Enqueue the node
        if (rear == NULL) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        
        stk = stk->next;
    }
    return front;
}

// 7) FUNCTION ONVERTS STACK OF FUNCTION TOSTACK INTO A DOUBLY LL:

TDList *StacktoList(TStack *stk) {
    TDList *head = NULL, *tail = NULL;
    
    // Sort stack first
    stk = sortWordStack(stk);
    
    // Process each stack node
    while (stk != NULL) {
        // Create new list node
        TDList *newNode = malloc(sizeof(TDList));
        if (!newNode) {
            // Cleanup on allocation failure
            while (head != NULL) {
                TDList *temp = head;
                head = head->next;
                free(temp->word);
                free(temp->synonym);
                free(temp->antonym);
                free(temp);
            }
            return NULL;
        }
        
        // Duplicate string data
        newNode->word = strdup(stk->word);
        newNode->synonym = stk->synonym ? strdup(stk->synonym) : NULL;
        newNode->antonym = stk->antonym ? strdup(stk->antonym) : NULL;
        newNode->prev = tail;
        newNode->next = NULL;
        
        // Add to list
        if (head == NULL) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        
        stk = stk->next;
    }
    return head;
}

// 8)FUNCTION TO ADD WORD WORD AND ITS SYN AND ANT TO SORTED STACK :
TStack *addWordStack(TStack *stk, char *word, char *syne, char *anton) {
    // Create new node
    TStack *newNode = malloc(sizeof(TStack));
    if (!newNode) return stk;
    
    // Duplicate string data
    newNode->word = strdup(word);
    newNode->synonym = syne ? strdup(syne) : NULL;
    newNode->antonym = anton ? strdup(anton) : NULL;
    
    // Handle empty stack or insert at head
    if (!stk || strcmp(word, stk->word) < 0) {
        newNode->next = stk;
        return newNode;
    }
    
    // Find insertion point
    TStack *current = stk;
    while (current->next && strcmp(word, current->next->word) > 0) {
        current = current->next;
    }
    
    // Insert node
    newNode->next = current->next;
    current->next = newNode;
    
    return stk;
}

// 9) FUNCTION TO SORT WORDS BASED ON THERE NUMBER OF SYLLABLES:
int countSyllables(const char *word) {
    int count = 0;
    int inSyllable = 0;

    for (int i = 0; word[i]; i++) {
        char ch = tolower(word[i]);
        if (strchr("aeiouy", ch)) {
            if (!inSyllable) {
                count++;
                inSyllable = 1;
            }
        } else {
            inSyllable = 0;
        }
    }

    return (count > 0) ? count : 1;
}



TStack *syllableStack(TStack *stk) {
    // Handle empty or single-node stack
    if (!stk || !stk->next) return stk;
    
    // Count nodes
    int count = 0;
    TStack *temp = stk;
    while (temp) { count++; temp = temp->next; }
    
    // Create array of node copies
    TStack **nodeArray = malloc(count * sizeof(TStack *));
    if (!nodeArray) return stk;
    
    temp = stk;
    for (int i = 0; i < count; i++) {
        nodeArray[i] = copyNode(temp);
        temp = temp->next;
    }
    
    // Bubble sort by syllable count
    for (int i = 0; i < count-1; i++) {
        for (int j = 0; j < count-i-1; j++) {
            if (countSyllables(nodeArray[j]->word) > countSyllables(nodeArray[j+1]->word)) {
                TStack *temp = nodeArray[j];
                nodeArray[j] = nodeArray[j+1];
                nodeArray[j+1] = temp;
            }
        }
    }
    
    // Rebuild linked list
    for (int i = 0; i < count-1; i++) {
        nodeArray[i]->next = nodeArray[i+1];
    }
    nodeArray[count-1]->next = NULL;
    
    TStack *result = nodeArray[0];
    free(nodeArray);
    return result;
}

// 10) FUNCTION TO SORT WORD BASED ON PROUNOUNCIATION:
static bool containsDiphthong(const char *word) {
    const char *diphthongs[] = {"ai","au","oi","ou","ei","ey","ie","ea","io","oa",NULL};
    for (int i = 0; diphthongs[i]; i++) {
        if (strstr(word, diphthongs[i])) return true;
    }
    return false;
}

static bool hasLongVowel(const char *word) {
    int len = strlen(word);
    // Check for consecutive vowels
    for (int i = 0; i < len-1; i++) {
        if (tolower(word[i]) == tolower(word[i+1]) && 
            strchr("aeiou", tolower(word[i]))) {
            return true;
        }
    }
    // Check for silent 'e' ending
    return (len > 1 && tolower(word[len-1]) == 'e');
}

TPronunciationStacks prounounciationStack(TStack *stk) {
    TPronunciationStacks result = {NULL, NULL, NULL};
    
    // Categorize each word
    while (stk != NULL) {
        TStack *copy = copyNode(stk);
        if (!copy) continue;
        
        if (containsDiphthong(stk->word)) {
            copy->next = result.diphthongs;
            result.diphthongs = copy;
        } 
        else if (hasLongVowel(stk->word)) {
            copy->next = result.longVowels;
            result.longVowels = copy;
        } 
        else {
            copy->next = result.shortVowels;
            result.shortVowels = copy;
        }
        
        stk = stk->next;
    }
    return result;
}

// 11)  FUNCTION TO FIND THE SMALLEST WORD IN STACK :
char *getSmallest(TStack *stk) {
    if (!stk) return NULL;
    
    char *smallest = strdup(stk->word);
    if (!smallest) return NULL;
    
    // Compare with all words
    TStack *current = stk->next;
    while (current != NULL) {
        if (strcmp(current->word, smallest) < 0) {
            free(smallest);
            smallest = strdup(current->word);
            if (!smallest) return NULL;
        }
        current = current->next;
    }
    return smallest;
}

// 12) PROCEDURE THAT PRINTS THE CYCLE WORD WHERE A SYN OR ANT OF WORD LEAD TO ANOTHER :
static bool isVisited(char *word, char **visited, int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(word, visited[i]) == 0) return true;
    }
    return false;
}

void cycleSearch(TStack *stk) {
    // Check each word as starting point
    TStack *current = stk;
    while (current != NULL) {
        char **visited = NULL;
        int visitedCount = 0;
        char *word = current->word;
        bool cycleFound = false;
        
        // Follow synonym/antonym chain
        while (word != NULL) {
            // Check for cycle
            if (isVisited(word, visited, visitedCount)) {
                printf("Cycle found starting at: %s\n", word);
                cycleFound = true;
                break;
            }
            
            // Add to visited list
            char **newVisited = realloc(visited, (visitedCount + 1) * sizeof(char *));
            if (!newVisited) break;
            visited = newVisited;
            visited[visitedCount++] = strdup(word);
            
            // Find next word in chain
            TStack *tmp = stk;
            word = NULL;
            while (tmp != NULL) {
                if (strcmp(tmp->word, visited[visitedCount-1]) == 0) {
                    word = tmp->synonym ? tmp->synonym : tmp->antonym;
                    break;
                }
                tmp = tmp->next;
            }
        }
        
        // Cleanup visited list
        for (int i = 0; i < visitedCount; i++) {
            free(visited[i]);
        }
        free(visited);
        
        if (!cycleFound) {
            printf("No cycle found starting at: %s\n", current->word);
        }
        
        current = current->next;
    }
}

// 13) FUNCTION THAT CHECK IF  A WORD IS PALYNDROME:

bool isPalindromeStack(char *word) {
    int len = strlen(word);
    if (len == 0) return true;
    
    // Create stack of characters
    char *stack = malloc(len);
    if (!stack) return false;
    int top = -1;
    
    // Push all characters
    for (int i = 0; i < len; i++) {
        stack[++top] = word[i];
    }
    
    // Compare with original
    for (int i = 0; i < len; i++) {
        if (word[i] != stack[top--]) {
            free(stack);
            return false;
        }
    }
    
    free(stack);
    return true;
}

// 14)  FUNCTION TO REVERSE STACK USING RECURSION:
static TStack* insertAtBottom(TStack *stk, TStack *node) {
    // Base case: empty stack
    if (!stk) {
        node->next = NULL;
        return node;
    }
    
    // Recursively insert at bottom
    stk->next = insertAtBottom(stk->next, node);
    return stk;
}

TStack* StackRev(TStack *stk) {
    // Base cases: empty or single-node stack
    if (!stk || !stk->next) return stk;
    
    // Remove top node
    TStack *top = stk;
    stk = stk->next;
    top->next = NULL;
    
    // Reverse remaining stack
    stk = StackRev(stk);
    
    // Insert original top at bottom
    return insertAtBottom(stk, top);
}

/* ==================== CLEANUP FUNCTIONS ==================== */

void freeStack(TStack *stk) {
    while (stk != NULL) {
        TStack *temp = stk;
        stk = stk->next;
        free(temp->word);
        free(temp->synonym);
        free(temp->antonym);
        free(temp);
    }
}

void freeQueue(TQueue *q) {
    while (q != NULL) {
        TQueue *temp = q;
        q = q->next;
        free(temp->word);
        free(temp->synonym);
        free(temp->antonym);
        free(temp);
    }
}

void freeList(TDList *list) {
    while (list != NULL) {
        TDList *temp = list;
        list = list->next;
        free(temp->word);
        free(temp->synonym);
        free(temp->antonym);
        free(temp);
    }
}

// Function to safely read a string from user input
void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
            buffer[len-1] = '\0';
    }
}

// Dynamically create a stack from user input
TStack *inputStackFromUser() {
    int n;
    char word[100], syn[100], ant[100];
    TStack *stack = NULL;

    printf("Enter number of words: ");
    scanf("%d", &n);
    getchar(); // clear newline from buffer

    for (int i = 0; i < n; i++) {
        printf("Word %d:\n", i + 1);

        printf(" - Enter word: ");
        readLine(word, sizeof(word));

        printf(" - Enter synonym: ");
        readLine(syn, sizeof(syn));

        printf(" - Enter antonym: ");
        readLine(ant, sizeof(ant));

        stack = addWordStack(stack, word, syn, ant);
    }

    return stack;
}