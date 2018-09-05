#include<stdio.h>
#include<iostream>
#include<string.h>
#include<map>
using namespace std;

enum t_token {
  NOT, NOT_EQUAL, AND, LEFT_PARENTHESIS, RIGHT_PARENTESIS, TIMES,
  PLUS, PLUS_PLUS, COMMA, MINUS, DOT, DIVIDE,
  COLON, SEMI_COLON, LESS_THAN, LESS_OR_EQUAL,
  EQUALS, GREATER_THAN, GREATER_OR_EQUAL, LEFT_SQUARE, RIGHT_SQUARE,

  ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCITION,
  IF, INTEGER, OF, STRING, STRUCT, TRUE, TYPE, VAR, WHILE,

  LEFT_BRACES, OR, RIGHT_BRACES,

  CHARACTER, NUMERAL, STRINGVAL, ID,

  UNKNOWN
};

t_token searchKeyWord(char *name);
int searchName(char *name);

bool isNumeral(char *name) {
  if(name[0] < '0' or name[0] > '9') return false;
  for(int i = 0; name[i]; i++) {
    if(i == 1 and (name[i] == 'x' or name[i] == 'X')) continue;
    if(name[i] < '0' or name[i] > '9') return false;
  }
  return true;
}
bool isCharacter(char *name) {
  if(name[0] == '\'' and name[2] == '\'' and name[3] == '\0') return true;
  return false;
}
bool isStringVal(char *name) {
  int n = strlen(name);
  if(name[0] == '\"' and name[n-1] == '\"') return true;
  return false;
}

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

  return UNKNOWN;
}

int token_counter;
map<string, int> secondary_token;

int searchName (char *name) {
  if(!secondary_token.count(name)) {
    secondary_token[name] = token_counter++;
  }
  return secondary_token[name];
}

struct t_const {
  char type;//0 - char, 1 - int, 2 - string
  union{
    char cVal;
    int nVal;
    char* sVal;
  }v;
}; 


int main() {
  return 0;
}
