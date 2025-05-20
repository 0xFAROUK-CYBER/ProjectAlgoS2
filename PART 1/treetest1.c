// treeTest.c
#include "trees.h"
#include <ctype.h>

void displayMenu() {
    printf("\n\n=== Tree Operations ===\n");
    printf("1. Insert into BST\n");
    printf("2. Delete from BST\n");
    printf("3. Search in BST\n");
    printf("4. In-order Traversal\n");
    printf("5. Pre-order Traversal\n");
    printf("6. Post-order Traversal\n");
    printf("7. Convert Sorted List to BST\n");
    printf("8. Build Max Heap from Array\n");
    printf("9. Display Current Tree (In-order)\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void getLogDetails(int *id, char *timestamp, int *severity, char *message) {
    printf("Enter Log ID: ");
    scanf("%d", id);
    printf("Enter Timestamp (format: DD-MM-YYYY HH:MM:SS): ");
    scanf(" %[^\n]", timestamp);
    printf("Enter Severity (1-5): ");
    scanf("%d", severity);
    printf("Enter Message: ");
    scanf(" %[^\n]", message);
}

void displayLog(TLogEntry* log) {
    if (log) {
        printf("ID: %d | Time: %s | Severity: %d | Message: %s\n", 
               log->id, log->timestamp, log->severity, log->message);
    } else {
        printf("Log not found.\n");
    }
}

TLogEntry* createSortedList(int numNodes) {
    TLogEntry* head = NULL;
    TLogEntry* tail = NULL;
    
    for (int i = 0; i < numNodes; i++) {
        printf("\nCreating sorted list node #%d:\n", i+1);
        int id, severity;
        char timestamp[20], message[100];
        
        getLogDetails(&id, timestamp, &severity, message);
        
        TLogEntry* newNode = (TLogEntry*)malloc(sizeof(TLogEntry));
        newNode->id = id;
        strcpy(newNode->timestamp, timestamp);
        newNode->severity = severity;
        strcpy(newNode->message, message);
        newNode->left = NULL;
        newNode->right = NULL;
        
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->right = newNode;
            tail = newNode;
        }
    }
    return head;
}

void displayHeap(TLogEntry arr[], int n) {
    printf("\nHeap Contents (%d elements):\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i+1, arr[i].timestamp);
    }
}

int main() {
    TLogEntry* root = NULL;
    TLogEntry* sortedList = NULL;
    TLogEntry heapArray[100];
    int heapSize = 0;
    int choice, id, severity;
    char timestamp[20], message[100];
    
    printf("=== Tree Operations Test System ===\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Insert into BST
                getLogDetails(&id, timestamp, &severity, message);
                root = insertBST(root, id, timestamp, severity, message);
                printf("Log inserted into BST.\n");
                break;
                
            case 2: // Delete from BST
                printf("Enter timestamp to delete: ");
                scanf(" %[^\n]", timestamp);
                root = deleteBST(root, timestamp);
                printf("Log with timestamp %s deleted if found.\n", timestamp);
                break;
                
            case 3: // Search in BST
                printf("Enter timestamp to search: ");
                scanf(" %[^\n]", timestamp);
                TLogEntry* found = searchBST(root, timestamp);
                displayLog(found);
                break;
                
            case 4: // In-order Traversal
                printf("\nIn-order Traversal:\n");
                inOrderTraversal(root);
                break;
                
            case 5: // Pre-order Traversal
                printf("\nPre-order Traversal:\n");
                preOrderTraversal(root);
                break;
                
            case 6: // Post-order Traversal
                printf("\nPost-order Traversal:\n");
                postOrderTraversal(root);
                break;
                
            case 7: // Convert Sorted List to BST
                printf("How many nodes in sorted list? ");
                int numNodes;
                scanf("%d", &numNodes);
                sortedList = createSortedList(numNodes);
                root = sortedListToBST(&sortedList, countListNodes(sortedList));
                printf("Converted sorted list to balanced BST.\n");
                break;
                
            case 8: // Build Max Heap
                printf("How many elements in heap? (max 100): ");
                scanf("%d", &heapSize);
                if (heapSize > 100) heapSize = 100;
                
                for (int i = 0; i < heapSize; i++) {
                    printf("\nHeap element #%d:\n", i+1);
                    getLogDetails(&id, timestamp, &severity, message);
                    heapArray[i].id = id;
                    strcpy(heapArray[i].timestamp, timestamp);
                    heapArray[i].severity = severity;
                    strcpy(heapArray[i].message, message);
                }
                
                buildHeap(heapArray, heapSize);
                printf("Max heap built from array.\n");
                displayHeap(heapArray, heapSize);
                break;
                
            case 9: // Display Tree (In-order)
                printf("\nCurrent BST (In-order):\n");
                inOrderTraversal(root);
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
    
    // TODO: Add memory cleanup for tree nodes
    
    return 0;
}