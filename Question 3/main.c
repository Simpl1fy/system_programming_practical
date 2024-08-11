#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100
#define MAX_LABEL_LEN 50
#define MAX_LINE_LEN 100

typedef struct {
    char label[MAX_LABEL_LEN];
    int address;
} Symbol;

typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

void init_symbol_table(SymbolTable *table) {
    table->count = 0;
}

int add_symbol(SymbolTable *table, const char *label, int address) {
    if (table->count >= MAX_SYMBOLS) {
        printf("Error: Symbol table overflow\n");
        return -1;
    }

    strcpy(table->symbols[table->count].label, label);
    table->symbols[table->count].address = address;
    table->count++;

    return 0;
}

int find_symbol(SymbolTable *table, const char *label) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].label, label) == 0) {
            return table->symbols[i].address;
        }
    }
    return -1;
}

void print_symbol_table(SymbolTable *table) {
    printf("\nSymbol Table:\n");
    printf("Label\tAddress\n");
    printf("-----------------\n");
    for (int i = 0; i < table->count; i++) {
        printf("%s\t%d\n", table->symbols[i].label, table->symbols[i].address);
    }
}

void create_symbol_table(const char *filename, SymbolTable *table) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[MAX_LINE_LEN];
    int address = 0;

    while (fgets(line, sizeof(line), file)) {
        char *label_end = strchr(line, ':');
        if (label_end != NULL) {
            char label[MAX_LABEL_LEN];
            strncpy(label, line, label_end - line);
            label[label_end - line] = '\0';

            add_symbol(table, label, address);
        }

        address++;
    }

    fclose(file);
}

int main() {
    char filename[100];
    SymbolTable table;

    init_symbol_table(&table);

    printf("Enter the assembly program filename: ");
    scanf("%s", filename);

    create_symbol_table(filename, &table);

    print_symbol_table(&table);

    return 0;
}
