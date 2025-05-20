// queue2test.c
#include "queueLLL2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void displayMenu() {
    printf("\n\n=== Word Queue Operations ===\n");
    printf("1. Load words from file\n");
    printf("2. Get word information\n");
    printf("3. Sort words alphabetically\n");
    printf("4. Sort words by length\n");
    printf("5. Sort words by vowel count\n");
    printf("6. Delete a word\n");
    printf("7. Update word information\n");
    printf("8. Find similar words\n");
    printf("9. Merge synonym and antonym lists\n");
    printf("10. Add new word\n");
    printf("11. Create syllable queue\n");
    printf("12. Create pronunciation queues\n");
    printf("13. Display current lists\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void displayList(TList* head) {
    printf("\nCurrent List:\n");
    while (head) {
        printf("%s (syn: %s, chars: %d, vowels: %d)\n", 
               head->word, head->relatedWord, head->numChars, head->numVowels);
        head = head->next;
    }
}

void displayQueue(TQueue* q) {
    printf("\nQueue Contents:\n");
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    
    TQueue* tempQ = createQueue();
    while (!isEmpty(q)) {
        TList* data = dequeue(q);
        printf("%s (syn: %s, chars: %d, vowels: %d)\n",
               data->word, data->relatedWord, data->numChars, data->numVowels);
        enqueue(tempQ, data);
    }
    
    // Restore original queue
    while (!isEmpty(tempQ)) {
        enqueue(q, dequeue(tempQ));
    }
    free(tempQ);
}

void displayPronunciationQueues(PronunciationQueues pq) {
    printf("\nShort Vowel Queue:");
    displayQueue(pq.shortQ);
    printf("\nLong Vowel Queue:");
    displayQueue(pq.longQ);
    printf("\nDiphthong Queue:");
    displayQueue(pq.diphthongQ);
}

int main() {
    TList* synList = NULL;
    TList* antList = NULL;
    TQueue* syllableQueue = NULL;
    PronunciationQueues pronunciationQueues;
    char filename[100] = "words.txt"; // Default filename
    int choice;
    
    printf("=== Word Queue Management System ===\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: { // Load words from file
                printf("Enter filename (or press enter for default 'words.txt'): ");
                getchar(); // Consume newline
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0'; // Remove newline
                if (strlen(filename) == 0) strcpy(filename, "words.txt");
                
                FILE* f = fopen(filename, "r");
                if (!f) {
                    printf("Error opening file %s\n", filename);
                    break;
                }
                
                synList = getSynWords(f);
                rewind(f);
                antList = getAntoWords(f);
                fclose(f);
                
                printf("Loaded %d synonyms and %d antonyms from %s\n", 
                       countListNodes(synList), countListNodes(antList), filename);
                break;
            }
                
            case 2: { // Get word information
                char word[100];
                printf("Enter word to look up: ");
                scanf("%s", word);
                getInfWord(synList, antList, word);
                break;
            }
                
            case 3: // Sort words alphabetically
                synList = sortWord(synList);
                printf("Synonyms sorted alphabetically\n");
                break;
                
            case 4: // Sort words by length
                synList = sortWord2(synList);
                printf("Synonyms sorted by length\n");
                break;
                
            case 5: // Sort words by vowel count
                synList = sortWord3(synList);
                printf("Synonyms sorted by vowel count\n");
                break;
                
            case 6: { // Delete a word
                char word[100];
                printf("Enter word to delete: ");
                scanf("%s", word);
                synList = deleteWord(filename, synList, antList, word);
                printf("Word '%s' deleted from lists and file\n", word);
                break;
            }
                
            case 7: { // Update word information
                char word[100], syn[100], ant[100];
                printf("Enter word to update: ");
                scanf("%s", word);
                printf("Enter new synonym: ");
                scanf("%s", syn);
                printf("Enter new antonym: ");
                scanf("%s", ant);
                synList = updateWord(filename, synList, antList, word, syn, ant);
                printf("Word '%s' updated\n", word);
                break;
            }
                
            case 8: { // Find similar words
                char word[100];
                double rate;
                printf("Enter word to compare: ");
                scanf("%s", word);
                printf("Enter similarity rate (0.0-1.0): ");
                scanf("%lf", &rate);
                TList* similar = similarWord(synList, word, rate);
                printf("Words with similarity >= %.2f:\n", rate);
                displayList(similar);
                freeList(similar);
                break;
            }
                
            case 9: { // Merge lists
                TList* merged = merge(synList, antList);
                printf("Merged list created\n");
                displayList(merged);
                freeList(merged);
                break;
            }
                
            case 10: { // Add new word
                char word[100], syn[100], ant[100];
                printf("Enter new word: ");
                scanf("%s", word);
                printf("Enter synonym: ");
                scanf("%s", syn);
                printf("Enter antonym: ");
                scanf("%s", ant);
                synList = addWord(synList, antList, word, syn, ant, filename);
                printf("Word '%s' added\n", word);
                break;
            }
                
            case 11: { // Create syllable queue
                if (syllableQueue) {
                    // Free previous queue if exists
                    while (!isEmpty(syllableQueue)) dequeue(syllableQueue);
                    free(syllableQueue);
                }
                syllableQueue = syllable(synList);
                printf("Syllable queue created\n");
                displayQueue(syllableQueue);
                break;
            }
                
            case 12: { // Create pronunciation queues
                pronunciationQueues = prounounciation(synList);
                printf("Pronunciation queues created\n");
                displayPronunciationQueues(pronunciationQueues);
                break;
            }
                
            case 13: // Display current lists
                printf("\nSynonyms:");
                displayList(synList);
                printf("\nAntonyms:");
                displayList(antList);
                break;
                
            case 0: // Exit
                printf("Exiting program\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        // Pause before continuing
        if (choice != 0) {
            printf("\nPress Enter to continue...");
            while (getchar() != '\n'); // Clear input buffer
            getchar(); // Wait for Enter
        }
        
    } while (choice != 0);
    
    // Cleanup
    freeList(synList);
    freeList(antList);
    if (syllableQueue) {
        while (!isEmpty(syllableQueue)) dequeue(syllableQueue);
        free(syllableQueue);
    }
    
    return 0;
}