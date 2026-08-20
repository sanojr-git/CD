/* EX.NO: 7 - Three Address Code Generation using YACC */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tempCount = 1;
char temp[20];

typedef struct { char *str; } YYSTYPE;

void printTAC(char *result, char *op1, char *op, char *op2) {
    printf("%s = %s %s %s\n", result, op1, op, op2);
}
%}

%token ID NUM
%left '+' '-'
%left '*' '/'

%%
stmt: ID '=' expr { printf("%s = %s\n", $1.str, $3.str); }
    ;
expr: expr '+' expr {
        sprintf(temp, "t%d", tempCount++);
        printTAC(temp, $1.str, "+", $3.str);
        $$.str = strdup(temp);
    }
    | expr '-' expr {
        sprintf(temp, "t%d", tempCount++);
        printTAC(temp, $1.str, "-", $3.str);
        $$.str = strdup(temp);
    }
    | expr '*' expr {
        sprintf(temp, "t%d", tempCount++);
        printTAC(temp, $1.str, "*", $3.str);
        $$.str = strdup(temp);
    }
    | expr '/' expr {
        sprintf(temp, "t%d", tempCount++);
        printTAC(temp, $1.str, "/", $3.str);
        $$.str = strdup(temp);
    }
    | ID  { $$ = $1; }
    | NUM { $$ = $1; }
    ;
%%

int main() {
    printf("Enter expression (e.g., a = b + c * d):\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}
