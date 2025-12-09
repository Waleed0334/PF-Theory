#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DB_FILENAME "members.dat"

typedef struct {
    int studentID;
    char fullName[100];       
    char batch[32];           // "CS", "SE", "Cyber Security", "AI"
    char membership[8];       // "IEEE" or "ACM"
    char regDate[11];         // registration date
    char dob[11];             // birth date
    char interest[8];         // "IEEE", "ACM", or "Both"
} Student;

typedef struct {
    Student *arr;
    size_t count;
    size_t capacity;
} StudentDB;

static StudentDB gdb = { NULL, 0, 0 };

static void fatal(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void ensure_capacity(StudentDB *db, size_t minCap) {
    if (db->capacity >= minCap) return;
    size_t newCap = (db->capacity == 0) ? 8 : db->capacity * 2;
    while (newCap < minCap) newCap *= 2;
    Student *tmp = realloc(db->arr, newCap * sizeof(Student));
    if (!tmp) fatal("realloc");
    db->arr = tmp;
    db->capacity = newCap;
}

int loadDatabase(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        if (errno == ENOENT) { 
            gdb.arr = NULL;
            gdb.count = gdb.capacity = 0;
            return 0;
        } else {
            fprintf(stderr, "Error opening '%s' for reading: %s\n", filename, strerror(errno));
            return -1;
        }
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        fprintf(stderr, "fseek failed: %s\n", strerror(errno));
        fclose(f);
        return -1;
    }
    long sz = ftell(f);
    if (sz < 0) {
        fprintf(stderr, "ftell failed: %s\n", strerror(errno));
        fclose(f);
        return -1;
    }
    rewind(f);

    size_t recordSize = sizeof(Student);
    if (sz % recordSize != 0) {
        fprintf(stderr, "Warning: file size is not a multiple of record size. File may be corrupted.\n");
    }

    size_t n = sz / recordSize;
    if (n == 0) {
        gdb.arr = NULL;
        gdb.count = gdb.capacity = 0;
        fclose(f);
        return 0;
    }

    ensure_capacity(&gdb, n);
    size_t read = fread(gdb.arr, recordSize, n, f);
    if (read != n) {
        fprintf(stderr, "Error reading records from file: expected %zu got %zu\n", n, read);
        fclose(f);
        return -1;
    }
    gdb.count = n;
    fclose(f);
    return 0;
}

int saveDatabase(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "Error opening '%s' for writing: %s\n", filename, strerror(errno));
        return -1;
    }
    if (gdb.count > 0) {
        size_t written = fwrite(gdb.arr, sizeof(Student), gdb.count, f);
        if (written != gdb.count) {
            fprintf(stderr, "Error writing to file: wrote %zu of %zu records\n", written, gdb.count);
            fclose(f);
            return -1;
        }
    }
    fclose(f);
    return 0;
}

int addStudentToFile(const Student *s, const char *filename) {
    FILE *f = fopen(filename, "ab");
    if (!f) {
        fprintf(stderr, "Error opening '%s' for appending: %s\n", filename, strerror(errno));
        return -1;
    }
    size_t written = fwrite(s, sizeof(Student), 1, f);
    if (written != 1) {
        fprintf(stderr, "Error appending record to file\n");
        fclose(f);
        return -1;
    }
    fclose(f);
    return 0;
}

int findStudentIndex(int studentID) {
    for (size_t i = 0; i < gdb.count; ++i) {
        if (gdb.arr[i].studentID == studentID) return (int)i;
    }
    return -1;
}

int validBatch(const char *b) {
    if (strcmp(b, "CS") == 0) return 1;
    if (strcmp(b, "SE") == 0) return 1;
    if (strcmp(b, "Cyber Security") == 0) return 1;
    if (strcmp(b, "AI") == 0) return 1;
    return 0;
}
int validMembership(const char *m) {
    if (strcmp(m, "IEEE") == 0) return 1;
    if (strcmp(m, "ACM") == 0) return 1;
    return 0;
}
int validInterest(const char *i) {
    if (strcmp(i, "IEEE") == 0) return 1;
    if (strcmp(i, "ACM") == 0) return 1;
    if (strcmp(i, "Both") == 0) return 1;
    return 0;
}

void chomp(char *s) {
    size_t L = strlen(s);
    if (L == 0) return;
    if (s[L-1] == '\n') s[L-1] = '\0';
}

void read_line(char *buf, size_t size) {
    if (fgets(buf, (int)size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    chomp(buf);
}

Student inputStudent(void) {
    Student s;
    char tmp[256];

    printf("Enter Student ID (integer): ");
    while (1) {
        if (!fgets(tmp, sizeof(tmp), stdin)) { tmp[0] = '\0'; }
        if (sscanf(tmp, "%d", &s.studentID) == 1) break;
        printf("Invalid ID. Enter an integer: ");
    }

    printf("Enter Full Name (max 99 chars): ");
    read_line(s.fullName, sizeof(s.fullName));

    printf("Enter Batch (CS / SE / Cyber Security / AI): ");
    while (1) {
        read_line(s.batch, sizeof(s.batch));
        if (validBatch(s.batch)) break;
        printf("Invalid batch. Allowed: CS, SE, Cyber Security, AI: ");
    }

    printf("Enter Membership Type (IEEE / ACM): ");
    while (1) {
        read_line(s.membership, sizeof(s.membership));
        if (validMembership(s.membership)) break;
        printf("Invalid membership. Allowed: IEEE, ACM: ");
    }

    printf("Enter Registration Date (YYYY-MM-DD): ");
    read_line(s.regDate, sizeof(s.regDate));

    printf("Enter Date of Birth (YYYY-MM-DD): ");
    read_line(s.dob, sizeof(s.dob));

    printf("Enter Interest (IEEE / ACM / Both): ");
    while (1) {
        read_line(s.interest, sizeof(s.interest));
        if (validInterest(s.interest)) break;
        printf("Invalid interest. Allowed: IEEE, ACM, Both: ");
    }

    return s;
}

int addStudent(const Student *s, const char *filename) {
    if (findStudentIndex(s->studentID) != -1) {
        fprintf(stderr, "Error: Student ID %d already exists. Aborting add.\n", s->studentID);
        return -1;
    }

    ensure_capacity(&gdb, gdb.count + 1);
    gdb.arr[gdb.count] = *s;
    gdb.count++;

    if (addStudentToFile(s, filename) != 0) {
        fprintf(stderr, "Error: failed to append new student to file. Rolling back memory add.\n");
        gdb.count--;
        return -1;
    }
    return 0;
}

int updateStudent(int studentID) {
    int idx = findStudentIndex(studentID);
    if (idx == -1) {
        fprintf(stderr, "Student ID %d not found.\n", studentID);
        return -1;
    }

    Student *s = &gdb.arr[idx];
    printf("Updating student: %d - %s\n", s->studentID, s->fullName);
    printf("Current Batch: %s\n", s->batch);
    printf("Current Membership: %s\n", s->membership);

    char choice[8];
    printf("Change batch? (y/n): ");
    read_line(choice, sizeof(choice));
    if (choice[0] == 'y' || choice[0] == 'Y') {
        printf("Enter new Batch (CS / SE / Cyber Security / AI): ");
        while (1) {
            read_line(s->batch, sizeof(s->batch));
            if (validBatch(s->batch)) break;
            printf("Invalid batch. Try again: ");
        }
    }

    printf("Change membership? (y/n): ");
    read_line(choice, sizeof(choice));
    if (choice[0] == 'y' || choice[0] == 'Y') {
        printf("Enter new Membership (IEEE / ACM): ");
        while (1) {
            read_line(s->membership, sizeof(s->membership));
            if (validMembership(s->membership)) break;
            printf("Invalid membership. Try again: ");
        }
    }

    if (saveDatabase(DB_FILENAME) != 0) {
        fprintf(stderr, "Failed to save database after update.\n");
        return -1;
    }
    printf("Update successful and saved.\n");
    return 0;
}

int deleteStudent(int studentID) {
    int idx = findStudentIndex(studentID);
    if (idx == -1) {
        fprintf(stderr, "Student ID %d not found.\n", studentID);
        return -1;
    }

    if ((size_t)idx < gdb.count - 1) {
        memmove(&gdb.arr[idx], &gdb.arr[idx+1], (gdb.count - idx - 1) * sizeof(Student));
    }
    gdb.count--;

    if (saveDatabase(DB_FILENAME) != 0) {
        fprintf(stderr, "Failed to save database after deletion.\n");
        return -1;
    }
    printf("Deleted student %d and saved database.\n", studentID);
    return 0;
}

void displayAll(void) {
    if (gdb.count == 0) {
        printf("No registrations.\n");
        return;
    }
    printf("Total students: %zu\n", gdb.count);
    for (size_t i = 0; i < gdb.count; ++i) {
        Student *s = &gdb.arr[i];
        printf("ID: %d | Name: %s | Batch: %s | Membership: %s | Reg: %s | DOB: %s | Interest: %s\n",
               s->studentID, s->fullName, s->batch, s->membership, s->regDate, s->dob, s->interest);
    }
}

void batchReport(const char *batchFilter, const char *interestFilter) {
    size_t found = 0;
    for (size_t i = 0; i < gdb.count; ++i) {
        Student *s = &gdb.arr[i];
        if (strcmp(batchFilter, "ALL") != 0) {
            if (strcmp(s->batch, batchFilter) != 0) continue;
        }
        if (strcmp(interestFilter, "ALL") != 0) {
            if (strcmp(interestFilter, "Both") == 0) {
                if (strcmp(s->interest, "Both") != 0) continue;
            } else {
                if (strcmp(s->interest, interestFilter) != 0 && strcmp(s->interest, "Both") != 0) continue;
            }
        }
        if (found == 0) {
            printf("Report for batch='%s' interest='%s'\n", batchFilter, interestFilter);
        }
        printf("ID: %d | Name: %s | Membership: %s | Reg: %s | DOB: %s | Interest: %s\n",
               s->studentID, s->fullName, s->membership, s->regDate, s->dob, s->interest);
        found++;
    }
    if (found == 0) printf("No matching records.\n");
}

void freeAll(void) {
    free(gdb.arr);
    gdb.arr = NULL;
    gdb.count = gdb.capacity = 0;
}

/* Menu-driven  */
void menu(void) {
    char cmd[64];
    while (1) {
        printf("\n--- Membership Manager Menu ---\n");
        printf("1. Register new student\n");
        printf("2. Update student (batch/membership)\n");
        printf("3. Delete student\n");
        printf("4. View all registrations\n");
        printf("5. Generate batch-wise report\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        int choice = atoi(cmd);

        if (choice == 1) {
            Student s = inputStudent();
            if (addStudent(&s, DB_FILENAME) == 0) {
                printf("Student added and appended to file.\n");
            } else {
                printf("Failed to add student.\n");
            }
        }
        else if (choice == 2) {
            printf("Enter Student ID to update: ");
            if (!fgets(cmd, sizeof(cmd), stdin)) continue;
            int id = atoi(cmd);
            updateStudent(id);
        }
        else if (choice == 3) {
            printf("Enter Student ID to delete: ");
            if (!fgets(cmd, sizeof(cmd), stdin)) continue;
            int id = atoi(cmd);
            deleteStudent(id);
        }
        else if (choice == 4) {
            displayAll();
        }
        else if (choice == 5) {
            char batchFilter[64], interestFilter[16];
            printf("Enter batch to filter (CS / SE / Cyber Security / AI / ALL): ");
            read_line(batchFilter, sizeof(batchFilter));
            if (strcmp(batchFilter, "") == 0) strcpy(batchFilter, "ALL");
            printf("Enter interest to filter (IEEE / ACM / Both / ALL): ");
            read_line(interestFilter, sizeof(interestFilter));
            if (strcmp(interestFilter, "") == 0) strcpy(interestFilter, "ALL");
            batchReport(batchFilter, interestFilter);
        }
        else if (choice == 6) {
            // Save entire DB before exit to ensure consistency
            if (saveDatabase(DB_FILENAME) != 0) {
                fprintf(stderr, "Warning: failed to save database prior to exit.\n");
            }
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }
}

int main(void) {
    if (loadDatabase(DB_FILENAME) != 0) {
        fprintf(stderr, "Failed to load database. Starting with an empty DB.\n");
    } else {
        printf("Loaded %zu records from '%s'.\n", gdb.count, DB_FILENAME);
    }

    menu();

    freeAll();
    return 0;
}
