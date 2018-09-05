#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;

enum t_token {
  NOT, NOT_EQUAL, AND, LEFT_PARENTHESIS, RIGHT_PARENTESIS, TIMES,
  PLUS, PLUS_PLUS, COMMA, MINUS, DOT, DIVIDE,

  ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCITION,
  IF, INTEGER, OF, STRING, STRUCT, TRUE, TYPE, VAR, WHILE,

  COLON, SEMI_COLON, LESS_THAN, LESS_OR_EQUAL,
  EQUALS, GREATER_THAN, GREATER_OR_EQUAL, LEFT_SQUARE, RIGHT_SQUARE,
  LEFT_BRACES, OR, RIGHT_BRACES,


  CHARACTER, NUMERAL, STRINGVAL, ID,

  UNKNOWN
};

t_token searchKeyWord(char *name);
int searchName(char *name);

t_token searchKeyWord(char *name) {
  char reserved_words[][10] = {
    "!", "!=", "&", "(", ")", "*", "+", "++", ",", "-", ".", "/",
    ":", ";", "<", "<=", "=", ">", ">=", "[", "]",

    "array", "boolean", "break", "char", "continue",
    "do", "else", "false", "function", "if", "integer", "of", "string",
    "struct", "true", "type", "var", "while",

    "{",  "|", "}"};

  int l = 0, r = 41;
  while(l != r) {
    int m =  (l+r)/2;
    int aux = strcmp(reserved_words[m], name);
    if(aux < 0) l = m+1;
    else r = m;
  }

  if(!strcmp(reserved_words[l], name)) return (t_token)l;

  return (t_token)0;

}

int main() {
  char s[10];

  while(1) {
    scanf("%s", s);
    cout << s << endl;
    t_token t = searchKeyWord(s);
    //cout << "teste: " << (int)t << endl;
    cout << "teste 2: " << ((t == BOOLEAN)? 1: 0) << endl;
  }
  return 0;
}
