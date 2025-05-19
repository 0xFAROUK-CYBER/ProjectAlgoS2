// bidirectionalLinkedListTest.c
#include "bidirectionalLinkedLists.h"
#include <ctype.h>

void displayMenu() {
    printf("\n\n=== Bidirectional Linked List Operations ===\n");
    printf("1. Insert at Beginning\n");
    printf("2. Insert at End\n");
    printf("3. Insert at Position\n");
    printf("4. Delete by ID\n");
    printf("5. Delete First\n");
    printf("6. Delete Last\n");
    printf("7. Delete Middle Node\n");
    printf("8. Search by ID\n");
    printf("9. Search by Timestamp\n");
    printf("10. Search by Keyword\n");
    printf("11. Sort by Date\n");
    printf("12. Sort by Severity\n");
    printf("13. Reverse List\n");
    printf("14. Count Nodes\n");
    printf("15. Move Forward\n");
    printf("16. Move Backward\n");
    printf("17. Display All Logs\n");
    printf("18. Merge with Another List\n");
    printf("0. Exit\n");
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

void displayLog(DLogEntry* log) {
    if (log) {
        printf("ID: %d | Time: %s | Severity: %d | Message: %s\n", 
               log->id, log->timestamp, log->severity, log->message);
    } else {
        printf("Log not found.\n");
    }
}

void displayAllLogs(DLogEntry* head) {
    printf("\n=== All Log Entries (%d) ===\n", countLogsD(head));
    DLogEntry* current = head;
    while (current) {
        displayLog(current);
        current = current->next;
    }
}

DLogEntry* createSecondList() {
    DLogEntry* list2 = NULL;
    int numLogs;
    printf("How many logs to add to second list? ");
    scanf("%d", &numLogs);
    
    for (int i = 0; i < numLogs; i++) {
        printf("\nLog Entry #%d for second list:\n", i+1);
        int id, severity;
        char timestamp[20], message[100];
        
        getLogDetails(&id, timestamp, &severity, message);
        list2 = insertAtEndD(list2, id, timestamp, severity, message);
    }
    return list2;
}

int main() {
    DLogEntry* head = NULL;
    DLogEntry* current = NULL;
    int choice, id, position, severity, steps;
    char timestamp[20], message[100], keyword[100];
    
    printf("=== Bidirectional Linked List Log System ===\n");
    
    // First create the initial list
    int numLogs;
    printf("How many initial log entries would you like to create? ");
    scanf("%d", &numLogs);
    
    for (int i = 0; i < numLogs; i++) {
        printf("\nLog Entry #%d:\n", i+1);
        getLogDetails(&id, timestamp, &severity, message);
        head = insertAtEndD(head, id, timestamp, severity, message);
    }
    
    // Then show the operation menu
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Insert at beginning
                getLogDetails(&id, timestamp, &severity, message);
                head = insertAtBeginningD(head, id, timestamp, severity, message);
                printf("Log added at beginning.\n");
                break;
                
            case 2: // Insert at end
                getLogDetails(&id, timestamp, &severity, message);
                head = insertAtEndD(head, id, timestamp, severity, message);
                printf("Log added at end.\n");
                break;
                
            case 3: // Insert at position
                printf("Enter position (0-%d): ", countLogsD(head));
                scanf("%d", &position);
                getLogDetails(&id, timestamp, &severity, message);
                head = insertAtPositionD(head, position, id, timestamp, severity, message);
                printf("Log added at position %d.\n", position);
                break;
                
            case 4: // Delete by ID
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                head = deleteByIDD(head, id);
                printf("Deleted log with ID %d if found.\n", id);
                break;
                
            case 5: // Delete first
                head = deleteFirstD(head);
                printf("Deleted first log.\n");
                break;
                
            case 6: // Delete last
                head = deleteLastD(head);
                printf("Deleted last log.\n");
                break;
                
            case 7: // Delete middle
                head = deleteMiddleNode(head);
                printf("Deleted middle node.\n");
                break;
                
            case 8: // Search by ID
                printf("Enter ID to search: ");
                scanf("%d", &id);
                current = searchByIDD(head, id);
                displayLog(current);
                break;
                
            case 9: // Search by timestamp
                printf("Enter timestamp to search (DD-MM-YYYY HH:MM:SS): ");
                scanf(" %[^\n]", timestamp);
                current = searchByTimestampD(head, timestamp);
                displayLog(current);
                break;
                
            case 10: // Search by keyword
                printf("Enter keyword to search: ");
                scanf(" %[^\n]", keyword);
                current = searchByKeywordD(head, keyword);
                displayLog(current);
                break;
                
            case 11: // Sort by date
                head = sortByDateD(head);
                printf("List sorted by date.\n");
                break;
                
            case 12: // Sort by severity
                head = sortBySeverityD(head);
                printf("List sorted by severity.\n");
                break;
                
            case 13: // Reverse
                head = reverseListD(head);
                printf("List reversed.\n");
                break;
                
            case 14: // Count
                printf("Total logs: %d\n", countLogsD(head));
                break;
                
            case 15: // Move forward
                printf("Enter steps to move forward: ");
                scanf("%d", &steps);
                if (!current) current = head;
                current = moveForward(current, steps);
                printf("Current node after moving:\n");
                displayLog(current);
                break;
                
            case 16: // Move backward
                printf("Enter steps to move backward: ");
                scanf("%d", &steps);
                if (!current) current = head;
                current = moveBackward(current, steps);
                printf("Current node after moving:\n");
                displayLog(current);
                break;
                
            case 17: // Display all
                displayAllLogs(head);
                break;
                
            case 18: // Merge lists
                printf("Creating second list to merge...\n");
                DLogEntry* list2 = createSecondList();
                head = mergeDLists(head, list2);
                printf("Lists merged successfully.\n");
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
        head = deleteFirstD(head);
    }
    
    return 0;
}