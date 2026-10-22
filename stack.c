#include <stdio.h>
#include <string.h>

#define MAX 1000

char stack[MAX];
int idx[MAX];   // stores the position of each opening bracket
int top = -1;

void push(char c, int pos) {
    stack[++top] = c;
    idx[top] = pos;
}

char pop() {
    return stack[top--];
}

int isOpening(char c) {
    return c == '(' || c == '{' || c == '[';
}

int isClosing(char c) {
    return c == ')' || c == '}' || c == ']';
}

int matches(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int main() {
    char str[MAX];

    printf("Enter a string: ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';   // remove trailing newline

    top = -1;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        char c = str[i];

        if (isOpening(c)) {
            push(c, i);
        } else if (isClosing(c)) {
            if (top == -1) {
                printf("Not balanced: extra closing '%c' at index %d\n", c, i);
                return 0;
            }
            char open = stack[top];
            if (!matches(open, c)) {
                printf("Not balanced: '%c' at index %d does not match '%c' at index %d\n",
                       c, i, open, idx[top]);
                return 0;
            }
            pop();
        }
        // all other characters are ignored
    }

    if (top != -1) {
        printf("Not balanced: unclosed '%c' at index %d\n", stack[top], idx[top]);
    } else {
        printf("Balanced\n");
    }

    return 0;
}