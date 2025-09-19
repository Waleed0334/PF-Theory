#include <stdio.h>

int main() {
    int age;
    char eyeTest, writtenTest, drivingTest, medicalCertificate;

    printf("Enter your age: ");
    scanf("%d", &age);

    if (age >= 18) {
        printf("Have you passed the eye test? (P/F): ");
        scanf(" %c", &eyeTest);

        if (eyeTest == 'P' || eyeTest == 'p') {
            printf("Have you passed the written test? (P/F): ");
            scanf(" %c", &writtenTest);

            if (writtenTest == 'P' || writtenTest == 'p') {
                printf("Have you passed the driving test? (P/F): ");
                scanf(" %c", &drivingTest);

                if (drivingTest == 'P' || drivingTest == 'p') {
                    
                    if (age > 60) {
                        printf("Do you have a medical fitness certificate? (Y/N): ");
                        scanf(" %c", &medicalCertificate);

                        if (medicalCertificate == 'Y' || medicalCertificate == 'y') {
                            printf("You are eligible for the license.\n");
                        } else {
                            printf("You are not eligible for the license.\n");
                        }
                    } else {
                        printf("You are eligible for the license.\n");
                    }
                } else {
                    printf("You are not eligible for the license.\n");
                }
            } else {
                printf("You need to retake the written test.\n");
            }
        } else {
            printf("You need a prescription for glasses.\n");
        }
    } else {
        printf("The applicant is not eligible.\n");
    }

    return 0;
}
