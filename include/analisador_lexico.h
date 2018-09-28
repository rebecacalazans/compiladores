#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<string>
#include<map>

using namespace std;


//structs
enum t_token {
  NOT, NOT_EQUAL, AND, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, TIMES,
  PLUS, PLUS_PLUS, COMMA, MINUS, DOT, DIVIDE,
  COLON, SEMI_COLON, LESS_THAN, LESS_OR_EQUAL,
  EQUALS, GREATER_THAN, GREATER_OR_EQUAL, LEFT_SQUARE, RIGHT_SQUARE,

  ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCITION,
  IF, INTEGER, OF, STRING, STRUCT, TRUE, TYPE, VAR, WHILE,

  LEFT_BRACES, OR, RIGHT_BRACES, EQUAL_EQUAL, MINUS_MINUS, END,

  CHARACTER, NUMERAL, STRINGVAL, ID,

  UNKNOWN
};

struct t_const {
  char type;//0 - char, 1 - int, 2 - string
  union{
    char cVal;
    int nVal;
    char* sVal;
  }val;
};

//global variables
const int MAX_CONSTS = 1e5;
int nNumConsts = 0;
int token_counter;
map<string, int> secondary_token;
t_const vConsts[MAX_CONSTS];

//functions
t_token nextToken();
t_token searchKeyWord(const char *name);
int searchName (const char *name);

char readChar();
bool isNumeral(char *name);
bool isCharacter(char *name);
bool isStringVal(char *name);


int addCharConst(char c);
int addIntConst(int n);
int addStringConst(char* s);
int addStringConst(string s);

char getCharConst(int n);
int getIntConst(int n);
char* getStringConst(int n);

bool isspace(char c);

t_token nextToken();
