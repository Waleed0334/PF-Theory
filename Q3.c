#include <stdio.h>
#define ROWS 3
#define COLS 3

void updateSector(int grid[ROWS][COLS], int row, int col, int bit, int value) {
    if (value == 1){
        grid[row][col] |= (1 << bit);}
    else{
        grid[row][col] &= ~(1 << bit);}
}

void querySector(int grid[ROWS][COLS], int row, int col) {
    int status = grid[row][col];
    printf("\nSector [%d][%d] Status:\n", row, col);
    printf("Power: %s\n", (status & (1 << 0)) ? "ON" : "OFF");
    printf("Overload: %s\n", (status & (1 << 1)) ? "YES" : "NO");
    printf("Maintenance: %s\n", (status & (1 << 2)) ? "REQUIRED" : "NOT REQUIRED");
}

void runDiagnostic(int grid[ROWS][COLS]) {
    int overloadCount = 0, maintenanceCount = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] & (1 << 1)){
                overloadCount++;}
            if (grid[i][j] & (1 << 2)){
                maintenanceCount++;}
        }
    }
    printf("\n-------System Diagnostic Report------\n");
    printf("Overloaded Sectors: %d\n", overloadCount);
    printf("Maintenance Required: %d\n", maintenanceCount);
}

int main() {
    int grid[ROWS][COLS] = {0};
    int choice, row, col, bit, value;

    while (1) {
        printf("\n----------------------------------------------\n");
        printf("===== IESCO Grid Monitoring System =====\n");
        printf("-----------------------------------------------\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("-----------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter row (0-%d): ", ROWS - 1);
                scanf("%d", &row);
                printf("Enter col (0-%d): ", COLS - 1);
                scanf("%d", &col);
                printf("Enter bit number (0=Power, 1=Overload, 2=Maintenance): ");
                scanf("%d", &bit);
                printf("Enter value (1=Set, 0=Clear): ");
                scanf("%d", &value);
                updateSector(grid, row, col, bit, value);
                printf("Sector updated successfully!\n");
                break;
            case 2:
                printf("Enter row and column to query: ");
                scanf("%d %d", &row, &col);
                querySector(grid, row, col);
                break;
            case 3:
                runDiagnostic(grid);
                break;
            case 4:
                printf("Thank you!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
