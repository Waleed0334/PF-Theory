#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    int popularity;
    int lastUsed;  // Used to find Least Recently Used (LRU)
} Book;

int main() {
    int capacity, Q;
    printf("Enter capacity and Q:\n");
    scanf("%d %d", &capacity, &Q);

    Book shelf[100];
    int count = 0;
    int time = 0;

    for (int k = 0; k < Q; k++) {    // MAIN LOOP USING FOR
        char op[10];
        printf("enter operation:\n");
        scanf("%s", op);

        //        ADD OPERATION
        if (strcmp(op, "ADD") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            time++;

            int found = -1;

            // Find book if already exists
            for (int i = 0; i < count; i++) {
                if (shelf[i].id == x) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                // Update popularity and lastUsed
                shelf[found].popularity = y;
                shelf[found].lastUsed = time;
            } 
            else {
                // Shelf full → remove LRU
                if (count == capacity) {
                    int lruIndex = 0;

                    for (int i = 1; i < count; i++) {
                        if (shelf[i].lastUsed < shelf[lruIndex].lastUsed)
                            lruIndex = i;
                    }

                    // SHIFT LEFT to remove LRU
                    for (int i = lruIndex; i < count - 1; i++) {
                        shelf[i] = shelf[i + 1];
                    }

                    count--;
                }

                // Add new book
                shelf[count].id = x;
                shelf[count].popularity = y;
                shelf[count].lastUsed = time;
                count++;
            }
        }
        //      ACCESS OPERATION
        else if (strcmp(op, "ACCESS") == 0) {
            int x;
            scanf("%d", &x);
            time++;

            int found = -1;

            for (int i = 0; i < count; i++) {
                if (shelf[i].id == x) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                printf("-1\n");
            } 
            else {
                shelf[found].lastUsed = time;  // update last access time
                printf("%d\n", shelf[found].popularity);
            }
        }
    }

    return 0;
}
