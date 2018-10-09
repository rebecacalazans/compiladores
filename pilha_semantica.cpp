#include<pilha_semantica.h>

using namespace std;

bool IS_TYPE_KIND(t_kind k) {
  return ((k) == ARRAY_TYPE_ or
          (k) == STRUCT_TYPE_ or
          (k) == ALIAS_TYPE_ or
          (k) == SCALAR_TYPE_);
}

int new_label() {
  static int label_number = 0;
  return label_number++;
}

vector<t_attrib> semantic_stack;
int semantic_stack_size = 0;
int nFuncs = 0;
pobject curFunction;
int functionVarPos;


void semantic_stack_push(t_attrib attrib) {
  semantic_stack.push_back(attrib);
}

void semantic_stack_pop() {
  semantic_stack.pop_back();
}
t_attrib semantic_stack_top() {
  return semantic_stack.back();
}

void semantics(t_rule rule) {
  static int name,n,l,l1,l2;
  static pobject p,t,f;
  static t_attrib IDD_static,IDU_static,ID_static,T_static,LI_static,LI0_static,LI1_static,TRU_static,FALS_static,STR_static,CHR_static,NUM_static,DC_static,DC0_static,DC1_static,LP_static,LP0_static,LP1_static,E_static,E0_static,E1_static,L_static,L0_static,L1_static,R_static,R0_static,R1_static,Y_static,Y0_static,Y1_static,F_static,F0_static,F1_static,LV_static,LV0_static,LV1_static,MC_static,LE_static,LE0_static,LE1_static,MT_static,ME_static,MW_static,NB_static;

  switch(rule){
    case RULE_LDE_0:    //LDE -> LDE DE
    case RULE_LDE_1:    //LDE -> DE
    case RULE_DE_0:     //DE -> DF
    case RULE_DE_1:     //DE -> DT
    break;

    case RULE_T_0:      //T -> TOKEN_INTEGER
      T_static.T.type = pInt;
      T_static.type = T;
      T_static.nSize = 1;
      semantic_stack_push(T_static);
    break;

    case RULE_T_1:      //T -> TOKEN_CHAR
      T_static.T.type = pChar;
      T_static.type = T;
      T_static.nSize = 1;
      semantic_stack_push(T_static);
    break;

    case RULE_T_2:      //T -> TOKEN_BOOLEAN
      T_static.T.type = pBool;
      T_static.type = T;
      T_static.nSize = 1;
      semantic_stack_push(T_static);
    break;

    case RULE_T_3:      //T -> TOKEN_STRING
      T_static.T.type = pString;
      T_static.type = T;
      T_static.nSize = 1;
      semantic_stack_push(T_static);
    break;

    case RULE_T_4:      //T -> IDU
      IDU_static = semantic_stack_top();
      p = IDU_static.ID.obj;
      semantic_stack_pop();

      if(IS_TYPE_KIND(p->eKind) || p->eKind == UNIVERSAL_){
        T_static.T.type = p;
        if(p->eKind == ALIAS_TYPE_){
          T_static.nSize = p->Alias.nSize;
        }
        else if(p->eKind == ARRAY_TYPE_){
          T_static.nSize = p->Array.nSize;
        }
        else if(p->eKind == STRUCT_TYPE_){
          T_static.nSize = p->Struct.nSize;
        }
      }
      else{
        T_static.T.type = pUniversal;
        T_static.nSize = 0;
        //Error
      }
      T_static.type = T;
      semantic_stack_push(T_static);
    break;

    case RULE_DT_0:     //DT -> TOKEN_TYPE IDD TOKEN_EQUAL TOKEN_ARRAY TOKEN_LEFT_SQUARE NUM TOKEN_RIGHT_SQUARE TOKEN_OF T
      T_static = semantic_stack_top();
      semantic_stack_pop();
      NUM_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();

      p = IDD_static.ID.obj;
      n = NUM_static.NUM.val;
      t = T_static.T.type;

      p->eKind = ARRAY_TYPE_;
      p->Array.nNumElems = n;
      p->Array.pElemType = t;
      p->Array.nSize = n * T_static.nSize;
    break;

    case RULE_DT_1:     //DT -> TOKEN_TYPE IDD TOKEN_EQUAL TOKEN_STRUCT NB TOKEN_LEFT_BRACES DC TOKEN_RIGHT_BRACES
      DC_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();

      p = IDD_static.ID.obj;
      p->eKind = STRUCT_TYPE_;
      p->Struct.pFields = DC_static.DC.list;
      p->Struct.nSize = DC_static.nSize;
      end_block();
    break;

    case RULE_DT_2:     //DT -> TOKEN_TYPE IDD TOKEN_EQUAL T
      T_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();

      p = IDD_static.ID.obj;
      t = T_static.T.type;

      p->eKind = ALIAS_TYPE_;
      p->Alias.pBaseType = t;
      p->Alias.nSize = T_static.nSize;
    break;

    case RULE_DC_0:     //DC -> DC TOKEN_SEMICOLON LI TOKEN_COLON T
      T_static = semantic_stack_top();
      semantic_stack_pop();
      LI_static = semantic_stack_top();
      semantic_stack_pop();
      DC1_static = semantic_stack_top();
      semantic_stack_pop();

      p = LI_static.LI.list;
      t = T_static.T.type;
      n = DC1_static.nSize;

      while( p != NULL && p->eKind == NO_KIND_DEF_){
        p->eKind = FIELD_;
        p->Field.pType = t;
        p->Field.nIndex = n;
        p->Field.nSize = T_static.nSize;
        n = n + T_static.nSize;
        p = p->pNext;
      }

      DC0_static.DC.list = DC1_static.DC.list;
      DC0_static.nSize = n;
      DC0_static.type = DC;
      semantic_stack_push(DC0_static);
    break;

    case RULE_DC_1:     //DC -> LI TOKEN_COLON T
      T_static = semantic_stack_top();
      semantic_stack_pop();
      LI_static = semantic_stack_top();
      semantic_stack_pop();

      p = LI_static.LI.list;
      t = T_static.T.type;
      n = 0;
      while( p != NULL && p->eKind == NO_KIND_DEF_){
        p->eKind = FIELD_;
        p->Field.pType = t;
        p->Field.nSize = T_static.nSize;
        p->Field.nIndex = n;
        n = n + T_static.nSize;
        p = p->pNext;
      }
      DC_static.DC.list = LI_static.LI.list;
      DC_static.nSize = n;
      DC_static.type = DC;
      semantic_stack_push(DC_static);
    break;

    case RULE_DF_0:     //DF -> TOKEN_FUNCTION IDD NB TOKEN_LEFT_PARENTHESIS LP TOKEN_RIGHT_PARENTHESIS TOKEN_COLON T MF B
      end_block();
      /*fpos_t currentPos;
        fgetpos(out,&currentPos);
        fsetpos(out,&functionVarPos);
        fprintf(out,"%d",f->_.Function.nVars-f->_.Function.nParams);
        fsetpos(out,&currentPos);
        fprintf(out,"END_FUNC\n");*/
    break;

    case RULE_LP_0:     //LP -> LP TOKEN_COMMA IDD TOKEN_COLON T
      T_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();
      LP1_static = semantic_stack_top();
      semantic_stack_pop();

      p = IDD_static.ID.obj;
      t = T_static.T.type;
      n = LP1_static.nSize;

      p->eKind = PARAM_;
      p->Param.pType = t;
      p->Param.nIndex = n;
      p->Param.nSize = T_static.nSize;

      LP0_static.LP.list = LP1_static.LP.list;
      LP0_static.nSize = n + T_static.nSize;
      LP0_static.type = LP;
      semantic_stack_push(LP0_static);
    break;

    case RULE_LP_1:     //LP -> IDD TOKEN_COLON T
      T_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();

      p = IDD_static.ID.obj;
      t = T_static.T.type;
      p->eKind = PARAM_;
      p->Param.pType = t;
      p->Param.nIndex = 0;
      p->Param.nSize = T_static.nSize;
      LP_static.LP.list = p;
      LP_static.nSize = T_static.nSize;
      LP_static.type = LP;

      semantic_stack_push(LP_static);
    break;

    case RULE_B_0:      //B -> TOKEN_LEFT_BRACES LDV LS TOKEN_RIGHT_BRACES
    break;

    case RULE_LDV_0:    //LDV -> LDV DV
    case RULE_LDV_1:    //LDV -> DV
    case RULE_LS_0:     //LS -> LS S
    case RULE_LS_1:     //LS -> S
    break;

    case RULE_DV_0:     //DV -> TOKEN_VAR LI TOKEN_COLON T TOKEN_SEMICOLON
      T_static = semantic_stack_top();
      t = T_static.T.type;
      semantic_stack_pop();
      LI_static = semantic_stack_top();
      semantic_stack_pop();
      p = LI_static.LI.list;
      n = curFunction->Function.nVars;

      while(p != NULL && p->eKind == NO_KIND_DEF_){
        p->eKind = VAR_;
        p->Var.pType = t;
        p->Var.nSize = T_static.nSize;
        p->Var.nIndex = n;

        n += T_static.nSize;
        p = p->pNext;
      }

      curFunction->Function.nVars = n;
    break;

    case RULE_LI_0:     //LI -> LI TOKEN_COMMA IDD
      IDD_static = semantic_stack_top();
      semantic_stack_pop();
      LI1_static = semantic_stack_top();
      semantic_stack_pop();
      LI0_static.LI.list = LI1_static.LI.list;
      LI0_static.type = LI;
      semantic_stack_push(LI0_static);
    break;

    case RULE_LI_1:     //LI -> IDD
      IDD_static = semantic_stack_top();
      LI_static.LI.list = IDD_static.ID.obj;
      LI_static.type = LI;
      semantic_stack_pop();
      semantic_stack_push(LI_static);
    break;

    case RULE_MT_0:     //MT -> ''
      l = new_label();
      MT_static.MT.label = l;
      MT_static.type = MT;
      semantic_stack_push(MT_static);
    break;

    case RULE_S_0:      //S -> TOKEN_IF TOKEN_LEFT_PARENTHESIS E TOKEN_RIGHT_PARENTHESIS S
      MT_static = semantic_stack_top();
      semantic_stack_pop();
      E_static = semantic_stack_top();
      semantic_stack_pop();

      t = E_static.E.type;
      //if( !check_types(t,pBool)){//Error}

    break;

    case RULE_ME_0:     //ME -> ''
      MT_static = semantic_stack_top();
      l1 = MT_static.MT.label;
      l2 = new_label();
      ME_static.ME.label = l2;
      ME_static.type = ME;
      semantic_stack_push(ME_static);

    break;

    case RULE_S_1:      //S -> TOKEN_IF TOKEN_LEFT_PARENTHESIS E TOKEN_RIGHT_PARENTHESIS S TOKEN_ELSE S
      ME_static = semantic_stack_top();
      semantic_stack_pop();
      MT_static = semantic_stack_top();
      semantic_stack_pop();
      E_static = semantic_stack_top();
      semantic_stack_pop();

      l = ME_static.ME.label;

      t = E_static.E.type;
      //if( !check_types(t,pBool)){//Error}
    break;
    case RULE_MW_0:     //MW -> ''
      l = new_label();
      MW_static.MW.label = l;
      semantic_stack_push(MW_static);
    break;

    case RULE_S_2:      //S -> TOKEN_WHILE TOKEN_LEFT_PARENTHESIS E TOKEN_RIGHT_PARENTHESIS S
      MT_static = semantic_stack_top();
      semantic_stack_pop();
      E_static = semantic_stack_top();
      semantic_stack_pop();
      MW_static = semantic_stack_top();
      semantic_stack_pop();

      l1 = MW_static.MW.label;
      l2 = MT_static.MT.label;

      t = E_static.E.type;
      //if( !check_types(t,pBool)){//Error}

    break;

    case RULE_S_3:      //S -> TOKEN_DO S TOKEN_WHILE TOKEN_LEFT_PARENTHESIS E TOKEN_RIGHT_PARENTHESIS TOKEN_SEMICOLON
      E_static = semantic_stack_top();
      semantic_stack_pop();
      MW_static = semantic_stack_top();
      semantic_stack_pop();

      l = MW_static.MW.label;

      t = E_static.E.type;
      //if( !check_types(t,pBool)){//Error}

    break;

    case RULE_S_4:      //S -> NB B
      end_block();
    break;

    case RULE_S_5:      //S -> LV TOKEN_EQUAL E TOKEN_SEMICOLON
      E_static = semantic_stack_top();
      semantic_stack_pop();
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      t = LV_static.LV.type;

      //if(!check_types(LV_static.LV.type, E_static.E.type)){//Error}
    break;

    case RULE_S_6:      //S -> TOKEN_BREAK TOKEN_SEMICOLON
    case RULE_S_7:      //S -> TOKEN_CONTINUE TOKEN_SEMICOLON
    break;

    case RULE_E_0:      //E -> E TOKEN_AND L
      L_static = semantic_stack_top();
      semantic_stack_pop();
      E1_static = semantic_stack_top();
      semantic_stack_pop();
      //if( !check_types(E1_static.E.type,pBool)){//Error}

      //if( !check_types(L_static.L.type,pBool)){//Error}

      E0_static.E.type = pBool;
      E0_static.type = E;
      semantic_stack_push(E0_static);
    break;

    case RULE_E_1:      //E -> E TOKEN_OR L
      L_static = semantic_stack_top();
      semantic_stack_pop();
      E1_static = semantic_stack_top();
      semantic_stack_pop();
      //if( !check_types(E1_._.E.type,pBool)){Error(ERR_BOOL_TYPE_EXPECTED);}

      //if( !check_types(L_._.L.type,pBool)){Error(ERR_BOOL_TYPE_EXPECTED);}

      E0_static.E.type = pBool;
      E0_static.type = E;
      semantic_stack_push(E0_static);
    break;

    case RULE_E_2:      //E -> L
      L_static = semantic_stack_top();
      semantic_stack_pop();
      E_static.E.type = L_static.L.type;
      E_static.type = E;
      semantic_stack_push(E_static);
    break;

    case RULE_L_0:      //L -> L TOKEN_LESS R
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);

    break;

    case RULE_L_1:      //L -> L TOKEN_GREATER R
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
    break;

    case RULE_L_2:      //L -> L TOKEN_LESS_OR_EQUAL R
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
    break;

    case RULE_L_3:      //L -> L TOKEN_GREATER_OR_EQUAL R
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
    break;

    case RULE_L_4:      //L -> L TOKEN_EQUAL_EQUAL R
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
    break;

    case RULE_L_5:      //L -> L TOKEN_NOT_EQUAL R
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
    break;

    case RULE_L_6:      //L -> R
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L_static.L.type = R_static.R.type;
      L_static.type = L;
      semantic_stack_push(L_static);
    break;

    case RULE_R_0:      //R -> R TOKEN_PLUS Y
      Y_static = semantic_stack_top();
      semantic_stack_pop();
      R1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( ! check_types(R1_._.R.type,K_._.K.type)){Error(ERR_TYPE_MISMATCH);}

      //if( !check_types(R1_._.R.type,pInt) && !check_types(R1_._.R.type,pString)){Error(ERR_INVALID_TYPE);}

      R0_static.R.type = R1_static.R.type;
      R0_static.type = R;
      semantic_stack_push(R0_static);
    break;

    case RULE_R_1:      //R -> R TOKEN_MINUS Y
      Y_static = semantic_stack_top();
      semantic_stack_pop();
      R1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( ! check_types(R1_._.R.type,K_._.K.type)){Error(ERR_TYPE_MISMATCH);}

      //if( !check_types(R1_._.R.type,pInt)){Error(ERR_INVALID_TYPE);}

      R0_static.R.type = R1_static.R.type;
      R0_static.type = R;
      semantic_stack_push(R0_static);
    break;

    case RULE_R_2:      //R -> Y
      Y_static = semantic_stack_top();
      semantic_stack_pop();
      R_static.R.type = Y_static.Y.type;
      R_static.type = R;
      semantic_stack_push(R_static);
    break;
    case RULE_Y_0:      //Y -> Y TOKEN_TIMES F
      F_static = semantic_stack_top();
      semantic_stack_pop();
      Y1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( !check_types(K1_._.K.type,F_._.F.type)){Error(ERR_TYPE_MISMATCH);}

      //if( !check_types(K1_._.K.type,pInt)){Error(ERR_INVALID_TYPE);}

      Y0_static.Y.type = Y1_static.Y.type;
      Y0_static.type = Y;
      semantic_stack_push(Y0_static);
    break;

    case RULE_Y_1:      //Y -> Y TOKEN_DIVIDE F
      F_static = semantic_stack_top();
      semantic_stack_pop();
      Y1_static = semantic_stack_top();
      semantic_stack_pop();

      //if( !check_types(K1_._.K.type,F_._.F.type)){Error(ERR_TYPE_MISMATCH);}

      //if( !check_types(K1_._.K.type,pInt)){Error(ERR_INVALID_TYPE);}

      Y0_static.Y.type = Y1_static.Y.type;
      Y0_static.type = Y;
      semantic_stack_push(Y0_static);
    break;
    case RULE_Y_2:      //Y -> F
      F_static = semantic_stack_top();
      semantic_stack_pop();
      Y_static.Y.type = F_static.F.type;
      Y_static.type = Y;
      semantic_stack_push(Y_static);
    break;
    case RULE_F_0:      //F -> LV
      LV_static = semantic_stack_top();
      semantic_stack_pop();

      n = LV_static.LV.type->Type.nSize;

      F_static.F.type = LV_static.LV.type;
      F_static.type = F;
      semantic_stack_push(F_static);
    break;
    case RULE_F_1:      //F -> TOKEN_PLUS_PLUS LV
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      t = LV_static.LV.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

      F_static.F.type = pInt;
      F_static.type = F;
      semantic_stack_push(F_static);
    break;
    case RULE_F_2:      //F -> TOKEN_MINUS_MINUS LV
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      t = LV_static.LV.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

      F_static.F.type = LV_static.LV.type;
      F_static.type = F;
      semantic_stack_push(F_static);
    break;
    case RULE_F_3:      //F -> LV TOKEN_PLUS_PLUS
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      t = LV_static.LV.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

      F_static.F.type = LV_static.LV.type;
      F_static.type = F;
      semantic_stack_push(F_static);
    break;
    case RULE_F_4:      //F -> LV TOKEN_MINUS_MINUS
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      t = LV_static.LV.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

      F_static.F.type = t;
      F_static.type = F;
      semantic_stack_push(F_static);
    break;
    case RULE_F_5:      //F -> TOKEN_LEFT_PARENTHESIS E TOKEN_RIGHT_PARENTHESIS
      E_static = semantic_stack_top();
      semantic_stack_pop();

      F_static.F.type = E_static.E.type;
      F_static.type = F;
      semantic_stack_push(F_static);
    break;
    case RULE_F_6:      //F -> IDU MC TOKEN_LEFT_PARENTHESIS LE TOKEN_RIGHT_PARENTHESIS
      LE_static = semantic_stack_top();
      semantic_stack_pop();
      MC_static = semantic_stack_top();
      semantic_stack_pop();
      IDU_static = semantic_stack_top();
      semantic_stack_pop();
      f = IDU_static.ID.obj;
      F_static.F.type = MC_static.MC.type;
      //if(!LE_static.LE.err){
      //if(LE_._.LE.n-1 < f->_.Function.nParams && LE_._.LE.n != 0){
      //Error(ERR_TOO_FEW_ARGS);
      //}
      //else if(LE_._.LE.n-1 > f->_.Function.nParams){
      //Error(ERR_TOO_MANY_ARGS);
      //}
      //}
      F_static.type = F;
      semantic_stack_push(F_static);
    break;
    case RULE_F_7:      //F -> TOKEN_MINUS F
      F1_static = semantic_stack_top();
      semantic_stack_pop();

      t = F1_static.F.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

      F0_static.F.type = t;
      F0_static.type = F;
      semantic_stack_push(F0_static);
    break;
    case RULE_F_8:      //F -> TOKEN_NOT F
      F1_static = semantic_stack_top();
      semantic_stack_pop();

      t = F1_static.F.type;
      //if( !check_types(t,pBool)){Error(ERR_INVALID_TYPE);}

      F0_static.F.type = t;
      F0_static.type = F;
      semantic_stack_push(F0_static);
    break;
    case RULE_F_9:      //F -> TRUE
      TRU_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pBool;
      F_static.type = F;
      semantic_stack_push(F_static);

    break;
    case RULE_F_10:     //F -> FALSE
      FALS_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pBool;
      F_static.type = F;
      semantic_stack_push(F_static);
    break;
    case RULE_F_11:     //F -> CHR
      CHR_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pChar;
      F_static.type = F;
      semantic_stack_push(F_static);
      n = secondary_token;
    break;
    case RULE_F_12:     //F -> STR
      STR_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pString;
      F_static.type = F;
      semantic_stack_push(F_static);
      n = secondary_token;
    break;
    case RULE_F_13:     //F -> NUM
      STR_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pInt;
      F_static.type = F;
      semantic_stack_push(F_static);
      n = secondary_token;
    break;
    case RULE_LE_1:     //LE -> E
      E_static = semantic_stack_top();
      semantic_stack_pop();
      MC_static = semantic_stack_top();

      LE_static.LE.param = NULL;
      LE_static.LE.err = MC_static.MC.err;
      n = 1;
      if( !MC_static.MC.err){
        p = MC_static.MC.param;
        if(p == NULL){
          //Error(ERR_TOO_MANY_ARGS);
          LE_static.LE.err = true;
        }
        else{
          //if(!check_types(p->_.Param.pType,E_._.E.type)){Error(ERR_PARAM_TYPE);}
          LE_static.LE.param = p->pNext;
          LE_static.LE.n = n+1;
        }
      }
      LE_static.type = LE;
      semantic_stack_push(LE_static);
    break;
    case RULE_LE_0:     //LE -> LE TOKEN_COMMA E
      E_static = semantic_stack_top();
      semantic_stack_pop();
      LE1_static = semantic_stack_top();
      semantic_stack_pop();
      LE0_static.LE.param = NULL;
      LE0_static.LE.err = L1_static.LE.err;

      n = LE1_static.LE.n;
      if(!LE1_static.LE.err){
        p = LE1_static.LE.param;
        if(p == NULL){
          //Error(ERR_TOO_MANY_ARGS);
          LE0_static.LE.err = true;
        }
        else{
          //if(!check_types(p->_.Param.pType,E_._.E.type)){Error(ERR_PARAM_TYPE);}
          LE0_static.LE.param = p->pNext;
          LE0_static.LE.n = n + 1;
        }
      }
      LE0_static.type = LE;
      semantic_stack_push(LE0_static);
    break;
    case RULE_LV_0:     //LV -> LV TOKEN_DOT IDU
      ID_static = semantic_stack_top();
      semantic_stack_pop();
      LV1_static = semantic_stack_top();
      semantic_stack_pop();

      t = LV1_static.LV.type;
      if( t-> eKind != STRUCT_TYPE_){
        if(t->eKind != UNIVERSAL_){
          //Error( ERR_KIND_NOT_STRUCT);
        }
        LV0_static.LV.type = pUniversal;
      }
      else{
        p = t->Struct.pFields;
        while(p!=NULL){
          if(p->name == ID_static.ID.name){
            break;
          }
          p = p->pNext;
        }
        if(p == NULL){
          //Error(ERR_FIELD_NOT_DECL);
          LV0_static.LV.type = pUniversal;
        }
        else{
          LV0_static.LV.type = p->Field.pType;
          LV0_static.LV.type->Type.nSize = p->Field.nSize;
        }
      }

      LV0_static.type = LV;
      semantic_stack_push(LV0_static);
    break;
    case RULE_LV_1:     //LV -> LV TOKEN_LEFT_SQUARE E TOKEN_RIGHT_SQUARE
      E_static = semantic_stack_top();
      semantic_stack_pop();
      LV1_static = semantic_stack_top();
      semantic_stack_pop();

      t = LV1_static.LV.type;
      if(check_types(t,pString)){
        LV0_static.LV.type = pChar;
      }
      else if(t->eKind != ARRAY_TYPE_){
        if(t->eKind != UNIVERSAL_){
          //Error(ERR_KIND_NOT_ARRAY);
        }
        LV0_static.LV.type = pUniversal;
      }
      else{
        LV0_static.LV.type = t->Array.pElemType;
        n = t->Array.pElemType->Type.nSize;
      }

      if( !check_types(E_static.E.type,pInt)){
        //Error(ERR_INVALID_INDEX_TYPE);
      }

      LV0_static.type = LV;
      semantic_stack_push(LV0_static);
    break;

    case RULE_LV_2:     //LV -> IDU
      IDU_static = semantic_stack_top();
      semantic_stack_pop();

      p = IDU_static.ID.obj;
      if(p->eKind != VAR_ && p->eKind != PARAM_){
        if(p->eKind != UNIVERSAL_){
          //Error(ERR_KIND_NOT_VAR);
        }
        LV_static.LV.type = pUniversal;
      }
      else{
        LV_static.LV.type = p->Var.pType;
        LV_static.LV.type->Type.nSize = p->Var.nSize;
      }
      LV_static.type = LV;

      t = LV_static.LV.type;

      semantic_stack_push(LV_static);
    break;

    case RULE_NB_0:     //NB -> ''
      new_block();
    break;
    case RULE_NF_0:     //NF -> ''
      IDD_static = semantic_stack_top();
      // TODO Não tem pop??
      f = IDD_static.ID.obj;
      f->eKind = FUNCTION_;
      f->Function.nParams = 0;
      f->Function.nVars = 0;
      f->Function.nIndex = nFuncs++;
      new_block();
    break;

    case RULE_MF_0:     //MF -> ''

      T_static = semantic_stack_top();
      semantic_stack_pop();
      LP_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();

      f = IDD_static.ID.obj;
      f->eKind = FUNCTION_;
      f->Function.pRetType = T_static.T.type;
      f->Function.pParams = LP_static.LP.list;
      f->Function.nParams = LP_static.nSize;
      f->Function.nVars = 0;
      curFunction = f;

              f->Function.nParams,0);

      /*fgetpos(out,&functionVarPos);
        fprintf(out,"\n");*/
    break;

    case RULE_MC_0:     //MC -> ''
      IDU_static = semantic_stack_top();
      f = IDU_static.ID.obj;

      if(f->eKind != FUNCTION_){
        //Error(ERR_KIND_NOT_FUNCTION);
        MC_static.MC.type = pUniversal;
        MC_static.MC.param = NULL;
        MC_static.MC.err = true;
      }
      else{
        MC_static.MC.type = f->Function.pRetType;
        MC_static.MC.param = f->Function.pParams;
        MC_static.MC.err = false;
      }
      MC_static.type = MC;
      semantic_stack_push(MC_static);
    break;

    case RULE_IDD_0:    //IDD -> TOKEN_ID
      name = secondary_token;
      IDD_static.ID.name = name;
      if((p = search_symbol_in_scope(name)) != NULL){
        //Error
      }
      else
        p = define_symbol(name);
      IDD_static.ID.obj = p;
      semantic_stack_push(IDD_static);
    break;

    case RULE_IDU_0:    //IDU -> TOKEN_ID
      name = secondary_token;
      IDU_static.ID.name = name;

      if((p = search_symbol_globally(name)) == NULL){
        //Error
        exit(0);
        p = define_symbol(name);
      }
      IDU_static.ID.obj = p;
      semantic_stack_push(IDU_static);
    break;

    case RULE_ID_0:     //ID -> TOKEN_ID
      name = secondary_token;
      ID_static.ID.name = name;
      ID_static.ID.obj = NULL;
      semantic_stack_push(ID_static);
    break;
    case RULE_TRUE_0:   //TRUE -> TOKEN_TRUE
      TRU_static.type = TRUE_TOKEN;
      TRU_static.TRU.val = true;
      TRU_static.TRU.type = pBool;
      semantic_stack_push(TRU_static);
    break;
    case RULE_FALSE_0:  //FALSE -> TOKEN_FALSE
      FALS_static.type = FALSE_TOKEN;
      FALS_static.FALS.val = false;
      FALS_static.FALS.type = pBool;
      semantic_stack_push(FALS_static);
    break;
    case RULE_CHR_0:    //CHR -> TOKEN_CHARACTER
      CHR_static.type = CHR;
      CHR_static.CHR.type = pChar;
      CHR_static.CHR.pos = secondary_token;
      CHR_static.CHR.val = get_char_const(secondary_token);
      semantic_stack_push(CHR_static);
    break;
    case RULE_STR_0:    //STR -> TOKEN_STRINGVAL
      STR_static.type = STR;
      STR_static.STR.type = pString;
      STR_static.STR.pos = secondary_token;
      STR_static.STR.val = get_string_const(secondary_token);
      semantic_stack_push(STR_static);
    break;
    case RULE_NUM_0:    //NUM -> TOKEN_NUMERAL
      NUM_static.type = NUM;
      NUM_static.NUM.type = pInt;
      NUM_static.NUM.pos = secondary_token;
      NUM_static.NUM.val = get_numeral_const(secondary_token);
      semantic_stack_push(NUM_static);
    break;
  }
}
