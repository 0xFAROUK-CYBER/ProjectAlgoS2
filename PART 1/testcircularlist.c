// circularListTest.c
#include "circularLists.h"
#include <ctype.h>

void displayMenu() {
    printf("\n\n=== Circular Linked List Operations ===\n");
    printf("1.  Insert Log Entry\n");
    printf("2.  Insert Log at Position\n");
    printf("3.  Delete Log by ID\n");
    printf("4.  Delete First Log\n");
    printf("5.  Delete Last Log\n");
    printf("6.  Search Log by ID\n");
    printf("7.  Search Log by Timestamp\n");
    printf("8.  Search Log by Keyword\n");
    printf("9.  Sort Logs by Date\n");
    printf("10. Sort Logs by Severity\n");
    printf("11. Reverse Log List\n");
    printf("12. Count Log Entries\n");
    printf("13. Display All Logs\n");
    printf("14. Maintain Fixed Size Buffer\n");
    printf("15. Detect Cycle\n");
    printf("0.  Exit\n");
    printf("Enter your choice: ");
}

void getLogDetails(int *id, char *timestamp, int *severity, char *message) {
    printf("Enter Log ID: ");
    scanf("%d", id);
    printf("Enter Timestamp (format YYYY-MM-DD HH:MM:SS): ");
    scanf(" %[^\n]", timestamp);
    printf("Enter Severity (1-5): ");
    scanf("%d", severity);
    printf("Enter Message: ");
    scanf(" %[^\n]", message);
}

void createInitialList(CLogEntry** tail) {
    int numLogs;
    printf("=== Create Initial Log List ===\n");
    printf("How many log entries would you like to create initially? (0-%d): ", MAX_LOGS);
    scanf("%d", &numLogs);
    
    if (numLogs < 0 || numLogs > MAX_LOGS) {
        printf("Invalid number. Setting to default (3).\n");
        numLogs = 3;
    }
    
    for (int i = 0; i < numLogs; i++) {
        printf("\nLog Entry #%d:\n", i+1);
        int id, severity;
        char timestamp[20], message[100];
        
        getLogDetails(&id, timestamp, &severity, message);
        *tail = insertCircular(*tail, id, timestamp, severity, message);
    }
    printf("\nInitial list created with %d log entries.\n", numLogs);
}

int main() {
    CLogEntry* tail = NULL;
    int choice, id, position, severity, size = 0;
    char timestamp[20], message[100], keyword[100];
    
    printf("=== Circular Linked List Log System ===\n");
    
    // First create the initial list
    createInitialList(&tail);
    
    // Then show the operation menu
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Insert
                getLogDetails(&id, timestamp, &severity, message);
                tail = insertCircular(tail, id, timestamp, severity, message);
                printf("Log entry added successfully!\n");
                break;
                
            case 2: // Insert at position
                printf("Enter position: ");
                scanf("%d", &position);
                getLogDetails(&id, timestamp, &severity, message);
                tail = insertAtPositionCircular(tail, position, id, timestamp, severity, message);
                printf("Log entry added at position %d!\n", position);
                break;
                
            case 3: // Delete by ID
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                tail = deleteByIDCircular(tail, id);
                printf("Log with ID %d deleted if found.\n", id);
                break;
                
            case 4: // Delete first
                tail = deleteFirstCircular(tail);
                printf("First log entry deleted.\n");
                break;
                
            case 5: // Delete last
                tail = deleteLastCircular(tail);
                printf("Last log entry deleted.\n");
                break;
                
            case 6: // Search by ID
                printf("Enter ID to search: ");
                scanf("%d", &id);
                CLogEntry* found = searchByIDCircular(tail, id);
                if (found) {
                    printf("Found Log: ID: %d, Time: %s, Severity: %d, Message: %s\n", 
                           found->id, found->timestamp, found->severity, found->message);
                } else {
                    printf("Log with ID %d not found.\n", id);
                }
                break;
                
            case 7: // Search by timestamp
                printf("Enter timestamp to search (format YYYY-MM-DD HH:MM:SS): ");
                scanf(" %[^\n]", timestamp);
                found = searchByTimestampCircular(tail, timestamp);
                if (found) {
                    printf("Found Log: ID: %d, Time: %s, Severity: %d, Message: %s\n", 
                           found->id, found->timestamp, found->severity, found->message);
                } else {
                    printf("Log with timestamp %s not found.\n", timestamp);
                }
                break;
                
            case 8: // Search by keyword
                printf("Enter keyword to search: ");
                scanf(" %[^\n]", keyword);
                found = searchByKeywordCircular(tail, keyword);
                if (found) {
                    printf("Found Log: ID: %d, Time: %s, Severity: %d, Message: %s\n", 
                           found->id, found->timestamp, found->severity, found->message);
                } else {
                    printf("No logs containing '%s' found.\n", keyword);
                }
                break;
                
            case 9: // Sort by date
                tail = sortByDateCircular(tail);
                printf("Logs sorted by date.\n");
                break;
                
            case 10: // Sort by severity
                tail = sortBySeverityCircular(tail);
                printf("Logs sorted by severity.\n");
                break;
                
            case 11: // Reverse
                tail = reverseCircular(tail);
                printf("Log list reversed.\n");
                break;
                
            case 12: // Count
                printf("Total log entries: %d\n", countLogsCircular(tail));
                break;
                
            case 13: // Display all
                printf("\n=== All Log Entries ===\n");
                traverseCircular(tail);
                break;
                
            case 14: // Fixed size buffer
                getLogDetails(&id, timestamp, &severity, message);
                tail = createFixedSizeBuffer(tail, id, timestamp, severity, message, &size);
                printf("Fixed buffer maintained. Current size: %d/%d\n", size, MAX_LOGS);
                break;
                
            case 15: // Detect cycle
                if (tail) {
                    printf("Cycle detection (redundant for circular list): %s\n", 
                           detectCycle(tail->next) ? "Cycle exists" : "No cycle");
                } else {
                    printf("List is empty.\n");
                }
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
    while (tail != NULL) {
        tail = deleteFirstCircular(tail);
    }
    
    return 0;
}