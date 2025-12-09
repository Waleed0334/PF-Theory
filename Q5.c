#include <stdio.h>
#include <string.h>

void reverse(char msg[]) {
    int len = strlen(msg);
    for (int i = 0; i < len / 2; i++) {
        char temp = msg[i];
        msg[i] = msg[len - i - 1];
        msg[len - i - 1] = temp;
    }
}

void toggleBits(char msg[]) {
    for (int i = 0; msg[i] != '\0'; i++) {
        msg[i] ^= (1 << 1);  
        msg[i] ^= (1 << 4);  
    }
}

void encodeMessage(char msg[]) {
    reverse(msg);      
    toggleBits(msg);
    printf("\n Encoded Message is: %s\n", msg);
}

void decodeMessage(char msg[]) {
    toggleBits(msg);  
    reverse(msg);      
    printf("\n Decoded Message is: %s\n", msg);
}

int main() {
    char msg[200];
    int choice;

    while (1) {
        printf("\n-------------------------------------------------------------\n");
        printf("===================TCS Secure Message Tool=====================\n");
        printf("\n-------------------------------------------------------------\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("\nEnter Message to Encode: ");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = '\0';
                encodeMessage(msg);
                break;

            case 2:
                printf("\nEnter Message to Decode: ");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = '\0';
                decodeMessage(msg);
                break;

            case 3:
                printf("\nThankYou!\n");
                return 0;

            default:
                printf("\n Invalid Choice! Please try again.\n");
        }
    }
}
