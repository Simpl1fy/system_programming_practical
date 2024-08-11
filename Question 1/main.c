#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINES_PER_PAGE 20

void display_file_page_wise(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[256];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        line_count++;

        if (line_count % LINES_PER_PAGE == 0) {
            printf("\n--Press Enter to continue--\n");
            getchar();
        }
    }

    fclose(file);
}

void count_vowels_chars_lines(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    int vowels = 0, characters = 0, lines = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }

        ch = tolower(ch);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            vowels++;
        }
    }

    fclose(file);

    printf("Vowels: %d\n", vowels);
    printf("Characters: %d\n", characters);
    printf("Lines: %d\n", lines);
}

void copy_file(char *source, char *destination) {
    FILE *src = fopen(source, "r");
    if (src == NULL) {
        printf("Error: Could not open source file %s\n", source);
        return;
    }

    FILE *dest = fopen(destination, "w");
    if (dest == NULL) {
        printf("Error: Could not open destination file %s\n", destination);
        fclose(src);
        return;
    }

    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully from %s to %s\n", source, destination);
}

int main() {
    int choice;
    char filename[100], dest[100];

    do {
        printf("\nMenu:\n");
        printf("1. Display contents of a file (page-wise)\n");
        printf("2. Count vowels, characters, and lines in a file\n");
        printf("3. Copy a file\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the filename: ");
                scanf("%s", filename);
                display_file_page_wise(filename);
                break;

            case 2:
                printf("Enter the filename: ");
                scanf("%s", filename);
                count_vowels_chars_lines(filename);
                break;

            case 3:
                printf("Enter the source filename: ");
                scanf("%s", filename);
                printf("Enter the destination filename: ");
                scanf("%s", dest);
                copy_file(filename, dest);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
