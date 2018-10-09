#pragma once

#include<analise_tipo.h>
#include<tabela.h>
#include<vector>

struct t_attrib {
  t_nont type;
  int nSize;
  union {
    struct {
      pobject obj;
      int name;
    } ID;

    struct {
      pobject type;
    } T,E,L,R,Y,F,LV;

    struct {
        pobject type;
        pobject param;
        int err;
    } MC;

    struct {
        int label;
    } MT,ME,MW,MA;

    struct{
        pobject type;
        pobject param;
        int err;
        int n;
    } LE;

    struct {
        pobject list;
    } LI,DC,LP;

    struct {
        pobject type;
        int val;
    } TRU,FALS;

    struct {
        pobject type;
        int pos;
        char val;
    } CHR;

    struct {
        pobject type;
        char* val;
        int pos;
    } STR;

    struct {
        pobject type;
        int val;
        int pos;
    } NUM;
  };
};

void semantics(int rule);
