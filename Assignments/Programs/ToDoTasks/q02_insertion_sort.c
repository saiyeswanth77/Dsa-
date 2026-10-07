#include <stdio.h>

void display(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int n, a[100], shifts = 0;
    printf("Enter number of marks: ");
    scanf("%d", &n);
    printf("Enter %d marks:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
            shifts++;
        }
        a[j + 1] = key;
        printf("After pass %d: ", i);
        display(a, n);
    }
    printf("\nFinal sorted list: ");
    display(a, n);
    printf("Total number of shifts: %d\n", shifts);
    return 0;
}
