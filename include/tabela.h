#pragma once

#include "analisador_lexico.h"

extern int rule[85][2];
extern int action[168][95];

typedef enum {
  DF = 52, DE, DC, DV, DT, TRUE_TOKEN, IDD, LE, LDE, NB, NF, LI, LV, NUM, LS, LP,
  LDV, B, E, F, IDU, L, P, S, R, T, STR, Y, ME, MF, FALSE_TOKEN, MC, CHR, MT, MW
} nonterminal;

void create_action_table();
