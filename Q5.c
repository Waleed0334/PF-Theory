#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 4   

typedef struct {
    char **lines;     // dynamic array of pointers to lines
    size_t count;     // number of stored lines
    size_t capacity;  // allocated capacity for the lines array
} Editor;

static void fatal_alloc(const char *msg) {
    perror(msg);
    fprintf(stderr, "Fatal: memory allocation failed. Exiting.\n");
    exit(EXIT_FAILURE);
}

char *read_line_stdin(void) {
    size_t bufsize = 80;
    size_t len = 0;
    char *buf = malloc(bufsize);
    if (!buf) fatal_alloc("malloc");

    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\r') continue; 
        if (c == '\n') break;

        if (len + 1 >= bufsize) {
            bufsize *= 2;
            char *tmp = realloc(buf, bufsize);
            if (!tmp) {
                free(buf);
                fatal_alloc("realloc");
            }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }

    if (c == EOF && len == 0) {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';

    char *exact = malloc(len + 1);
    if (!exact) {
        free(buf);
        fatal_alloc("malloc");
    }
    memcpy(exact, buf, len + 1);
    free(buf);
    return exact;
}

char *read_line_file(FILE *f) {
    size_t bufsize = 128;
    size_t len = 0;
    char *buf = malloc(bufsize);
    if (!buf) fatal_alloc("malloc");

    int c;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\r') continue;
        if (c == '\n') break;
        if (len + 1 >= bufsize) {
            bufsize *= 2;
            char *tmp = realloc(buf, bufsize);
            if (!tmp) {
                free(buf);
                fatal_alloc("realloc");
            }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }

    if (c == EOF && len == 0) {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    char *exact = malloc(len + 1);
    if (!exact) {
        free(buf);
        fatal_alloc("malloc");
    }
    memcpy(exact, buf, len + 1);
    free(buf);
    return exact;
}

void initEditor(Editor *ed) {
    ed->capacity = INITIAL_CAPACITY;
    ed->count = 0;
    ed->lines = malloc(ed->capacity * sizeof(char*));
    if (!ed->lines) fatal_alloc("malloc");
}

void freeAll(Editor *ed) {
    if (!ed->lines) return;
    for (size_t i = 0; i < ed->count; ++i) {
        free(ed->lines[i]);
    }
    free(ed->lines);
    ed->lines = NULL;
    ed->count = ed->capacity = 0;
}

void ensureCapacity(Editor *ed, size_t minCapacity) {
    if (ed->capacity >= minCapacity) return;
    size_t newCap = ed->capacity ? ed->capacity : 1;
    while (newCap < minCapacity) newCap *= 2;
    char **tmp = realloc(ed->lines, newCap * sizeof(char*));
    if (!tmp) fatal_alloc("realloc");
    ed->lines = tmp;
    ed->capacity = newCap;
}

void insertLine(Editor *ed, size_t index, const char *text) {
    if (index > ed->count) {
        fprintf(stderr, "insertLine: invalid index %zu (count=%zu)\n", index, ed->count);
        return;
    }

    ensureCapacity(ed, ed->count + 1);

    if (index < ed->count) {
        memmove(&ed->lines[index + 1], &ed->lines[index], (ed->count - index) * sizeof(char*));
    }

    size_t len = strlen(text);
    char *copy = malloc(len + 1);
    if (!copy) fatal_alloc("malloc");
    memcpy(copy, text, len + 1);

    ed->lines[index] = copy;
    ed->count++;
}

void deleteLine(Editor *ed, size_t index) {
    if (index >= ed->count) {
        fprintf(stderr, "deleteLine: invalid index %zu (count=%zu)\n", index, ed->count);
        return;
    }
    free(ed->lines[index]);
    if (index + 1 < ed->count) {
        memmove(&ed->lines[index], &ed->lines[index + 1], (ed->count - index - 1) * sizeof(char*));
    }
    ed->count--;
}

void printAllLines(Editor *ed) {
    printf("----- Buffer (%zu lines) -----\n", ed->count);
    for (size_t i = 0; i < ed->count; ++i) {
        printf("%zu: %s\n", i + 1, ed->lines[i]);
    }
    printf("-----------------------------\n");
}

void shrinkToFit(Editor *ed) {
    if (ed->count == ed->capacity) return; 
    if (ed->count == 0) {
    
        free(ed->lines);
        ed->lines = malloc(INITIAL_CAPACITY * sizeof(char*));
        if (!ed->lines) fatal_alloc("malloc");
        ed->capacity = INITIAL_CAPACITY;
        return;
    }
    char **tmp = realloc(ed->lines, ed->count * sizeof(char*));
    if (!tmp) fatal_alloc("realloc");
    ed->lines = tmp;
    ed->capacity = ed->count;
}
void appendLine(Editor *ed, const char *text) {
    insertLine(ed, ed->count, text);
}

int saveToFile(Editor *ed, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Error opening file '%s' for writing: %s\n", filename, strerror(errno));
        return -1;
    }
    for (size_t i = 0; i < ed->count; ++i) {
        if (fprintf(f, "%s\n", ed->lines[i]) < 0) {
            fprintf(stderr, "Error writing to file '%s'\n", filename);
            fclose(f);
            return -1;
        }
    }
    fclose(f);
    return 0;
}

int loadFromFile(Editor *ed, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error opening file '%s' for reading: %s\n", filename, strerror(errno));
        return -1;
    }

    freeAll(ed);
    initEditor(ed);

    char *line;
    while ((line = read_line_file(f)) != NULL) {
        appendLine(ed, line);
        free(line); 
    }

    fclose(f);
    return 0;
}
void printHelp(void) {
    printf("Commands:\n");
    printf("  a       : append a line (type line then Enter)\n");
    printf("  i idx   : insert a line at position idx (1-based). then type line\n");
    printf("  d idx   : delete line at position idx (1-based)\n");
    printf("  p       : print all lines\n");
    printf("  s name  : save to file 'name'\n");
    printf("  l name  : load from file 'name'\n");
    printf("  r       : shrinkToFit (release unused memory)\n");
    printf("  h       : help\n");
    printf("  q       : quit\n");
}

int main(void) {
    Editor ed;
    initEditor(&ed);

    printf("Minimal Line Editor (demo). Initial capacity = %d\n", INITIAL_CAPACITY);
    printHelp();

    char cmd[64];
    while (1) {
        printf("\n> ");
        if (!fgets(cmd, sizeof(cmd), stdin)) break; 
        // strip trailing newline
        size_t L = strlen(cmd);
        if (L > 0 && cmd[L-1] == '\n') cmd[L-1] = '\0';

        if (strcmp(cmd, "") == 0) continue;

        if (strcmp(cmd, "a") == 0) {
            printf("Type line: ");
            char *line = read_line_stdin();
            if (!line) {
                printf("(no input)\n");
                continue;
            }
            appendLine(&ed, line);
            free(line);
            printf("Appended. count=%zu cap=%zu\n", ed.count, ed.capacity);
        }
        else if (cmd[0] == 'i' && (cmd[1] == ' ' || cmd[1] == '\t')) {
            int idx = atoi(cmd+1);
            if (idx < 1 || (size_t)idx > ed.count + 1) {
                printf("Invalid index. Valid range: 1..%zu\n", ed.count + 1);
                continue;
            }
            printf("Type line for insertion at %d: ", idx);
            char *line = read_line_stdin();
            if (!line) { printf("(no input)\n"); continue; }
            insertLine(&ed, (size_t)idx - 1, line);
            free(line);
            printf("Inserted. count=%zu cap=%zu\n", ed.count, ed.capacity);
        }
        else if (cmd[0] == 'd' && (cmd[1] == ' ' || cmd[1] == '\t')) {
            int idx = atoi(cmd+1);
            if (idx < 1 || (size_t)idx > ed.count) {
                printf("Invalid index. Valid range: 1..%zu\n", ed.count);
                continue;
            }
            deleteLine(&ed, (size_t)idx - 1);
            printf("Deleted. count=%zu cap=%zu\n", ed.count, ed.capacity);
        }
        else if (strcmp(cmd, "p") == 0) {
            printAllLines(&ed);
        }
        else if (cmd[0] == 's' && (cmd[1] == ' ' || cmd[1] == '\t')) {
            char *name = cmd+1;
            while (*name==' '||*name=='\t') name++;
            if (*name=='\0') { printf("No filename given.\n"); continue; }
            if (saveToFile(&ed, name) == 0) printf("Saved to '%s'\n", name);
        }
        else if (cmd[0] == 'l' && (cmd[1] == ' ' || cmd[1] == '\t')) {
            char *name = cmd+1;
            while (*name==' '||*name=='\t') name++;
            if (*name=='\0') { printf("No filename given.\n"); continue; }
            if (loadFromFile(&ed, name) == 0) printf("Loaded from '%s'. count=%zu cap=%zu\n", name, ed.count, ed.capacity);
        }
        else if (strcmp(cmd, "r") == 0) {
            shrinkToFit(&ed);
            printf("ShrinkToFit done. count=%zu cap=%zu\n", ed.count, ed.capacity);
        }
        else if (strcmp(cmd, "h") == 0) {
            printHelp();
        }
        else if (strcmp(cmd, "q") == 0) {
            break;
        }
        else {
            printf("Unknown command. 'h' for help.\n");
        }
    }

    freeAll(&ed);
    printf("Exiting. All memory freed.\n");
    return 0;
}
