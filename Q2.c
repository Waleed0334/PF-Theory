#include <stdio.h>

void customerInfo(char name[], char cnic[]) {
    printf("\nEnter Customer Name: ");
    scanf("%s", name);
    printf("Enter Customer CNIC: ");
    scanf("%s", cnic);
}

void displayInventory(int productCode[], int stock[], int price[], int size) {
    printf("\n---------- INVENTORY -----------\n");
    printf("Code\tStock\tPrice\n");
    for (int i = 0; i < size; i++) {
        printf("%03d\t%d\t%d\n", productCode[i], stock[i], price[i]);
    }
}

void addToCart(int productCode[], int stock[], int price[], int cartQty[], int size) {
    int code, qty;
    displayInventory(productCode, stock, price, size);
    printf("\nEnter Product Code to purchase: ");
    scanf("%d", &code);
    printf("Enter Quantity: ");
    scanf("%d", &qty);
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (productCode[i] == code) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Invalid Product Code!\n");
        return;
    }
    if (stock[index] >= qty) {
        cartQty[index] += qty;
        stock[index] -= qty;
        printf("Added to cart successfully!\n");
    } else {
        printf("Sorry! Only %d items left in stock.\n", stock[index]);
    }
}

float displayTotalBill(int productCode[], int price[], int cartQty[], int size) {
    float total = 0;
    printf("\n------ CART BILL ------\n");
    printf("Code\tQty\tPrice\tTotal\n");
    for (int i = 0; i < size; i++) {
        if (cartQty[i] > 0) {
            int itemTotal = cartQty[i] * price[i];
            printf("%03d\t%d\t%d\t%d\n", productCode[i], cartQty[i], price[i], itemTotal);
            total += itemTotal;
        }
    }
    printf("----------------------\n");
    printf("Total Amount: %.2f\n", total);
    return total;
}

void showInvoice(char name[], char cnic[], int productCode[], int price[], int cartQty[], int size) {
    char promo[20];
    float total = displayTotalBill(productCode, price, cartQty, size);
    float discount = 0;
    printf("\n=========== INVOICE ===========\n");
    printf("Customer Name : %s\n", name);
    printf("Customer CNIC : %s\n", cnic);
    printf("\nEnter Promo Code: ");
    scanf("%s", promo);
    if ((promo[0] == 'E' || promo[0] == 'e') && (promo[1] == 'I' || promo[1] == 'i')  && (promo[2] == 'D' ||promo[2] == 'd') &&
        promo[3] == '2' && promo[4] == '0' && promo[5] == '2' &&
        promo[6] == '5' && promo[7] == '\0') {
        discount = total * 0.25;
        printf("Promo Applied (25%% OFF)\n");
    } else {
        printf("No valid promo applied.\n");
    }
    printf("Discount: %.2f\n", discount);
    printf("Final Amount: %.2f\n", total - discount);
    printf("================================\n");
}

int main() {
    int productCode[4] = {1, 2, 3, 4};
    int stock[4] = {50, 10, 20, 8};
    int price[4] = {100, 200, 300, 150};
    int cartQty[4] = {0, 0, 0, 0};
    char customerName[50];
    char customerCNIC[20];
    int choice;
    int size = 4;
    printf("=========== SUPERMARKET SYSTEM ===========\n");
    printf("-------------------------------------------\n");
    while (1) {
        printf("\n1. Enter Customer Info\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                customerInfo(customerName, customerCNIC);
                break;
            case 2:
                displayInventory(productCode, stock, price, size);
                break;
            case 3:
                addToCart(productCode, stock, price, cartQty, size);
                break;
            case 4:
                displayTotalBill(productCode, price, cartQty, size);
                break;
            case 5:
                showInvoice(customerName, customerCNIC, productCode, price, cartQty, size);
                break;
            case 6:
                printf("Thank you!\n");
                return 0;
            default:
                printf("Invalid Option!\n");
        }
    }
}