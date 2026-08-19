/* EX.NO: 1 - Symbol Table Implementation
   AIM: Develop a lexical analyzer to recognize tokens and create a symbol table */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct table {
    char var[10];
    int value;
} tbl[20];

int i, j, n;

void create();
void modify();
int search(char variable[], int n);
void insert();
void display();

int main() {
    int ch, result = 0;
    char v[10];
    do {
        printf("\nEnter your choice\n1.Create\n2.Insert\n3.Modify\n4.Search\n5.Display\n6.Exit: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: create(); break;
            case 2: insert(); break;
            case 3: modify(); break;
            case 4:
                printf("Enter the variable to search: ");
                scanf("%s", v);
                result = search(v, n);
                if (result == 0)
                    printf("Variable not found in table\n");
                else
                    printf("Location: %d, Value of %s is %d\n", result, tbl[result].var, tbl[result].value);
                break;
            case 5: display(); break;
            case 6: exit(0);
        }
    } while (ch != 6);
    return 0;
}

void create() {
    printf("Enter number of entries: ");
    scanf("%d", &n);
    printf("Enter variable and value:\n");
    for (i = 1; i <= n; i++) {
        scanf("%s %d", tbl[i].var, &tbl[i].value);
        if (tbl[i].var[0] >= '0' && tbl[i].var[0] <= '9') {
            printf("Variable must start with a letter. Re-enter:\n");
            i--;
            continue;
        }
        for (j = 1; j < i; j++) {
            if (strcmp(tbl[i].var, tbl[j].var) == 0) {
                printf("Variable already exists. Re-enter:\n");
                scanf("%s %d", tbl[i].var, &tbl[i].value);
                j = 0;
            }
        }
    }
    printf("Table created:\n");
    display();
}

void insert() {
    if (n >= 20) { printf("Table full!\n"); return; }
    n++;
    printf("Enter variable and value: ");
    scanf("%s %d", tbl[n].var, &tbl[n].value);
    printf("After insertion:\n");
    display();
}

void modify() {
    char variable[10];
    int result;
    printf("Enter variable to modify: ");
    scanf("%s", variable);
    result = search(variable, n);
    if (result == 0)
        printf("%s not found\n", variable);
    else {
        printf("Current value: %d\nEnter new variable and value: ", tbl[result].value);
        scanf("%s %d", tbl[result].var, &tbl[result].value);
        printf("After modification:\n");
        display();
    }
}

int search(char variable[], int n) {
    for (i = 1; i <= n; i++)
        if (strcmp(tbl[i].var, variable) == 0)
            return i;
    return 0;
}

void display() {
    printf("VARIABLE\tVALUE\n");
    for (i = 1; i <= n; i++)
        printf("%s\t\t%d\n", tbl[i].var, tbl[i].value);
}
