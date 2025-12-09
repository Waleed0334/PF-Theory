#include <stdio.h>

double calculation(double loan, double interest, int year) {
    double installment=30000;
    if (loan <= 0 || year == 0) {
        printf("There is no repayment amount.\n");
        return 0;
    }

    loan = loan + (loan * (interest / 100));
    
    double payment;
    if (installment > loan) {
    payment = loan;    
    } else {
    payment = installment; 
    }

    loan = loan - payment;   

    printf("Year %d: Remaining loan = %.2lf\n", year, loan);
        
    return payment + calculation(loan, interest, year - 1);
}

int main() {
    double loan, interest, repaymentAmount;
    int year;

    printf("Enter Year:\n");
    scanf("%d", &year);

    printf("Enter interest rate:\n");
    scanf("%lf", &interest);

    printf("Enter Loan:\n");
    scanf("%lf", &loan);

    repaymentAmount = calculation(loan, interest, year);

    printf("\nTotal repayment amount over %d years = %.2lf\n", year, repaymentAmount);

    return 0;
}
