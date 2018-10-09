#include<analise_tipo.h>


object int_ = { -1, NULL_TOKEN, SCALAR_TYPE_ };
pobject pInt = &int_;
object char_ = { -1, NULL_TOKEN, SCALAR_TYPE_ };
pobject pChar = &char_;
object bool_
 = { -1, NULL, SCALAR_TYPE_ };
pobject pBool = &bool_;
object string_ = { -1, NULL_TOKEN, SCALAR_TYPE_ };
pobject pString = &string_;
object universal_= { -1, NULL_TOKEN, SCALAR_TYPE_ };
pobject pUniversal = &universal_;

pobject symbol_table[MAX_NEST_LEVEL];
pobject symbol_table_last[MAX_NEST_LEVEL];
int current_level = -1;

int new_block() {
  symbol_table[++current_level] = NULL_TOKEN;
  symbol_table_last[current_level] = NULL_TOKEN;
  return current_level;
}

int end_block() {
  return --symbol_table_level;
}

pobject define(int nName) {
  pobject obj = (pobject) malloc(sizeof(object));

  obj->nName = nName;
  obj->eKind = NO_KIND_DEF_;
  obj->next = symbol_table[symbol_table_level];
  symbol_table[symbol_table_level] = obj;

  return obj;
}

pobject search_symbol_in_scope(int name) {
  pobject obj = symbol_table[symbol_table_level];

  while (obj != NULL) {
    if (obj->name == name)
      return obj;
    obj = obj->next;
  }

  return obj;
}

pobject search_symbol_globally(int name) {
  pobject obj;

  for (int i = symbol_table_level; i >= 0; i--) {
    obj = symbol_table[i];

    while (obj != NULL) {
      if (obj->name == name)
        return obj;
      obj = obj->next;
    }
  }

  return obj;
}

int check_types(pobject t1, pobject t2)
{
  /**/ if (t1 == t2) return 1;
  else if (t1 == pUniversal || t2 == pUniversal) return 1;
  else if (t1->eKind == UNIVERSAL_ || t2->eKind == UNIVERSAL_) return 1;
  else if(t1->eKind == ALIAS_TYPE_ && t2->eKind != ALIAS_TYPE_){
    return check_types(t1->Alias.pBaseType,t2);
  }
  else if(t1->eKind != ALIAS_TYPE_ && t2->eKind == ALIAS_TYPE_){
    return check_types(t1,t2->Alias.pBaseType);
  }
  else if (t1->eKind == t2->eKind) {
    if (t1->eKind == ALIAS_TYPE_) {
      return check_types(t1->Alias.pBaseType, t2->Alias.pBaseType);
    } else if (t1->eKind == ARRAY_TYPE_) {
      if (t1->Array.nNumElems == t2->Array.nNumElems) {
        return check_types(t1->Array.pElemType, t2->Array.pElemType);
      }
    } else if (t1->eKind == STRUCT_TYPE_) {
      pobject f1 = t1->Struct.pFields;
      pobject f2 = t2->Struct.pFields;
      while (f1 != NULL && f2 != NULL) {
        if (!check_types(f1->Field.pType, f2->Field.pType))
          return 0;
      }
      return (f1 == NULL && f2 == NULL);
    }
  }
  return 0;
}
