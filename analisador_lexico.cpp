#include<stdio.h>
#include<iostream>
#include<string.h>
#include<map>
using namespace std;

const int MAX_CONSTS = 1e5;
int nNumConsts = 0;

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
t_token nextToken();
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
<<<<<<< HEAD
  }v;
}; 

=======
  }val;
};

<<<<<<< HEAD
t_const vConsts[MAX_CONSTS];

int addCharConst(char c) {
  vConsts[nNumConsts].type = 0;
  vConsts[nNumConsts].val = c;
  return nNumConsts++;
}
int addIntConst(int n) {
  vConsts[nNumConsts].type = 1;
  vConsts[nNumConsts].val = n;
  return nNumConsts++;
}
int addStringConst(char* s) {
  vConsts[nNumConsts].type = 2;
  vConsts[nNumConsts].val = s;
  return nNumConsts++;
}
char getCharConst(int n) {
  return vConsts[n].val;
}
int getIntConst(int n) {
  return vConsts[n].val;
}
char *getStringConst(int n) {
  return vConsts[n].val;
}
t_token nextToken()
{

    while (isspace(nextChar))
    {
        nextChar = readChar();
    }
    if (isalpha(nextChar))
    {
        string text = "";

        do
        {
            text += nextChar;
            nextChar = readChar();
        } while (isalnum(nextChar) || nextChar == '_');

        token = searchKeyWord(text);

        if (token == IDT)
            tokenSecundario = searchName(text);
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
            token = SEMI_COLON;
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
                token = EQUALS;
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
                token = LESS_THAN;
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
                token = GREATER_THAN;
            }
            break;
        default:
            token = UNKNOWN;
        }
    }
    return token;
}

int main() {
  return 0;
}
