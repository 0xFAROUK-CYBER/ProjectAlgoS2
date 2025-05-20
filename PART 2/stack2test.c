#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack2.h"

#define MAX_INPUT 100

// ==================== HELPER FUNCTIONS ====================

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_stack(TStack *stack) {
    printf("\nCurrent Stack:\n");
    printf("---------------\n");
    TStack *current = stack;
    int count = 1;
    while (current) {
        printf("%d. %s\n", count++, current->word);
        printf("   Synonym: %s\n", current->synonym ? current->synonym : "NULL");
        printf("   Antonym: %s\n\n", current->antonym ? current->antonym : "NULL");
        current = current->next;
    }
    if (count == 1) {
        printf("(Stack is empty)\n");
    }
    printf("---------------\n");
}

void print_word_info(TWordInfo *info) {
    if (!info) {
        printf("No word information found.\n");
        return;
    }
    printf("\nWord Information:\n");
    printf("-----------------\n");
    printf("Word: %s\n", info->word);
    printf("Synonym: %s\n", info->synonym ? info->synonym : "NULL");
    printf("Antonym: %s\n", info->antonym ? info->antonym : "NULL");
    printf("Character count: %d\n", info->charCount);
    printf("Vowel count: %d\n", info->vowelCount);
    printf("-----------------\n");
}

void print_pronunciation_stacks(TPronunciationStacks stacks) {
    printf("\nPronunciation Categories:\n");
    printf("=========================\n");
    
    printf("\nShort Vowels:\n");
    print_stack(stacks.shortVowels);
    
    printf("\nLong Vowels:\n");
    print_stack(stacks.longVowels);
    
    printf("\nDiphthongs:\n");
    print_stack(stacks.diphthongs);
}

void display_menu() {
    printf("\n=== STACK OPERATIONS MENU ===\n");
    printf("1. Convert List to Stack\n");
    printf("2. Get Word Information\n");
    printf("3. Sort Stack Alphabetically\n");
    printf("4. Delete Word from Stack\n");
    printf("5. Update Word in Stack\n");
    printf("6. Convert Stack to Queue\n");
    printf("7. Convert Stack to Doubly Linked List\n");
    printf("8. Add Word to Stack\n");
    printf("9. Sort Stack by Syllable Count\n");
    printf("10. Categorize by Pronunciation\n");
    printf("11. Find Smallest Word\n");
    printf("12. Detect Synonym/Antonym Cycles\n");
    printf("13. Check if Word is Palindrome\n");
    printf("14. Reverse Stack\n");
    printf("15. View Current Stack\n");
    printf("0. Exit\n");
    printf("=============================\n");
}

TSList *create_list_interactive() {
    TSList *list = NULL;
    char choice;
    
    printf("\n=== Create Linked List ===\n");
    do {
        TSList *new_node = malloc(sizeof(TSList));
        if (!new_node) {
            printf("Memory allocation failed!\n");
            return list;
        }
        
        new_node->word = malloc(MAX_INPUT);
        new_node->synonym = malloc(MAX_INPUT);
        new_node->antonym = malloc(MAX_INPUT);
        
        if (!new_node->word || !new_node->synonym || !new_node->antonym) {
            printf("Memory allocation failed!\n");
            free(new_node->word);
            free(new_node->synonym);
            free(new_node->antonym);
            free(new_node);
            return list;
        }
        
        printf("\nEnter word: ");
        scanf("%99s", new_node->word);
        clear_input_buffer();
        
        printf("Enter synonym: ");
        fgets(new_node->synonym, MAX_INPUT, stdin);
        new_node->synonym[strcspn(new_node->synonym, "\n")] = '\0';
        
        printf("Enter antonym: ");
        fgets(new_node->antonym, MAX_INPUT, stdin);
        new_node->antonym[strcspn(new_node->antonym, "\n")] = '\0';
        
        new_node->next = list;
        list = new_node;
        
        printf("\nAdd another word? (y/n): ");
        scanf(" %c", &choice);
        clear_input_buffer();
    } while (tolower(choice) == 'y');
    
    return list;
}

// ==================== TEST FUNCTIONS ====================

void test_toStack(TStack **stack) {
    printf("\n=== Convert List to Stack ===\n");
    TSList *list = create_list_interactive();
    
    *stack = toStack(list);
    printf("\nList converted to stack successfully!\n");
    print_stack(*stack);
    
    // Free the original list
    while (list) {
        TSList *temp = list;
        list = list->next;
        free(temp->word);
        free(temp->synonym);
        free(temp->antonym);
        free(temp);
    }
}

void test_getInfWordStack(TStack *stack) {
    if (!stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Get Word Information ===\n");
    char word[MAX_INPUT];
    
    printf("Enter word to search: ");
    scanf("%99s", word);
    clear_input_buffer();
    
    TWordInfo *info = getInfWordStack(stack, word);
    print_word_info(info);
    
    if (info) freeWordInfo(info);
}

void test_sortWordStack(TStack **stack) {
    if (!*stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Sort Stack Alphabetically ===\n");
    *stack = sortWordStack(*stack);
    printf("Stack sorted successfully!\n");
    print_stack(*stack);
}

void test_deleteWordStack(TStack **stack) {
    if (!*stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Delete Word from Stack ===\n");
    char word[MAX_INPUT];
    
    printf("Current stack:\n");
    print_stack(*stack);
    
    printf("\nEnter word to delete: ");
    scanf("%99s", word);
    clear_input_buffer();
    
    *stack = deleteWordStack(*stack, word);
    printf("\nOperation completed. Updated stack:\n");
    print_stack(*stack);
}

void test_updateWordStack(TStack **stack) {
    if (!*stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Update Word in Stack ===\n");
    char word[MAX_INPUT], synonym[MAX_INPUT], antonym[MAX_INPUT];
    
    printf("Current stack:\n");
    print_stack(*stack);
    
    printf("\nEnter word to update: ");
    scanf("%99s", word);
    clear_input_buffer();
    
    printf("Enter new synonym (or press Enter to skip): ");
    fgets(synonym, MAX_INPUT, stdin);
    synonym[strcspn(synonym, "\n")] = '\0';
    
    printf("Enter new antonym (or press Enter to skip): ");
    fgets(antonym, MAX_INPUT, stdin);
    antonym[strcspn(antonym, "\n")] = '\0';
    
    *stack = updateWordStack(*stack, word, 
                           strlen(synonym) > 0 ? synonym : NULL, 
                           strlen(antonym) > 0 ? antonym : NULL);
    printf("\nUpdate completed. Updated stack:\n");
    print_stack(*stack);
}

void test_stackToQueue(TStack *stack) {
    if (!stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Convert Stack to Queue ===\n");
    TQueue *queue = stackToQueue(stack);
    
    printf("\nQueue Contents:\n");
    printf("---------------\n");
    TQueue *current = queue;
    while (current) {
        printf("- %s\n", current->word);
        current = current->next;
    }
    printf("---------------\n");
    
    freeQueue(queue);
}

void test_StacktoList(TStack *stack) {
    if (!stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Convert Stack to Doubly Linked List ===\n");
    TDList *list = StacktoList(stack);
    
    printf("\nList Contents (forward):\n");
    printf("------------------------\n");
    TDList *current = list;
    while (current) {
        printf("- %s\n", current->word);
        current = current->next;
    }
    printf("------------------------\n");
    
    printf("\nList Contents (backward):\n");
    printf("-------------------------\n");
    current = list;
    while (current && current->next) current = current->next; // Move to tail
    while (current) {
        printf("- %s\n", current->word);
        current = current->prev;
    }
    printf("-------------------------\n");
    
    freeList(list);
}

void test_addWordStack(TStack **stack) {
    printf("\n=== Add Word to Stack ===\n");
    char word[MAX_INPUT], synonym[MAX_INPUT], antonym[MAX_INPUT];
    
    printf("Enter new word: ");
    scanf("%99s", word);
    clear_input_buffer();
    
    printf("Enter synonym: ");
    fgets(synonym, MAX_INPUT, stdin);
    synonym[strcspn(synonym, "\n")] = '\0';
    
    printf("Enter antonym: ");
    fgets(antonym, MAX_INPUT, stdin);
    antonym[strcspn(antonym, "\n")] = '\0';
    
    *stack = addWordStack(*stack, word, 
                        strlen(synonym) > 0 ? synonym : NULL, 
                        strlen(antonym) > 0 ? antonym : NULL);
    printf("\nWord added successfully!\n");
    print_stack(*stack);
}

void test_syllableStack(TStack **stack) {
    if (!*stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Sort Stack by Syllable Count ===\n");
    *stack = syllableStack(*stack);
    printf("Stack sorted by syllable count!\n");
    
    printf("\nWords with syllable counts:\n");
    printf("---------------------------\n");
    TStack *current = *stack;
    while (current) {
        printf("- %s (%d syllables)\n", current->word, countSyllables(current->word));
        current = current->next;
    }
    printf("---------------------------\n");
}

void test_prounounciationStack(TStack *stack) {
    if (!stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Categorize by Pronunciation ===\n");
    TPronunciationStacks result = prounounciationStack(stack);
    print_pronunciation_stacks(result);
    
    // Free the category stacks
    freeStack(result.shortVowels);
    freeStack(result.longVowels);
    freeStack(result.diphthongs);
}

void test_getSmallest(TStack *stack) {
    if (!stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Find Smallest Word ===\n");
    char *smallest = getSmallest(stack);
    if (smallest) {
        printf("The lexicographically smallest word is: %s\n", smallest);
        free(smallest);
    } else {
        printf("Could not determine smallest word.\n");
    }
}

void test_cycleSearch(TStack *stack) {
    if (!stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Detect Synonym/Antonym Cycles ===\n");
    printf("Analyzing relationships...\n");
    cycleSearch(stack);
}

void test_isPalindromeStack() {
    printf("\n=== Check if Word is Palindrome ===\n");
    char word[MAX_INPUT];
    
    printf("Enter word to check: ");
    scanf("%99s", word);
    clear_input_buffer();
    
    if (isPalindromeStack(word)) {
        printf("\"%s\" IS a palindrome!\n", word);
    } else {
        printf("\"%s\" is NOT a palindrome.\n", word);
    }
}

void test_StackRev(TStack **stack) {
    if (!*stack) {
        printf("\nStack is empty!\n");
        return;
    }
    
    printf("\n=== Reverse Stack ===\n");
    printf("Original stack:\n");
    print_stack(*stack);
    
    *stack = StackRev(*stack);
    
    printf("\nReversed stack:\n");
    print_stack(*stack);
}



// ==================== MAIN PROGRAM ====================

int main() {
    TStack *stack = NULL;
    int choice;
    
    printf("=== STACK OPERATIONS TEST PROGRAM ===\n");
    
    // First, let the user create the initial stack
    printf("\nFirst, let's create your initial stack:\n");
    test_toStack(&stack);
    
    // Then proceed with the menu operations
    do {
        display_menu();
        printf("Enter your choice (0-15): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        switch(choice) {
            case 1: 
                printf("\nCreating a new stack will replace the current one. Continue? (y/n): ");
                char confirm;
                scanf(" %c", &confirm);
                clear_input_buffer();
                if (tolower(confirm) == 'y') {
                    freeStack(stack);
                    test_toStack(&stack);
                }
                break;
            case 2: test_getInfWordStack(stack); break;
            case 3: test_sortWordStack(&stack); break;
            case 4: test_deleteWordStack(&stack); break;
            case 5: test_updateWordStack(&stack); break;
            case 6: test_stackToQueue(stack); break;
            case 7: test_StacktoList(stack); break;
            case 8: test_addWordStack(&stack); break;
            case 9: test_syllableStack(&stack); break;
            case 10: test_prounounciationStack(stack); break;
            case 11: test_getSmallest(stack); break;
            case 12: test_cycleSearch(stack); break;
            case 13: test_isPalindromeStack(); break;
            case 14: test_StackRev(&stack); break;
            case 15: print_stack(stack); break;
            case 0: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
        
        if (choice != 0) {
            printf("\nPress Enter to continue...");
            while (getchar() != '\n');
        }
    } while (choice != 0);
    
    freeStack(stack);
    return 0;
}