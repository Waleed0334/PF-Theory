#include<stdio.h>
int main(){
    int day;
    printf("Enter a value in the range(1-7) to see the corresponding day name \n");
    scanf("%d",&day);
    switch (day)
    {
    case 1:
        printf("The day is Monday.");
        break;
    case 2:
        printf("The day is Tuesday.");
        break;
    case 3:
        printf("The day is Wednesday.");
        break;
    case 4:
        printf("The day is Thursday.");
        break;
    case 5:
        printf("The day is Friday.");
        break;
    case 6:
        printf("The day is Saturday.");
        break;
    case 7:
        printf("The day is Sunday.");
        break;
    default:
        printf("Not Found! Please enter in range (1-7).");
        break;
    }
    
    return 0;
}