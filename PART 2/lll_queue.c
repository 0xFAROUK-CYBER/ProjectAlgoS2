#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lll_queue.h"



// Function to count vowels in a string
int countVowels(const char *str) {
    int count = 0;
    while (*str) {
        char c = tolower(*str);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        str++;
    }
    return count;
}

// Helper to create a new node
TList* createNode(const char *word, const char *relatedWord) {
    TList *newNode = malloc(sizeof(TList));
    if (!newNode) {
        perror("Failed to allocate node");
        exit(EXIT_FAILURE);
    }
    newNode->word = strdup(word);
    newNode->relatedWord = strdup(relatedWord);
    newNode->numChars = strlen(word);
    newNode->numVowels = countVowels(word);
    newNode->next = NULL;
    return newNode;
}

// Append node at end of list
void appendNode(TList **head, TList *node) {
    if (*head == NULL) {
        *head = node;
    } else {
        TList *temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

// Read words and synonyms into linked list
TList *getSynWords(FILE *f) {
    char word[100], synonym[100];
    TList *head = NULL;

    while (fscanf(f, "%99s %99s", word, synonym) == 2) {
        TList *node = createNode(word, synonym);
        appendNode(&head, node);
    }

    return head;
}

// Read words and antonyms into linked list
TList *getAntoWords(FILE *f) {
    char word[100], antonym[100];
    TList *head = NULL;

    while (fscanf(f, "%99s %99s", word, antonym) == 2) {
        TList *node = createNode(word, antonym);
        appendNode(&head, node);
    }

    return head;
}



// Assuming TList and countVowels() are defined as before

void getInfWord(TList *syn, TList *ant, char *word) {
    char *foundSyn = NULL;
    char *foundAnt = NULL;

    // Search synonym list
    for (TList *temp = syn; temp != NULL; temp = temp->next) {
        if (strcmp(temp->word, word) == 0) {
            foundSyn = temp->relatedWord;
            break;
        }
    }

    // Search antonym list
    for (TList *temp = ant; temp != NULL; temp = temp->next) {
        if (strcmp(temp->word, word) == 0) {
            foundAnt = temp->relatedWord;
            break;
        }
    }

    int numChars = strlen(word);
    int numVowels = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        char c = tolower(word[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            numVowels++;
        }
    }

   printf("Word: %s\n", word);
	if (foundSyn != NULL) {
    printf("Synonym: %s\n", foundSyn);
} else {
    printf("Synonym: Not found\n");
}
if (foundAnt != NULL) {
    printf("Antonym: %s\n", foundAnt);
} else {
    printf("Antonym: Not found\n");
}
	printf("Number of characters: %d\n", numChars);
	printf("Number of vowels: %d\n", numVowels);
}

void getInfWord2(TList *syn, TList *ant, char *inf) {
    char *foundWord = NULL;
    int numChars = 0, numVowels = 0;

    // Search synonym list for matching relatedWord
    for (TList *temp = syn; temp != NULL; temp = temp->next) {
        if (strcmp(temp->relatedWord, inf) == 0) {
            foundWord = temp->word;
            numChars = temp->numChars;
            numVowels = temp->numVowels;
            break;
        }
    }

    // If not found in synonyms, search antonyms list
    if (!foundWord) {
        for (TList *temp = ant; temp != NULL; temp = temp->next) {
            if (strcmp(temp->relatedWord, inf) == 0) {
                foundWord = temp->word;
                numChars = temp->numChars;
                numVowels = temp->numVowels;
                break;
            }
        }
    }

    if (foundWord) {
        printf("Input: %s\n", inf);
        printf("Word: %s\n", foundWord);
        printf("Number of characters: %d\n", numChars);
        printf("Number of vowels: %d\n", numVowels);
    } else {
        printf("'%s' not found as synonym or antonym.\n", inf);
    }
}

void swapNodesContent(TList *a, TList *b) {
    char *tempWord = a->word;
    char *tempRelated = a->relatedWord;
    int tempNumChars = a->numChars;
    int tempNumVowels = a->numVowels;

    a->word = b->word;
    a->relatedWord = b->relatedWord;
    a->numChars = b->numChars;
    a->numVowels = b->numVowels;

    b->word = tempWord;
    b->relatedWord = tempRelated;
    b->numChars = tempNumChars;
    b->numVowels = tempNumVowels;
}

// 2) sortWord: sort list alphabetically by word
TList *sortWord(TList *head) {
    if (!head) return NULL;

    int swapped;
    TList *ptr1;
    TList *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->word, ptr1->next->word) > 0) {
                swapNodesContent(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return head;
}

// 3) sortWord2: sort list ascending by number of chars
TList *sortWord2(TList *head) {
    if (!head) return NULL;

    int swapped;
    TList *ptr1;
    TList *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->numChars > ptr1->next->numChars) {
                swapNodesContent(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return head;
}

// 4) sortWord3: sort list descending by number of vowels
TList *sortWord3(TList *head) {
    if (!head) return NULL;

    int swapped;
    TList *ptr1;
    TList *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->numVowels < ptr1->next->numVowels) {
                swapNodesContent(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return head;
}

// Helper: delete nodes matching word in list
TList *deleteFromList(TList *head, const char *word) {
    TList *temp = head, *prev = NULL;
    while (temp) {
        if (strcmp(temp->word, word) == 0) {
            TList *toDelete = temp;
            if (!prev) head = temp->next;
            else prev->next = temp->next;
            temp = temp->next;
            free(toDelete->word);
            free(toDelete->relatedWord);
            free(toDelete);
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
    return head;
}

// Delete word line from file by rewriting file except that line
void deleteWordFromFile(const char *filename, const char *word) {
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) {
        if (f) fclose(f);
        if (temp) fclose(temp);
        perror("File open error");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        char lineWord[100];
        sscanf(line, "%99s", lineWord);
        if (strcmp(lineWord, word) != 0) fputs(line, temp);
    }
    fclose(f);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
}

// 5) Delete word from lists and file
TList *deleteWord(const char *filename, TList *syn, TList *ant, char *word) {
    syn = deleteFromList(syn, word);
    ant = deleteFromList(ant, word);
    deleteWordFromFile(filename, word);
    return syn;
}

// Update relatedWord field for a given word in the list
void updateInList(TList *head, const char *word, const char *newRelated) {
    for (TList *temp = head; temp; temp = temp->next) {
        if (strcmp(temp->word, word) == 0) {
            free(temp->relatedWord);
            temp->relatedWord = strdup(newRelated);
            break;
        }
    }
}

// Update the line in file for the given word
void updateWordInFile(const char *filename, const char *word, const char *newSyn, const char *newAnt) {
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) {
        if (f) fclose(f);
        if (temp) fclose(temp);
        perror("File open error");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        char lineWord[100], lineSyn[100], lineAnt[100];
        int count = sscanf(line, "%99s %99s %99s", lineWord, lineSyn, lineAnt);
        if (count >= 1 && strcmp(lineWord, word) == 0) {
            fprintf(temp, "%s %s %s\n", word, newSyn, newAnt);
        } else {
            fputs(line, temp);
        }
    }
    fclose(f);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
}

// 6) Update synonym and antonym in lists and file
TList *updateWord(const char *filename, TList *syn, TList *ant, char *word, char *syne, char *anton) {
    updateInList(syn, word, syne);
    updateInList(ant, word, anton);
    updateWordInFile(filename, word, syne, anton);
    return syn;
}

double similarity(const char *a, const char *b) {
    int lenA = strlen(a), lenB = strlen(b);
    int matches = 0, i = 0, j = 0;
    while (i < lenA && j < lenB) {
        if (tolower(a[i]) == tolower(b[j])) {
            matches++; i++; j++;
        } else {
            j++;
        }
    }
    return (double)matches / lenA;
}

// 7) Return list of words with similarity >= rate
TList *similarWord(TList *syn, char *word, double rate) {
    TList *result = NULL;
    for (TList *temp = syn; temp; temp = temp->next) {
        if (similarity(word, temp->word) >= rate) {
            TList *node = createNode(temp->word, temp->relatedWord);
            appendNode(&result, node);
        }
    }
    return result;
}

int containsSubstring(const char *word, const char *prt) {
    int lenWord = strlen(word), lenPrt = strlen(prt);
    for (int i = 0; i + lenPrt <= lenWord; i++) {
        int match = 1;
        for (int j = 0; j < lenPrt; j++) {
            if (tolower(word[i + j]) != tolower(prt[j])) {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    return 0;
}

// 3) Merge two single linked lists into one bidirectional list
// Combine nodes from syn and ant lists into new list with prev and next pointers
TList *merge(TList *syn, TList *ant) {
    TList *merged = NULL, *tail = NULL;

    while (syn || ant) {
        TList *newNode = NULL;
        if (syn) {
            newNode = createNode(syn->word, syn->relatedWord);
            syn = syn->next;
        }
        else if (ant) {
            newNode = createNode(ant->word, ant->relatedWord);
            ant = ant->next;
        }

        if (!merged) {
            merged = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    return merged;
}





// 4) Merge two lists into one circular doubly linked list
TList *merge2(TList *syn, TList *ant) {
    TList *head = NULL, *tail = NULL;

    while (syn || ant) {
        TList *newNode = NULL;
        if (syn) {
            newNode = createNode(syn->word, syn->relatedWord);
            syn = syn->next;
        }
        else if (ant) {
            newNode = createNode(ant->word, ant->relatedWord);
            ant = ant->next;
        }

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    if (head) {
        tail->next = head; // circular
        head->prev = tail;
    }

    return head;
}


// 5) Add a word with synonym and antonym to lists and append to file
TList *addWord(TList *syn, TList *ant, const char *word, const char *syne, const char *anton, const char *filename) {
    // Create and append nodes to lists
    TList *synNode = createNode(word, syne);
    appendNode(&syn, synNode);
    TList *antNode = createNode(word, anton);
    appendNode(&ant, antNode);

    // Append to file
    FILE *f = fopen(filename, "a");
    if (f) {
        fprintf(f, "%s %s %s\n", word, syne, anton);
        fclose(f);
    } else {
        perror("File open failed");
    }

    return syn; // returning updated syn list (ant list update must be handled externally if needed)
}






// Create empty queue
TQueue* createQueue() {
    TQueue* q = malloc(sizeof(TQueue));
    q->front = q->rear = NULL;
    return q;
}

// Enqueue node to queue
void enqueue(TQueue *q, TList *data) {
    QueueNode *temp = malloc(sizeof(QueueNode));
    temp->data = data;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// Check if queue is empty
int isEmpty(TQueue *q) {
    return q->front == NULL;
}

// Dequeue node from queue
TList* dequeue(TQueue *q) {
    if (isEmpty(q)) return NULL;
    QueueNode *temp = q->front;
    TList *data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return data;
}

// Count syllables: count groups of vowels as syllables
int countSyllables(const char *word) {
    int count = 0;
    int inVowelGroup = 0;
    for (int i = 0; word[i]; i++) {
        char c = tolower(word[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            if (!inVowelGroup) {
                count++;
                inVowelGroup = 1;
            }
        } else {
            inVowelGroup = 0;
        }
    }
    return count;
}

// Syllable function: creates a queue of words sorted by syllable count,
// with empty nodes separating groups
TQueue* syllable(TList *syn) {
    TQueue *queue = createQueue();

    // We'll first find max syllables to know range
    int maxSyllables = 0;
    for (TList *temp = syn; temp; temp = temp->next) {
        int s = countSyllables(temp->word);
        if (s > maxSyllables) maxSyllables = s;
    }

    // For each syllable count, enqueue all words with that count, then enqueue NULL as separator
    for (int s = 1; s <= maxSyllables; s++) {
        int found = 0;
        for (TList *temp = syn; temp; temp = temp->next) {
            if (countSyllables(temp->word) == s) {
                enqueue(queue, temp);
                found = 1;
            }
        }
        if (found) {
            enqueue(queue, NULL); // Separator empty node
        }
    }

    return queue;
}


// Helper to check if string contains a vowel pair (diphthong)
int containsDiphthong(const char *word) {
    const char *diphthongs[] = {"ai", "ei", "oi", "au", "ou", "ei", "ie", "ue"};
    int n = sizeof(diphthongs) / sizeof(diphthongs[0]);
    for (int i = 0; i < n; i++) {
        if (strstr(word, diphthongs[i]) != NULL) return 1;
    }
    return 0;
}

// Helper to check if word contains long vowel (double vowels)
int containsLongVowel(const char *word) {
    for (int i = 0; word[i + 1]; i++) {
        char c1 = tolower(word[i]);
        char c2 = tolower(word[i + 1]);
        if ((c1 == c2) && (c1 == 'a' || c1 == 'e' || c1 == 'i' || c1 == 'o' || c1 == 'u')) {
            return 1;
        }
    }
    return 0;
}


PronunciationQueues prounounciation(TList *syn) {
    PronunciationQueues queues;
    queues.shortQ = createQueue();
    queues.longQ = createQueue();
    queues.diphthongQ = createQueue();

    for (TList *temp = syn; temp; temp = temp->next) {
        if (containsDiphthong(temp->word)) {
            enqueue(queues.diphthongQ, temp);
        } else if (containsLongVowel(temp->word)) {
            enqueue(queues.longQ, temp);
        } else {
            enqueue(queues.shortQ, temp);
        }
    }

    return queues;
}


// from merge to queue 
TQueue* toQueue(TList* merged) {
    TQueue *queue = createQueue();
    for (TList *temp = merged; temp; temp = temp->next) {
        enqueue(queue, temp);
    }
    return queue;
}

