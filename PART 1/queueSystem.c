// queueTest.c
#include "queues.h"
#include <ctype.h>

void displayMenu() {
    printf("\n\n=== Queue Operations ===\n");
    printf("1. Enqueue (Add log)\n");
    printf("2. Dequeue (Remove log)\n");
    printf("3. Peek (View front log)\n");
    printf("4. Check if queue is empty\n");
    printf("5. Check if queue is full\n");
    printf("6. Display queue size\n");
    printf("7. Display all logs\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void getLogDetails(QLogEntry* log) {
    printf("Enter Log ID: ");
    scanf("%d", &log->id);
    printf("Enter Timestamp (DD-MM-YYYY HH:MM:SS): ");
    scanf(" %[^\n]", log->timestamp);
    printf("Enter Severity (1-5): ");
    scanf("%d", &log->severity);
    printf("Enter Message: ");
    scanf(" %[^\n]", log->message);
}

void displayLog(QLogEntry log) {
    printf("ID: %d | Time: %s | Severity: %d | Message: %s\n", 
           log.id, log.timestamp, log.severity, log.message);
}

void displayAllLogs(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    
    printf("\n=== All Logs in Queue (%d/%d) ===\n", q->size, MAX_QUEUE_SIZE);
    int index = q->front;
    for (int i = 0; i < q->size; i++) {
        printf("%d. ", i+1);
        displayLog(q->entries[index]);
        index = (index + 1) % MAX_QUEUE_SIZE;
    }
}

int main() {
    Queue logQueue;
    initQueue(&logQueue);
    int choice;
    QLogEntry log;
    
    printf("=== Log Queue Management System ===\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Enqueue
                if (isQueueFull(&logQueue)) {
                    printf("Queue is full! Cannot add more logs.\n");
                    break;
                }
                getLogDetails(&log);
                enqueue(&logQueue, log);
                printf("Log added to queue.\n");
                break;
                
            case 2: // Dequeue
                if (isQueueEmpty(&logQueue)) {
                    printf("Queue is empty! Nothing to remove.\n");
                    break;
                }
                log = dequeue(&logQueue);
                printf("Dequeued log:\n");
                displayLog(log);
                break;
                
            case 3: // Peek
                if (isQueueEmpty(&logQueue)) {
                    printf("Queue is empty! Nothing to peek.\n");
                    break;
                }
                log = peekQueue(&logQueue);
                printf("Front log:\n");
                displayLog(log);
                break;
                
            case 4: // Is empty
                printf("Queue is %s.\n", isQueueEmpty(&logQueue) ? "empty" : "not empty");
                break;
                
            case 5: // Is full
                printf("Queue is %s.\n", isQueueFull(&logQueue) ? "full" : "not full");
                break;
                
            case 6: // Size
                printf("Current queue size: %d/%d\n", logQueue.size, MAX_QUEUE_SIZE);
                break;
                
            case 7: // Display all
                displayAllLogs(&logQueue);
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
    
    return 0;
}