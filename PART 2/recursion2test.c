#include "recursion2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

File* createNode(const char* word) {
    File* newNode = (File*)malloc(sizeof(File));
    newNode->word = strdup(word);
    newNode->next = NULL;
    return newNode;
}

File* insertAtEnd(File* head, const char* word) {
    File* newNode = createNode(word);
    if (!head) return newNode;
    
    File* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

void displayList(File* head) {
    printf("\nCurrent List:\n");
    while (head) {
        printf("%s -> ", head->word);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(File* head) {
    while (head) {
        File* temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

void displayMenu() {
    printf("\n\n=== Recursive String Operations ===\n");
    printf("1. Count word occurrences in list\n");
    printf("2. Remove word occurrences from list\n");
    printf("3. Replace word occurrences in list\n");
    printf("4. Generate all permutations of a word\n");
    printf("5. Generate all subsequences of a word\n");
    printf("6. Find longest common subsequence length\n");
    printf("7. Count distinct subsequences of a word\n");
    printf("8. Check if word is palindrome\n");
    printf("9. Display current list\n");
    printf("10. Add word to list\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    File* head = NULL;
    int choice;
    char word[100], rep[100], word1[100], word2[100];
    
    printf("=== Recursive String Operations Test System ===\n");
    
    // Create initial list
    int numWords;
    printf("How many initial words would you like to add to the list? ");
    scanf("%d", &numWords);
    
    for (int i = 0; i < numWords; i++) {
        printf("Enter word #%d: ", i+1);
        scanf("%s", word);
        head = insertAtEnd(head, word);
    }
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Count word occurrences
                printf("Enter word to count: ");
                scanf("%s", word);
                printf("'%s' appears %d times in the list\n", 
                       word, countWordOccurence(head, word));
                break;
                
            case 2: // Remove word occurrences
                printf("Enter word to remove: ");
                scanf("%s", word);
                head = removeWordOccurence(head, word);
                printf("All occurrences of '%s' removed\n", word);
                break;
                
            case 3: // Replace word occurrences
                printf("Enter word to replace: ");
                scanf("%s", word);
                printf("Enter replacement word: ");
                scanf("%s", rep);
                head = replaceWordOccurence(head, word, rep);
                printf("All '%s' replaced with '%s'\n", word, rep);
                break;
                
            case 4: // Generate permutations
                printf("Enter word to permute: ");
                scanf("%s", word);
                printf("All permutations of '%s':\n", word);
                wordPermutation(word);
                break;
                
            case 5: // Generate subsequences
                printf("Enter word for subsequences: ");
                scanf("%s", word);
                printf("All subsequences of '%s':\n", word);
                subseqWord(word);
                break;
                
            case 6: // Longest common subsequence
                printf("Enter first word: ");
                scanf("%s", word1);
                printf("Enter second word: ");
                scanf("%s", word2);
                printf("Longest common subsequence length: %d\n", 
                       longestSubseqWord(word1, word2));
                break;
                
            case 7: // Distinct subsequences
                printf("Enter word to count distinct subsequences: ");
                scanf("%s", word);
                printf("Number of distinct subsequences: %d\n", 
                       distinctSubseqWord(word));
                break;
                
            case 8: // Check palindrome
                printf("Enter word to check: ");
                scanf("%s", word);
                printf("'%s' is %sa palindrome\n", 
                       word, isPalindromWord(word) ? "" : "not ");
                break;
                
            case 9: // Display list
                displayList(head);
                break;
                
            case 10: // Add word to list
                printf("Enter word to add: ");
                scanf("%s", word);
                head = insertAtEnd(head, word);
                printf("'%s' added to list\n", word);
                break;
                
            case 0: // Exit
                printf("Exiting program.\n");
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
    
    // Free memory before exiting
    freeList(head);
    
    return 0;
}