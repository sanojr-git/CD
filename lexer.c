/* EX.NO: 2 - Lexical Analyzer
   AIM: Read a C source file and identify tokens (identifiers, keywords, operators, etc.) */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *fp;
char delim[] = {' ', '\t', '\n', ',', ';', '(', ')', '{', '}', '[', ']', '#', '<', '>'};
char oper[]  = {'+', '-', '*', '/', '%', '=', '!'};
char key[20][12] = {
    "int","float","char","double","bool","void","extern","unsigned",
    "goto","static","class","struct","for","if","else","return",
    "register","long","while","do"
};
char predirect[2][12] = {"include", "define"};
char header[6][15]    = {"stdio.h","conio.h","malloc.h","process.h","string.h","ctype.h"};

int fop = 0, numflag = 0, f = 0;
char sop;

void skipcomment();
void analyze();
void check(char[]);
int isdelim(char);
int isop(char);

int main() {
    char fname[50];
    printf("\nEnter filename to analyze: ");
    scanf("%s", fname);
    fp = fopen(fname, "r");
    if (!fp) { printf("\nFile not found."); return 1; }
    analyze();
    printf("\n\nEnd of file\n");
    fclose(fp);
    return 0;
}

void analyze() {
    char token[50]; int j = 0; char c;
    while (!feof(fp)) {
        c = getc(fp);
        if (c == '/') { skipcomment(); }
        else if (c == '\"') { while ((c = getc(fp)) != '\"'); }
        else if (isalpha(c)) {
            if (f == 1) { token[j] = '\0'; check(token); j = 0; numflag = 0; f = 0; }
            token[j++] = c; f = 1;
        } else if (isdigit(c)) { if (!numflag) numflag = 1; token[j++] = c; }
        else {
            if (isdelim(c)) {
                if (f == 1 || numflag == 1) { token[j] = '\0'; check(token); j = 0; f = 0; numflag = 0; }
                if (c != ' ' && c != '\t' && c != '\n') printf("\nDelimiter\t : %c", c);
            } else if (isop(c)) {
                if (f == 1 || numflag == 1) { token[j] = '\0'; check(token); j = 0; f = 0; numflag = 0; }
                if (fop == 1) { printf("\nOperator\t : %c%c", sop, c); fop = 0; }
                else printf("\nOperator\t : %c", c);
            }
        }
    }
}

int isdelim(char c) {
    for (int i = 0; i < 14; i++) if (c == delim[i]) return 1;
    return 0;
}

int isop(char c) {
    for (int i = 0; i < 7; i++) {
        if (c == oper[i]) {
            char ch2 = getc(fp);
            for (int j = 0; j < 7; j++) {
                if (ch2 == oper[j]) { fop = 1; sop = ch2; return 1; }
            }
            ungetc(ch2, fp);
            return 1;
        }
    }
    return 0;
}

void check(char t[]) {
    if (numflag == 1) { printf("\nNumber\t\t : %s", t); return; }
    for (int i = 0; i < 2; i++) if (strcmp(t, predirect[i]) == 0) { printf("\nPreprocessor\t : %s", t); return; }
    for (int i = 0; i < 6; i++) if (strcmp(t, header[i]) == 0) { printf("\nHeader file\t : %s", t); return; }
    for (int i = 0; i < 20; i++) if (strcmp(key[i], t) == 0) { printf("\nKeyword\t\t : %s", t); return; }
    printf("\nIdentifier\t : %s", t);
}

void skipcomment() {
    char ch2 = getc(fp);
    if (ch2 == '/') while ((ch2 = getc(fp)) != '\n');
    else if (ch2 == '*') {
        int done = 0;
        while (!done) { ch2 = getc(fp); if (ch2 == '*') { ch2 = getc(fp); if (ch2 == '/') done = 1; } }
    }
}
