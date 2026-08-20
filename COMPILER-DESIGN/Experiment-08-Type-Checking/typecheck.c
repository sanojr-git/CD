/* EX.NO: 8 - Type Checking
   AIM: Implement type checking using a symbol table in C */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count = 0;
char key[4][12] = {"int", "float", "char", "double"};
char dstr[100][100], estr[100][100];
char resultvardt[100], arg1dt[100], arg2dt[100];

struct table {
    char var[10];
    char dt[10];
} tbl[20];

void entry(char *declaration);
int check(char t[]);
int search(char variable[]);
void typecheck(char *expression);

int main() {
    int i = 0, l = 0;
    printf("\nIMPLEMENTATION OF TYPE CHECKING\n");
    printf("\nDECLARATIONS (type END to finish):\n");
    while (1) {
        printf("\t");
        fgets(dstr[i], 100, stdin);
        dstr[i][strcspn(dstr[i], "\n")] = '\0';
        if (strcmp(dstr[i], "END") == 0) break;
        entry(dstr[i]);
        i++;
    }
    printf("\nEXPRESSIONS (type END to finish):\n");
    while (1) {
        printf("\t");
        fgets(estr[l], 100, stdin);
        estr[l][strcspn(estr[l], "\n")] = '\0';
        if (strcmp(estr[l], "END") == 0) break;
        l++;
    }
    printf("\nSEMANTIC ANALYZER (TYPE CHECKING):\n");
    for (i = 0; i < l; i++)
        typecheck(estr[i]);
    return 0;
}

void entry(char *declaration) {
    char datatype[10], varname[10];
    sscanf(declaration, "%s %[^;];", datatype, varname);
    if (!check(datatype)) { printf("Invalid datatype: %s\n", datatype); return; }
    if (search(varname) != -1) { printf("Variable '%s' already declared\n", varname); return; }
    strcpy(tbl[count].dt, datatype);
    strcpy(tbl[count].var, varname);
    count++;
}

int check(char t[]) {
    for (int i = 0; i < 4; i++)
        if (strcmp(key[i], t) == 0) return 1;
    return 0;
}

int search(char variable[]) {
    for (int i = 0; i < count; i++)
        if (strcmp(tbl[i].var, variable) == 0) return i;
    return -1;
}

void typecheck(char *expression) {
    char result[10], op1[10], op2[10]; char operator;
    sscanf(expression, "%s = %s %c %[^;];", result, op1, &operator, op2);
    int rIdx = search(result), o1Idx = search(op1), o2Idx = search(op2);
    if (rIdx == -1) { printf("Undefined variable: %s\n", result); return; }
    if (o1Idx == -1) { printf("Undefined variable: %s\n", op1); return; }
    if (o2Idx == -1) { printf("Undefined variable: %s\n", op2); return; }
    strcpy(resultvardt, tbl[rIdx].dt);
    strcpy(arg1dt, tbl[o1Idx].dt);
    strcpy(arg2dt, tbl[o2Idx].dt);
    if (strcmp(arg1dt, arg2dt) == 0) {
        if (strcmp(resultvardt, arg1dt) == 0)
            printf("No type mismatch in: %s\n", expression);
        else
            printf("Type mismatch: LValue and RValue must be same in '%s'\n", expression);
    } else {
        printf("Type mismatch between operands in '%s'\n", expression);
    }
}
