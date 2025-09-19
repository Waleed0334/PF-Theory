#include <stdio.h>

int main() {
    int counts[10] = {0};  
    int number;

    while (1) {
        printf("Enter a one digit number (0-9): \n");
        int result = scanf("%d", &number);

        if (result != 1 || number < 0 || number > 9) {
            printf("program is stopped due to invalid input.\n");
            break;
        }

        counts[number]++;
    }
    printf("\nNumber :  Number of Occurrences\n");
    for (int i = 0; i < 10; i++) {
        if (counts[i] > 0) {
            printf("%-9d %d\n", i, counts[i]);
        }
    }
    return 0;
}
