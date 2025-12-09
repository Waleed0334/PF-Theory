#include <stdio.h>
#include <string.h>

void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *count) {
    if (*count >= 100) {
        printf("Inventory full! Cannot add more books.\n");
        return;
    }

    int newISBN;
    printf("Enter ISBN: ");
    scanf("%d", &newISBN);

    for (int i = 0; i < *count; i++) {
        if (isbns[i] == newISBN) {
            printf("Error: ISBN already exists!\n");
            return;
        }
    }

    isbns[*count] = newISBN;

    printf("Enter Title (single word): ");
    scanf("%s", titles[*count]);

    printf("Enter Price: ");
    scanf("%f", &prices[*count]);

    printf("Enter Quantity: ");
    scanf("%d", &quantities[*count]);

    (*count)++;   
    printf("Book added successfully!\n");
}

void processSale(int isbns[], int quantities[], int count) {
    int isbn, qty;
    printf("Enter ISBN to sell: ");
    scanf("%d", &isbn);

    for (int i = 0; i < count; i++) {
        if (isbns[i] == isbn) {

            printf("Enter copies sold: ");
            scanf("%d", &qty);

            if (quantities[i] < qty) {
                printf("Error: Not enough stock!\n");
            } else {
                quantities[i] -= qty;
                printf("Sale successful! Remaining stock: %d\n", quantities[i]);
            }
            return;
        }
    }

    printf("Book not found!\n");
}

void lowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int count) {
    printf("\n--- LOW STOCK BOOKS (Quantity < 5) ---\n");

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (quantities[i] < 5) {
            found = 1;
            printf("ISBN: %d | Title: %s | Price: %.2f | Qty: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
        }
    }

    if (!found)
        printf("No books with low stock.\n");
}

int main() {
    int isbns[100];
    int quantities[100];
    int count = 0;
    char titles[100][50];
    float prices[100];

    int choice;

    while (1) {
        printf("\n===== LIBERTY BOOKS MENU =====\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(isbns, titles, prices, quantities, &count);
                break;

            case 2:
                processSale(isbns, quantities, count);
                break;

            case 3:
                lowStockReport(isbns, titles, prices, quantities, count);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
