#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<string>
#include<map>

#include<analisador_lexico.h>

int nNumConsts;
int token_counter;
map<string, int> secondary_token;
t_const vConsts[MAX_CONSTS];
int tokenSecundario;

using namespace std;

char readChar() {
  char c = getchar();
  return c;
}

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

t_token searchKeyWord(const char *name) {
  char reserved_words[][10] = {
    "!", "!=", "&", "(", ")", "*", "+", "++", ",", "-", ".", "/",
    ":", ";", "<", "<=", "=", ">", ">=", "[", "]",

    "array", "boolean", "break", "char", "continue",
    "do", "else", "function", "if", "integer", "of", "string",
    "struct", "type", "var", "while",

    "{",  "|", "}"};

  int l = 0, r = 41;
  while(l != r) {
    int m =  (l+r)/2;
    int aux = strcmp(reserved_words[m], name);
    if(aux < 0) l = m+1;
    else r = m;
  }

  if(!strcmp(reserved_words[l], name)) return (t_token)l;

  return ID;
}

int searchName (const char *name) {
  if(!secondary_token.count(name)) {
    secondary_token[name] = token_counter++;
  }
  return secondary_token[name];
}

int addCharConst(char c) {
  vConsts[nNumConsts].type = 0;
  vConsts[nNumConsts].val.cVal = c;
  return nNumConsts++;
}
int addIntConst(int n) {
  vConsts[nNumConsts].type = 1;
  vConsts[nNumConsts].val.nVal = n;
  return nNumConsts++;
}
int addStringConst(char* s) {
  vConsts[nNumConsts].type = 2;
  vConsts[nNumConsts].val.sVal = s;
  return nNumConsts++;
}
int addStringConst(string s) {
  vConsts[nNumConsts].type = 2;
  vConsts[nNumConsts].val.sVal = (char*) malloc(s.size());
  strcpy(vConsts[nNumConsts].val.sVal, s.c_str());
  return nNumConsts++;
}
char getCharConst(int n) {
  return vConsts[n].val.cVal;
}
int getIntConst(int n) {
  return vConsts[n].val.nVal;
}
char* getStringConst(int n) {
  return vConsts[n].val.sVal;
}

char nextChar = ' ';

t_token nextToken() {
  t_token token;
  while (isspace(nextChar))
  {
    nextChar = readChar();
  }
  if(nextChar == EOF) {
    token = EOF_TOKEN;
  }
  else if (isalpha(nextChar))
  {
    string text = "";

    do
    {
      text += nextChar;
      nextChar = readChar();
    } while (isalnum(nextChar) || nextChar == '_');

    token = searchKeyWord(text.c_str());

    if (token == ID)
      tokenSecundario = searchName(text.c_str());
  }
  else if (isdigit(nextChar))
  {
    string numeral = "";
    do
    {
      numeral += nextChar;
      nextChar = readChar();
    } while (isdigit(nextChar));

    token = NUMERAL;
    tokenSecundario = addIntConst(stoi(numeral));
  }
  else if (nextChar == '"')
  {
    string str;
    nextChar = readChar();
    do
    {
      str += nextChar;
      nextChar = readChar();
    } while (nextChar != '"');
    nextChar = readChar();
    token = STRINGVAL;
    tokenSecundario = addStringConst(str);
  }
  else if (nextChar == '\0')
  {
    return END;
  }
  else
  {
    switch (nextChar)
    {
      case '\'':
        nextChar = readChar();
        token = CHARACTER;
        tokenSecundario = addCharConst(nextChar);
        readChar();
        nextChar = readChar();
      break;

      case ':':
        nextChar = readChar();
        token = COLON;
      break;

      case ';':
        nextChar = readChar();
        token = SEMICOLON;
      break;

      case ',':
        nextChar = readChar();
        token = COMMA;
      break;

      case '[':
        nextChar = readChar();
        token = LEFT_SQUARE;
      break;

      case ']':
        nextChar = readChar();
        token = RIGHT_SQUARE;
      break;

      case '{':
        nextChar = readChar();
        token = LEFT_BRACES;
      break;

      case '}':
        nextChar = readChar();
        token = RIGHT_BRACES;
      break;

      case '(':
        nextChar = readChar();
        token = LEFT_PARENTHESIS;
      break;

      case ')':
        nextChar = readChar();
        token = RIGHT_PARENTHESIS;
      break;

      case '&':
        nextChar = readChar();
        if (nextChar == '&')
        {
          token = AND;
        }
        else
        {
          token = UNKNOWN;
        }
        nextChar = readChar();
      break;

      case '|':
        nextChar = readChar();
        if (nextChar == '|')
        {
          token = OR;
        }
        else
        {
          token = UNKNOWN;
        }
        nextChar = readChar();
      break;

      case '*':
        nextChar = readChar();
        token = TIMES;
      break;

      case '/':
        nextChar = readChar();
        token = DIVIDE;
      break;

      case '.':
        nextChar = readChar();
        token = DOT;
      break;

      case '+':
        nextChar = readChar();
        if (nextChar == '+')
        {
          token = PLUS_PLUS;
          nextChar = readChar();
        }
        else
        {
          token = PLUS;
        }
      break;

      case '!':
        nextChar = readChar();
        if (nextChar == '=')
        {
          token = NOT_EQUAL;
          nextChar = readChar();
        }
        else
        {
          token = NOT;
        }
      break;

      case '=':
        nextChar = readChar();
        if (nextChar == '=')
        {
          token = EQUAL_EQUAL;
          nextChar = readChar();
        }
        else
        {
          token = EQUAL;
        }
      break;

      case '-':
        nextChar = readChar();
        if (nextChar == '-')
        {
          token = MINUS_MINUS;
          nextChar = readChar();
        }
        else
        {
          token = MINUS;
        }
      break;

      case '<':
        nextChar = readChar();
        if (nextChar == '=')
        {
          token = LESS_OR_EQUAL;
          nextChar = readChar();
        }
        else
        {
          token = LESS;
        }
      break;

      case '>':
        nextChar = readChar();
        if (nextChar == '=')
        {
          token = GREATER_OR_EQUAL;
          nextChar = readChar();
        }
        else
        {
          token = GREATER;
        }
      break;
      default:
        token = UNKNOWN;
    }
  }
  return token;
}
