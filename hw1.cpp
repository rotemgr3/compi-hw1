#include "tokens.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <stdio.h>

using namespace std;

string tokenToStr(int token);

int main()
{
	int token;
	while ((token = yylex())) {
		string str = string(yytext);
		if (token == ERROR){
			if (str == "\0" || str == "\x00" || str == "\r" || str == "\n" || str == "\t")
				continue;
			cout << tokenToStr(token) << " " << yytext << endl;
			exit(0);
		}
		else if (token == UNCLOSED_STRING){
			cout << tokenToStr(token) << endl;
			exit(0);
		}
		else if (token == INVALID_HEX) {
			size_t found = str.find_last_of('\\');
			string escape_seq = str.substr(found+1);
			escape_seq = escape_seq.substr(0,3);
			if(escape_seq[escape_seq.size() - 1] == '\"')
				escape_seq = escape_seq.substr(0,escape_seq.size() - 1);
			cout << "Error undefined escape sequence " << escape_seq << endl;
			exit(0);
		}
		else if (token == INVALID_ESCAPE) {
			size_t found = str.find_last_of('\\');
			string escape_seq = str.substr(found+1);
			cout << "Error undefined escape sequence " << escape_seq[0] << endl;
			exit(0);
		}
		else if(token == STRING){
			str = str.substr(1,str.size()-2);
			string result;
			cout << yylineno << " " << tokenToStr(token) << " ";
			for(unsigned int i = 0; i<str.size(); i++){
				if(str[i] == '\\'){
					if (i+1 < str.size()) {
						switch (str[i+1]) {
							case 'n':
								result += '\n';
								break;
							case 't':
								result += '\t';
								break;
							case 'r':
								result += '\r';
								break;
							case '0':
								result += '\0';
								break;
							case '"':
								result += '\"';
								break;
							case '\\':
								result += '\\';
								break;
							case 'x':
								unsigned int x = std::stoul('0'+str.substr(i+1, 3), nullptr, 16);
								result += char(x);
								i += 2;							
								break;						
						}
						i++;
					}
				}
				else
					result += str[i];
			}
			cout << result.c_str() << endl;
		}
		else if(token == COMMENT){
			str = str.substr(0,2);
			cout << yylineno << " " << tokenToStr(token) << " " << str << endl;
		}
		else
			cout << yylineno << " " << tokenToStr(token) << " " << yytext << endl;
	}
	return 0;
}

string tokenToStr(int token){
	switch(token){
		case VOID:
			return "VOID";
		case INT:
			return "INT";
		case BYTE:
			return "BYTE";
		case B:
			return "B";
			break;
		case BOOL:
			return "BOOL";
		case AND:
			return "AND";
		case OR:
			return "OR";
		case NOT:
			return "NOT";
		case TRUE:
			return "TRUE";
			break;
		case FALSE:
			return "FALSE";
		case RETURN:
			return "RETURN";
		case IF:
			return "IF";
		case ELSE:
			return "ELSE";
		case WHILE:
			return "WHILE";
		case BREAK:
			return "BREAK";
		case CONTINUE:
			return "CONTINUE";
		case SC:
			return "SC";
		case COMMA:
			return "COMMA";
		case LPAREN:
			return "LPAREN";
		case RPAREN:
			return "RPAREN";
		case LBRACE:
			return "LBRACE";
		case RBRACE:
			return "RBRACE";
		case ASSIGN:
			return "ASSIGN";
		case RELOP:
			return "RELOP";
		case BINOP:
			return "BINOP";
		case COMMENT:
			return "COMMENT";
		case ID:
			return "ID";			
		case NUM:
			return "NUM";
		case STRING:
			return "STRING";
		case OVERRIDE:
			return "OVERRIDE";
		case ERROR:
			return "ERROR";
		case UNCLOSED_STRING:
			return "Error unclosed string";
		default:
			return "";
	}
}
