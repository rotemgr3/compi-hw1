%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap
zero            (0)
notzero   		([1-9])
digit           ([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n ])
alphanumeric    ([a-zA-Z0-9])
string          ([ !#-\[\]-~	])
escape          ([\"\\0ntr])
hex             (x[0-7][a-fA-F0-9])
notescape       ([^\"\\0ntr])
nothex          (x([^0-7][^0-9A-Fa-f]|[0-7][^0-9A-Fa-f]|[^0-9A-Fa-f]|[^0-7][0-9A-Fa-f]))

%%

void                                                        return VOID;
int                                                         return INT;
byte                                                        return BYTE;
b                                                           return B;
bool                                                        return BOOL;
override                                                    return OVERRIDE;
and                                                         return AND;
or                                                          return OR;
not                                                         return NOT;
true                                                        return TRUE;
false                                                       return FALSE;
return                                                      return RETURN;
if                                                          return IF;
else                                                        return ELSE;
while                                                       return WHILE;
break                                                       return BREAK;
continue                                                    return CONTINUE;
;                                                           return SC;
,                                                           return COMMA;
\(                                                          return LPAREN;
\)                                                          return RPAREN;
\{                                                          return LBRACE;
\}                                                          return RBRACE;
=                                                           return ASSIGN;
==|!=|<|>|<=|>=                                             return RELOP;
\+|\-|\*|\/                                                 return BINOP;
\/\/([^\r\n])*                                              return COMMENT;
{letter}{alphanumeric}*                                     return ID;
0|{notzero}+{digit}*                                        return NUM;
\"({string}|\\{hex}|{alphanumeric}|\\{escape})*\"           return STRING;
\"({string}|\\{hex}|{alphanumeric}|\\{escape})*             return UNCLOSED_STRING;
\"({string}|\\{hex}|{alphanumeric}|\\{escape})*\\{notescape} return INVALID_ESCAPE;
\"({string}|\\{hex}|{alphanumeric}|\\{escape})*\\{nothex}   return INVALID_HEX;
{whitespace}				                                ;

.		                                                    return ERROR;


%%




