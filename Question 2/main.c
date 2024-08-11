#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int top;
    int arr[MAX];
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int is_empty(Stack *s) {
    return s->top == -1;
}

int is_full(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int val) {
    if (!is_full(s)) {
        s->arr[++(s->top)] = val;
    }
}

int pop(Stack *s) {
    if (!is_empty(s)) {
        return s->arr[(s->top)--];
    }
    return -1;  // Return -1 if the stack is empty
}

int peek(Stack *s) {
    if (!is_empty(s)) {
        return s->arr[s->top];
    }
    return -1;  // Return -1 if the stack is empty
}

void check_balanced_parentheses(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    Stack s;
    init(&s);
    char ch;
    int line = 1;
    int error_found = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line++;
        } else if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, line);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            int top_line = pop(&s);
            if (top_line == -1) {
                printf("Error: Unmatched closing parenthesis '%c' at line %d\n", ch, line);
                error_found = 1;
            }
        }
    }

    while (!is_empty(&s)) {
        int top_line = pop(&s);
        printf("Error: Unmatched opening parenthesis at line %d\n", top_line);
        error_found = 1;
    }

    if (!error_found) {
        printf("No errors found. Parentheses are balanced.\n");
    }

    fclose(file);
}

int main() {
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    check_balanced_parentheses(filename);

    return 0;
}
