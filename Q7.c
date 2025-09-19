#include <stdio.h>
int main() {
    int day;
    printf("Please enter a number between 1 and 7 to know the day of the week: ");
    scanf("%d", &day);
    if (day == 1) {
        printf(" it's Monday.\n");
    } else if (day == 2) {
        printf(" it's Tuesday.\n");
    } else if (day == 3) {
        printf(" it's Wednesday.\n");
    } else if (day == 4) {
        printf(" it's Thursday.\n");
    } else if (day == 5) {
        printf(" it's Friday.\n");
    } else if (day == 6) {
        printf(" it's Saturday.\n");
    } else if (day == 7) {
        printf(" it's Sunday.\n");
    } else {
        printf(" %d is not a valid input. Please enter a number between 1 and 7.\n", day);
    }
     return 0;
    }

