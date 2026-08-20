/* EX.NO: 5 - Control Structure Syntax Recognition using YACC */
%{
#include <stdio.h>
#include <stdlib.h>
%}

%token IF ELSE FOR WHILE SWITCH CASE DEFAULT
%token ID NUM LBRACE RBRACE LPAREN RPAREN COLON SEMICOLON
%token EQ LE GE LT GT ASSIGN

%%
program: stmt_list ;
stmt_list: stmt_list stmt | stmt ;
stmt: if_stmt | while_stmt | for_stmt | switch_stmt | expr_stmt ;
expr_stmt: ID ASSIGN NUM SEMICOLON ;
if_stmt:
    IF LPAREN cond RPAREN LBRACE stmt_list RBRACE
  | IF LPAREN cond RPAREN LBRACE stmt_list RBRACE ELSE LBRACE stmt_list RBRACE
  ;
while_stmt: WHILE LPAREN cond RPAREN LBRACE stmt_list RBRACE ;
for_stmt: FOR LPAREN ID ASSIGN NUM SEMICOLON cond SEMICOLON ID ASSIGN ID RPAREN LBRACE stmt_list RBRACE ;
switch_stmt: SWITCH LPAREN ID RPAREN LBRACE case_list RBRACE ;
case_list:
    case_list CASE NUM COLON stmt_list
  | case_list DEFAULT COLON stmt_list
  | CASE NUM COLON stmt_list
  ;
cond: ID relop NUM ;
relop: EQ | LE | GE | LT | GT ;
%%

int main() {
    printf("Enter a C control structure:\n");
    yyparse();
    printf("Valid control structure syntax.\n");
    return 0;
}

int yyerror(char *s) {
    printf("Invalid control structure syntax.\n");
    return 0;
}
