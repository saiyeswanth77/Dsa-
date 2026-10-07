#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
char peek() { return stack[top]; }
int isEmpty() { return top == -1; }

int prec(char c) {
    switch (c) {
        case '^': return 3;
        case '*': case '/': return 2;
        case '+': case '-': return 1;
    }
    return 0;
}
int rightAssoc(char c) { return c == '^'; }

int main() {
    char infix[MAX], postfix[MAX];
    int k = 0;
    printf("Enter infix expression (no spaces): ");
    scanf("%s", infix);

    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (!isEmpty() && peek() != '(') postfix[k++] = pop();
            if (isEmpty()) { printf("Error: unbalanced parentheses\n"); return 1; }
            pop(); /* discard '(' */
        } else if (strchr("+-*/^", c)) {
            while (!isEmpty() && peek() != '(' &&
                   (prec(peek()) > prec(c) ||
                   (prec(peek()) == prec(c) && !rightAssoc(c))))
                postfix[k++] = pop();
            push(c);
        } else {
            printf("Error: invalid character '%c'\n", c);
            return 1;
        }
    }
    while (!isEmpty()) {
        if (peek() == '(') { printf("Error: unbalanced parentheses\n"); return 1; }
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
