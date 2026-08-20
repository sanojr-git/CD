/* EX.NO: 6 - Calculator using YACC */
%{
#include <ctype.h>
#include <stdio.h>
#define YYSTYPE double
%}

%token NUM
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
Statement: E           { printf("Answer: %g\n", $1); }
         | Statement '\n'
         ;
E: E '+' E             { $$ = $1 + $3; }
 | E '-' E             { $$ = $1 - $3; }
 | E '*' E             { $$ = $1 * $3; }
 | E '/' E             { $$ = $1 / $3; }
 | '-' E %prec UMINUS  { $$ = -$2; }
 | NUM                 { $$ = $1; }
 ;
%%

int main() {
    printf("Enter arithmetic expressions (Ctrl+D to quit):\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}
