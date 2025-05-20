
#include "recursion.h"
#include <ctype.h>

void displayMenu() {
    printf("\n\n=== Recursive Function Operations ===\n");
    printf("1. Reverse Linked List Recursively\n");
    printf("2. Calculate Factorial\n");
    printf("3. Calculate Fibonacci Sequence\n");
    printf("4. Find Maximum ID in List\n");
    printf("5. Binary Search in Sorted Log Array\n");
    printf("6. Convert Infix to Postfix Expression\n");
    printf("7. Display Current List\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

RLogEntry* createRNode(int id, const char* timestamp, int severity, const char* message) {
    RLogEntry* newNode = (RLogEntry*)malloc(sizeof(RLogEntry));
    newNode->id = id;
    strcpy(newNode->timestamp, timestamp);
    newNode->severity = severity;
    strcpy(newNode->message, message);
    newNode->next = NULL;
    return newNode;
}

RLogEntry* insertAtEndR(RLogEntry* head, int id, const char* timestamp, int severity, const char* message) {
    RLogEntry* newNode = createRNode(id, timestamp, severity, message);
    if (!head) return newNode;
    RLogEntry* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

void displayList(RLogEntry* head) {
    printf("\nCurrent List:\n");
    while (head) {
        printf("ID: %d | Time: %s | Severity: %d | Message: %s\n",
               head->id, head->timestamp, head->severity, head->message);
        head = head->next;
    }
}

void freeList(RLogEntry* head) {
    while (head) {
        RLogEntry* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    RLogEntry* head = NULL;
    RLogEntry* logsArray[100];
    int arraySize = 0;
    int choice, n, id, severity;
    char timestamp[20], message[100], infix[100], postfix[100];
    int index;
    
    printf("=== Recursive Function Test System ===\n");
    
    // First create initial list
    int numLogs;
    printf("How many initial log entries would you like to create? ");
    scanf("%d", &numLogs);
    
    for (int i = 0; i < numLogs; i++) {
        printf("\nLog Entry #%d:\n", i+1);
        printf("Enter ID: ");
        scanf("%d", &id);
        printf("Enter Timestamp (DD-MM-YYYY HH:MM:SS): ");
        scanf(" %[^\n]", timestamp);
        printf("Enter Severity (1-5): ");
        scanf("%d", &severity);
        printf("Enter Message: ");
        scanf(" %[^\n]", message);
        head = insertAtEndR(head, id, timestamp, severity, message);
    }
    
    // Prepare sorted array for binary search
    RLogEntry* temp = head;
    while (temp && arraySize < 100) {
        logsArray[arraySize++] = temp;
        temp = temp->next;
    }
    
    // Sort array by ID for binary search
    for (int i = 0; i < arraySize-1; i++) {
        for (int j = 0; j < arraySize-i-1; j++) {
            if (logsArray[j]->id > logsArray[j+1]->id) {
                RLogEntry* temp = logsArray[j];
                logsArray[j] = logsArray[j+1];
                logsArray[j+1] = temp;
            }
        }
    }
    
    // Then show the operation menu
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Reverse list recursively
                head = reverseListRecursive(head);
                printf("List reversed recursively.\n");
                displayList(head);
                break;
                
            case 2: // Factorial
                printf("Enter number to calculate factorial: ");
                scanf("%d", &n);
                printf("Factorial of %d is %d\n", n, factorial(n));
                break;
                
            case 3: // Fibonacci
                printf("Enter position in Fibonacci sequence: ");
                scanf("%d", &n);
                printf("Fibonacci(%d) = %d\n", n, fibonacci(n));
                break;
                
            case 4: // Find max ID
                printf("Maximum ID in list: %d\n", findMaxID(head));
                break;
                
            case 5: // Binary search
                printf("Enter ID to search: ");
                scanf("%d", &id);
                int result = binarySearchLog(logsArray, 0, arraySize-1, id);
                if (result != -1) {
                    printf("Found at position %d:\n", result);
                    printf("ID: %d | Time: %s | Severity: %d | Message: %s\n",
                           logsArray[result]->id, logsArray[result]->timestamp,
                           logsArray[result]->severity, logsArray[result]->message);
                } else {
                    printf("ID %d not found in list.\n", id);
                }
                break;
                
            case 6: // Infix to postfix
                printf("Enter infix expression (numbers and +-*/ only): ");
                scanf(" %[^\n]", infix);
                index = 0;
                infixToPostfix(infix, postfix, &index);
                printf("Postfix expression: %s\n", postfix);
                break;
                
            case 7: // Display list
                displayList(head);
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