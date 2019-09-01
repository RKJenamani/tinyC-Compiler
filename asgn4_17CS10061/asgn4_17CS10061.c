#include <stdio.h>
#include "y.tab.h"

yydebug = 1;
extern char* yytext;
extern int yyparse();

int main() 
{
  int token;
  yyparse();
  return 0;
}