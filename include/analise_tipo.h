#pragma once

enum t_kind{ NO_KIND_DEF_=-1, VAR_, PARAM_, FUNCTION_, FIELD_,
ARRAY_TYPE_, STRUCT_TYPE_, ALIAS_TYPE_, SCALAR_TYPE_ , UNIVERSAL_};

typedef struct object
{
  int nName;
  struct object * pNext;
  t_kind eKind;

  union {
    struct {
      struct object *pType;
      int nIndex;
      int nSize;
    } Var, Param, Field;
    struct {
      struct object *pRetType;
      struct object *pParams;
      int nIndex;
      int nParams;
      int nVars;
    } Function;
    struct {
      struct object *pElemType;
      int nNumElems;
      int nSize;
    } Array;
    struct {
      struct object *pFields;
      int nSize;
    } Struct;
  };
  struct {
    struct object *pBaseType;
    int nSize;
  } Alias, Type;
} object, * pobject;

int new_block();
int end_block();

pobject define_symbol(int name);
pobject search_symbol_in_scope(int name);
pobject search_symbol_globally(int name);
int check_types(pobject t1, pobject t2);

extern object int_;
extern pobject pInt;
extern object char_;
extern pobject pChar;
extern object bool_;
extern pobject pBool;
extern object string_;
extern pobject pString;
extern object universal_;
extern pobject pUniversal;

const int MAX_NEST_LEVEL = 5;

extern pobject symbol_table[MAX_NEST_LEVEL];
extern pobject symbol_table_last[MAX_NEST_LEVEL];
extern int current_level;
