#include <stdio.h>
#include <stdlib.h>

struct Node { int roll; struct Node *next; };
struct Node *head = NULL;

void display() {
    if (!head) { printf("List is empty\n"); return; }
    printf("List: ");
    for (struct Node *p = head; p; p = p->next) printf("%d -> ", p->roll);
    printf("NULL\n");
}

struct Node *newNode(int r) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->roll = r; n->next = NULL;
    return n;
}

void insertBegin(int r) {
    struct Node *n = newNode(r);
    n->next = head; head = n;
    display();
}

void insertEnd(int r) {
    struct Node *n = newNode(r);
    if (!head) head = n;
    else { struct Node *p = head; while (p->next) p = p->next; p->next = n; }
    display();
}

void search(int r) {
    int pos = 1;
    for (struct Node *p = head; p; p = p->next, pos++)
        if (p->roll == r) { printf("Roll %d found at position %d\n", r, pos); return; }
    printf("Roll number %d is not available\n", r);
}

void deleteRoll(int r) {
    struct Node *p = head, *prev = NULL;
    while (p && p->roll != r) { prev = p; p = p->next; }
    if (!p) { printf("Roll number %d is not available\n", r); return; }
    if (!prev) head = p->next; else prev->next = p->next;
    free(p);
    printf("Deleted %d\n", r);
    display();
}

int main() {
    int ch, r, n;
    printf("Enter number of initial roll numbers (creates list): ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Roll %d: ", i + 1); scanf("%d", &r);
        struct Node *nn = newNode(r);
        if (!head) head = nn;
        else { struct Node *p = head; while (p->next) p = p->next; p->next = nn; }
    }
    display();
    do {
        printf("\n1.Insert Begin 2.Insert End 3.Search 4.Delete 5.Display 6.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Roll: "); scanf("%d", &r); insertBegin(r); break;
            case 2: printf("Roll: "); scanf("%d", &r); insertEnd(r); break;
            case 3: printf("Roll: "); scanf("%d", &r); search(r); break;
            case 4: printf("Roll: "); scanf("%d", &r); deleteRoll(r); break;
            case 5: display(); break;
            case 6: break;
            default: printf("Invalid choice\n");
        }
    } while (ch != 6);
    return 0;
}
