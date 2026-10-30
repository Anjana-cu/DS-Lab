#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#define MAX 100
int parent[MAX], rank[MAX];

// Read one complete integer line. Return 0 for invalid input or end of file.
int readInt(int *value) {
    char line[128];
    char *end;
    long parsed;

    if (fgets(line, sizeof(line), stdin) == NULL)
        return 0;
    errno = 0;
    parsed = strtol(line, &end, 10);
    if (end == line)
        return 0;
    while (isspace((unsigned char)*end))
        end++;
    if (*end != '\0' || errno == ERANGE || parsed < INT_MIN || parsed > INT_MAX)
        return 0;
    *value = (int)parsed;
    return 1;
}

int readTwoInts(int *first, int *second) {
    char line[128];
    char *end;
    long a, b;

    if (fgets(line, sizeof(line), stdin) == NULL)
        return 0;
    errno = 0;
    a = strtol(line, &end, 10);
    if (end == line || errno == ERANGE)
        return 0;
    while (isspace((unsigned char)*end))
        end++;
    if (*end == '\0')
        return 0;
    errno = 0;
    b = strtol(end, &end, 10);
    if (errno == ERANGE)
        return 0;
    while (isspace((unsigned char)*end))
        end++;
    if (*end != '\0' || a < INT_MIN || a > INT_MAX || b < INT_MIN || b > INT_MAX)
        return 0;
    *first = (int)a;
    *second = (int)b;
    return 1;
}
// Initialize each element as a separate set
void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}
// Find with Path Compression
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}
// Union by Rank
void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) {
        printf("Already connected\n");
        return;
    }
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    }
    else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    }
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    printf("Union successful\n");
}
// Check connectivity
void connected(int x, int y) {
    if (find(x) == find(y))
        printf("Connected\n");
    else
        printf("Not Connected\n");
}
int main() {
    int n, choice, x, y;
    printf("Enter number of elements: ");
    if (!readInt(&n)) {
        printf("Invalid number of elements\n");
        return 1;
    }
    if (n < 1 || n > MAX) {
        printf("Invalid number of elements\n");
        return 1;
    }
    makeSet(n);
    while (1) {
        printf("\n1. Union");
        printf("\n2. Find");
        printf("\n3. Check Connectivity");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        if (!readInt(&choice)) {
            printf("Invalid choice\n");
            if (feof(stdin))
                break;
            continue;
        }

        if (choice == 4)
            break;
        if (choice < 1 || choice > 3) {
            printf("Invalid choice\n");
            continue;
        }
        if (choice == 2) {
            printf("Enter element: ");
            if (!readInt(&x)) {
                printf("Invalid element\n");
                if (feof(stdin))
                    break;
                continue;
            }
            if (x < 0 || x >= n) {
                printf("Invalid element\n");
                continue;
            }
            printf("Root = %d\n", find(x));
        }
        else {
            printf("Enter two elements: ");
            if (!readTwoInts(&x, &y)) {
                printf("Invalid elements\n");
                if (feof(stdin))
                    break;
                continue;
            }
            if (x < 0 || x >= n || y < 0 || y >= n) {
                printf("Invalid elements\n");
                continue;
            }
            if (choice == 1)
                unionSet(x, y);
            else
                connected(x, y);
        }
    }
    return 0;
}
