#include <stdio.h>
#define MAX 5

int push(int stack[], int maxSize, int top) {
    if (top == maxSize - 1) {
        printf("Overflow! Stack is full.\n");
        return top;
    } else {
        int value;
        printf("Enter value: ");
        scanf("%d", &value);
        top++;
        stack[top] = value;
        printf("%d pushed into stack.\n", value);
        return top;
    }
}

int pop(int stack[], int top) {
    if (top == -1) {
        printf("Underflow! Stack is empty.\n");
        return top;
    } else {
        printf("%d popped from stack.\n", stack[top]);
        top--;
        return top;
    }
}

void peek(int stack[], int top) {
    if (top == -1)
        printf("Stack is empty!\n");
    else
        printf("Top element: %d\n", stack[top]);
}

void display(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty!\n");
    } else {
        printf("Stack elements (top to bottom): ");
        for (int i = top; i >= 0; i--)
            printf("%d ", stack[i]);
        printf("\n");
    }
}

int main() {
    int stack[MAX];
    int top = -1;
    int choice;

    while (1) {
        printf("\n==== MENU ====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                top = push(stack, MAX, top);
                break;
            case 2:
                top = pop(stack, top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Program terminated.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}


