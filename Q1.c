#include <stdio.h>
int main() {
    float limit = 5000;
    float transaction;
    char country[15];
    char answer;
    int transactionLimit = 1;
    printf("Enter country:\n");
    scanf("%s", country);    
    if ((country[0] == 'P'|| country[0] =='p') && country[1] == 'a' && country[2] == 'k' &&
        country[3] == 'i' && country[4] == 's' && country[5] == 't' &&
        country[6] == 'a' && country[7] == 'n' && country[8] == '\0') {        
    }    
    else if ((country[0] == 'U' || country[0] == 'u') && country[1] == 'a' && country[2] == 'e' && country[3] == '\0') {        
    }
    else {
        printf("Unusual Country\n");
        return 0;
    }    
    printf("Enter your transaction amount:\n");
    scanf("%f", &transaction);
    if (transaction > limit) {
        printf("Limit Exceeded!\n");
        return 0;
    }    
    printf("Do you want more transactions? (y/n):\n");
    scanf(" %c", &answer);
    if (answer == 'y' || answer == 'Y') {      
        printf("Enter your transaction amount:\n");
        scanf("%f", &transaction);
        if (transaction > limit) {
            printf("Limit Exceeded!\n");
            return 0;
        }     
        printf("Do you want more transactions? (y/n):\n");
        scanf(" %c", &answer);
        if (answer == 'y' || answer == 'Y') {          
            printf("Enter your transaction amount:\n");
            scanf("%f", &transaction);
            if (transaction > limit) {
                printf("Limit Exceeded!\n");
                return 0;
            }            
            printf("Do you want more transactions? (y/n):\n");
            scanf(" %c", &answer);
            if (answer == 'y' || answer == 'Y') {              
                printf("Too many transactions in the same hour\n");
                return 0;
            } else {
                printf("Thank you\n");
                return 0;
            }
        } else {
            printf("Thank you\n");
            return 0;
        }
    } else {
        printf("Thank you\n");
        return 0;
    }
    return 0;
}
