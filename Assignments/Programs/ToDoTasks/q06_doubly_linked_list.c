#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Page { char url[50]; struct Page *prev, *next; };
struct Page *head = NULL, *tail = NULL, *current = NULL;

void insertPage(char *url) {
    struct Page *n = (struct Page *)malloc(sizeof(struct Page));
    strcpy(n->url, url); n->prev = n->next = NULL;
    if (!head) head = tail = n;
    else { tail->next = n; n->prev = tail; tail = n; }
    current = n;
    printf("Visited: %s\n", url);
}

void forward() {
    if (!current) { printf("No pages visited\n"); return; }
    if (!current->next) { printf("End of history: cannot go forward\n"); return; }
    current = current->next;
    printf("Current page: %s\n", current->url);
}

void backward() {
    if (!current) { printf("No pages visited\n"); return; }
    if (!current->prev) { printf("Beginning of history: cannot go back\n"); return; }
    current = current->prev;
    printf("Current page: %s\n", current->url);
}

void deletePage(char *url) {
    struct Page *p = head;
    while (p && strcmp(p->url, url) != 0) p = p->next;
    if (!p) { printf("Page '%s' not found\n", url); return; }
    if (p->prev) p->prev->next = p->next; else head = p->next;
    if (p->next) p->next->prev = p->prev; else tail = p->prev;
    if (current == p) current = p->prev ? p->prev : p->next;
    free(p);
    printf("Deleted page: %s\n", url);
}

void displayForward() {
    if (!head) { printf("History is empty\n"); return; }
    printf("First to Last: ");
    for (struct Page *p = head; p; p = p->next) printf("%s%s ", p->url, p == current ? "*" : "");
    printf("\n");
}

void displayBackward() {
    if (!tail) { printf("History is empty\n"); return; }
    printf("Last to First: ");
    for (struct Page *p = tail; p; p = p->prev) printf("%s%s ", p->url, p == current ? "*" : "");
    printf("\n");
}

int main() {
    int ch; char url[50];
    do {
        printf("\n1.Insert 2.Forward 3.Backward 4.Delete 5.Show First-Last 6.Show Last-First 7.Exit\n(* marks current page)\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Page: "); scanf("%49s", url); insertPage(url); break;
            case 2: forward(); break;
            case 3: backward(); break;
            case 4: printf("Page: "); scanf("%49s", url); deletePage(url); break;
            case 5: displayForward(); break;
            case 6: displayBackward(); break;
            case 7: break;
            default: printf("Invalid choice\n");
        }
    } while (ch != 7);
    return 0;
}
