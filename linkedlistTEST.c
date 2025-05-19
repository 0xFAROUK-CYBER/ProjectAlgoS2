// linkedListTest.c
#include "Linkedlists.h"
#include <ctype.h>

void displayMenu() {
    printf("\n\n=== Linked List Operations ===\n");
    printf("1.  Insert at Beginning\n");
    printf("2.  Insert at End\n");
    printf("3.  Insert at Position\n");
    printf("4.  Delete by ID\n");
    printf("5.  Delete by Timestamp\n");
    printf("6.  Delete First\n");
    printf("7.  Delete Last\n");
    printf("8.  Search by ID\n");
    printf("9.  Search by Timestamp\n");
    printf("10. Search by Keyword\n");
    printf("11. Sort by Date\n");
    printf("12. Sort by Severity\n");
    printf("13. Reverse List\n");
    printf("14. Count Nodes\n");
    printf("15. Display All Logs\n");
    printf("0.  Exit\n");
    printf("Enter your choice: ");
}

void getLogDetails(int *id, char *timestamp, int *severity, char *message) {
    printf("Enter Log ID: ");
    scanf("%d", id);
    printf("Enter Timestamp (DD-MM-YYYY HH:MM:SS): ");
    scanf(" %[^\n]", timestamp);
    printf("Enter Severity (1-5): ");
    scanf("%d", severity);
    printf("Enter Message: ");
    scanf(" %[^\n]", message);
}

void displayLog(LogEntry* log) {
    if (log) {
        printf("ID: %d | Time: %s | Severity: %d | Message: %s\n", 
               log->id, log->timestamp, log->severity, log->message);
    } else {
        printf("Log not found.\n");
    }
}

void createInitialList(LogEntry** head) {
    int numLogs;
    printf("=== Linked List Log System ===\n");
    printf("How many initial log entries would you like to create? (0-10): ");
    scanf("%d", &numLogs);
    
    if (numLogs < 0 || numLogs > 10) {
        printf("Invalid number. Setting to default (3).\n");
        numLogs = 3;
    }
    
    for (int i = 0; i < numLogs; i++) {
        printf("\nLog Entry #%d:\n", i+1);
        int id, severity;
        char timestamp[20], message[100];
        
        getLogDetails(&id, timestamp, &severity, message);
        *head = insertAtEnd(*head, id, timestamp, severity, message);
    }
    printf("\nInitial list created with %d log entries.\n", numLogs);
}

void displayAllLogs(LogEntry* head) {
    printf("\n=== All Log Entries (%d) ===\n", countLogs(head));
    LogEntry* current = head;
    while (current) {
        displayLog(current);
        current = current->next;
    }
}

int main() {
    LogEntry* head = NULL;
    int choice, id, position, severity;
    char timestamp[20], message[100], keyword[100];
    
    // First create the initial list
    createInitialList(&head);
    
    // Then show the operation menu
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Insert at beginning
                getLogDetails(&id, timestamp, &severity, message);
                head = insertAtBeginning(head, id, timestamp, severity, message);
                printf("Log added at beginning.\n");
                break;
                
            case 2: // Insert at end
                getLogDetails(&id, timestamp, &severity, message);
                head = insertAtEnd(head, id, timestamp, severity, message);
                printf("Log added at end.\n");
                break;
                
            case 3: // Insert at position
                printf("Enter position (0-%d): ", countLogs(head));
                scanf("%d", &position);
                getLogDetails(&id, timestamp, &severity, message);
                head = insertAtPosition(head, position, id, timestamp, severity, message);
                printf("Log added at position %d.\n", position);
                break;
                
            case 4: // Delete by ID
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                head = deleteByID(head, id);
                printf("Deleted log with ID %d if found.\n", id);
                break;
                
            case 5: // Delete by timestamp
                printf("Enter timestamp to delete (DD-MM-YYYY HH:MM:SS): ");
                scanf(" %[^\n]", timestamp);
                head = deleteByTimestamp(head, timestamp);
                printf("Deleted log with timestamp %s if found.\n", timestamp);
                break;
                
            case 6: // Delete first
                head = deleteFirst(head);
                printf("Deleted first log.\n");
                break;
                
            case 7: // Delete last
                head = deleteLast(head);
                printf("Deleted last log.\n");
                break;
                
            case 8: // Search by ID
                printf("Enter ID to search: ");
                scanf("%d", &id);
                displayLog(searchByID(head, id));
                break;
                
            case 9: // Search by timestamp
                printf("Enter timestamp to search (DD-MM-YYYY HH:MM:SS): ");
                scanf(" %[^\n]", timestamp);
                displayLog(searchByTimestamp(head, timestamp));
                break;
                
            case 10: // Search by keyword
                printf("Enter keyword to search: ");
                scanf(" %[^\n]", keyword);
                displayLog(searchByKeyword(head, keyword));
                break;
                
            case 11: // Sort by date
                head = sortByDate(head);
                printf("List sorted by date.\n");
                break;
                
            case 12: // Sort by severity
                head = sortBySeverity(head);
                printf("List sorted by severity.\n");
                break;
                
            case 13: // Reverse
                head = reverseList(head);
                printf("List reversed.\n");
                break;
                
            case 14: // Count
                printf("Total logs: %d\n", countLogs(head));
                break;
                
            case 15: // Display all
                displayAllLogs(head);
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
    while (head) {
        head = deleteFirst(head);
    }
    
    return 0;
}