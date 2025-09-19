#include <stdio.h>
int main() {
    int C1,C2,C3,C4,C5;
    printf("Enter value of card : \n");
    scanf("%d %d %d %d %d",&C1,&C2,&C3,&C4,&C5);
    if ((C1 < 1 || C1 > 13) || (C2 < 1 || C2 > 13) || (C3 < 1 || C3 > 13) ||
        (C4 < 1 || C4 > 13) || (C5 < 1 || C5 > 13))
    {
        printf(" card number doesnot exsist!");
    }else{
        if ((C1 == C2 && C2 == C3 && C4 == C5) ||
            (C1 == C2 && C2 == C4 && C3 == C5) ||
            (C1 == C2 && C2 == C5 && C3 == C4) ||
            (C1 == C3 && C3 == C4 && C2 == C5) ||
            (C1 == C3 && C3 == C5 && C2 == C4) ||
            (C1 == C4 && C4 == C5 && C2 == C3) ||
            (C2 == C3 && C3 == C4 && C1 == C5) ||
            (C2 == C3 && C3 == C5 && C1 == C4) ||
            (C2 == C4 && C4 == C5 && C1 == C3) ||
            (C3 == C4 && C4 == C5 && C1 == C2)) { 
                 printf("house full"); 
            }
        else{
            printf("House Not Full");
        }
    }
    return 0;
}
