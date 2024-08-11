#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100
#define MAX_NAME_LEN 50
#define MAX_TYPE_LEN 10

typedef struct {
    char name[MAX_NAME_LEN];
    char type[MAX_TYPE_LEN];
    int scope;
} Symbol;

typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

void init_symbol_table(SymbolTable *table) {
    table->count = 0;
}

int add_symbol(SymbolTable *table, const char *name, const char *type, int scope) {
    if (table->count >= MAX_SYMBOLS) {
        printf("Error: Symbol table overflow\n");
        return -1;
    }

    strcpy(table->symbols[table->count].name, name);
    strcpy(table->symbols[table->count].type, type);
    table->symbols[table->count].scope = scope;
    table->count++;

    return 0;
}

int find_symbol(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void print_symbol_table(SymbolTable *table) {
    printf("\nSymbol Table:\n");
    printf("Name\tType\tScope\n");
    printf("---------------------------\n");
    for (int i = 0; i < table->count; i++) {
        printf("%s\t%s\t%d\n", table->symbols[i].name, table->symbols[i].type, table->symbols[i].scope);
    }
}

void parse_code(const char *filename, SymbolTable *table) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[256];
    int scope = 0;

    while (fgets(line, sizeof(line), file)) {
        char type[MAX_TYPE_LEN];
        char name[MAX_NAME_LEN];

        // Simple parsing for variable declarations like "int x;", "float y;", "char z;"
        if (sscanf(line, " %s %s ;", type, name) == 2) {
            // Remove any trailing semicolon from the name
            name[strcspn(name, ";")] = '\0';

            // Add the symbol to the table
            add_symbol(table, name, type, scope);
        }

        // Increase scope when entering a block
        if (strchr(line, '{')) {
            scope++;
        }

        // Decrease scope when leaving a block
        if (strchr(line, '}')) {
            scope--;
        }
    }

    fclose(file);
}

int main() {
    char filename[100];
    SymbolTable table;

    init_symbol_table(&table);

    printf("Enter the source code filename: ");
    scanf("%s", filename);

    parse_code(filename, &table);

    print_symbol_table(&table);

    return 0;
}
