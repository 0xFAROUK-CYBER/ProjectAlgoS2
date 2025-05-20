
#include "stacks.h"
#include <ctype.h>

void displayMenu() {
    printf("\n\n=== Stack Operations ===\n");
    printf("1. Push (Add log)\n");
    printf("2. Pop (Remove log)\n");
    printf("3. Peek (View top log)\n");
    printf("4. Check if stack is empty\n");
    printf("5. Check if stack is full\n");
    printf("6. Reverse stack\n");
    printf("7. Insert at bottom\n");
    printf("8. Display stack size\n");
    printf("9. Display all logs\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void getLogDetails(SLogEntry* log) {
    printf("Enter Log ID: ");
    scanf("%d", &log->id);
    printf("Enter Timestamp (DD-MM-YYYY HH:MM:SS): ");
    scanf(" %[^\n]", log->timestamp);
    printf("Enter Severity (1-5): ");
    scanf("%d", &log->severity);
    printf("Enter Message: ");
    scanf(" %[^\n]", log->message);
}

void displayLog(SLogEntry log) {
    printf("ID: %d | Time: %s | Severity: %d | Message: %s\n", 
           log.id, log.timestamp, log.severity, log.message);
}

void displayAllLogs(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    
    printf("\n=== All Logs in Stack (%d/%d) ===\n", stack->top + 1, MAX_STACK_SIZE);
    Stack tempStack;
    initStack(&tempStack);
    
    // Copy and display
    while (!isEmpty(stack)) {
        SLogEntry log = pop(stack);
        displayLog(log);
        push(&tempStack, log);
    }
    
    // Restore original stack
    while (!isEmpty(&tempStack)) {
        push(stack, pop(&tempStack));
    }
}

int main() {
    Stack logStack;
    initStack(&logStack);
    int choice;
    SLogEntry log;
    
    printf("=== Log Stack Management System ===\n");
    
    // First create initial stack
    int numLogs;
    printf("How many initial log entries would you like to create? (0-%d): ", MAX_STACK_SIZE);
    scanf("%d", &numLogs);
    
    if (numLogs < 0 || numLogs > MAX_STACK_SIZE) {
        printf("Invalid number. Setting to default (3).\n");
        numLogs = 3;
    }
    
    for (int i = 0; i < numLogs; i++) {
        printf("\nLog Entry #%d:\n", i+1);
        getLogDetails(&log);
        push(&logStack, log);
    }
    
    // Then show the operation menu
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Push
                if (isFull(&logStack)) {
                    printf("Stack is full! Cannot add more logs.\n");
                    break;
                }
                getLogDetails(&log);
                push(&logStack, log);
                printf("Log pushed onto stack.\n");
                break;
                
            case 2: // Pop
                if (isEmpty(&logStack)) {
                    printf("Stack is empty! Nothing to pop.\n");
                    break;
                }
                log = pop(&logStack);
                printf("Popped log:\n");
                displayLog(log);
                break;
                
            case 3: // Peek
                if (isEmpty(&logStack)) {
                    printf("Stack is empty! Nothing to peek.\n");
                    break;
                }
                log = peek(&logStack);
                printf("Top log:\n");
                displayLog(log);
                break;
                
            case 4: // Is empty
                printf("Stack is %s.\n", isEmpty(&logStack) ? "empty" : "not empty");
                break;
                
            case 5: // Is full
                printf("Stack is %s.\n", isFull(&logStack) ? "full" : "not full");
                break;
                
            case 6: // Reverse
                reverseStack(&logStack);
                printf("Stack reversed.\n");
                break;
                
            case 7: // Insert at bottom
                if (isFull(&logStack)) {
                    printf("Stack is full! Cannot insert.\n");
                    break;
                }
                getLogDetails(&log);
                insertAtBottom(&logStack, log);
                printf("Log inserted at bottom.\n");
                break;
                
            case 8: // Size
                printf("Current stack size: %d/%d\n", logStack.top + 1, MAX_STACK_SIZE);
                break;
                
            case 9: // Display all
                displayAllLogs(&logStack);
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