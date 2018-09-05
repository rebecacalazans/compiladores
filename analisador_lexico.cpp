#include<stdio.h>

enum t_token {
  ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCITION,
  IF, INTEGER, OF, STRING, STRUCT, TRUE, TYPE, VAR, WHILE, COLON,
  SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE, LEFT_BRACES, RIGHT_BRACES,
  LEFT_PARENTHESIS, RIGHT_PARENTESIS, AND, OR, LESS_THAN, GREATER_THAN,
  LESS_OR_EQUAL, GREATER_OR_EQUAL, NOT_EQUAL, PLUS, PLUS_PLIS, MINUS,
  TIMES, DIVIDE, DOT, NOT,

  CHARACTER, NUMERAL, STRINGVAL, ID,

  UNKNOWN
};

t_token searchKeyWord(char *name);
int searchName(char *name);

t_token searchKeyWord(char *name) {
  char names[][] = {"array", "boolean", "break", "char", "continue",
    "do", "else", "false", "function", "if", "integer", "of", "string",
    "struct", "true", "type", "var", "while", ":", ";", ",", "=", "
}

int main() {
}
