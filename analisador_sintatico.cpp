#include <analisador_sintatico.h>
#include <pilha_semantica.h>

using namespace std;

vector<int> values;

void print_stack() {
  printf("stack:");
  for(int u: values) printf(" %d", u);
  printf("\n");
}

void parse() {
  create_action_table();

  t_token token;

  values.push_back(0);
  token = nextToken();

  do {
    int pos = action[values.back()][token];
    //print_stack();

    if(pos > 0) {
      values.push_back(pos);
      token = nextToken();
    }
    else if(pos < 0) {
      for(int i = 0; i < rule[-pos][0]; i++) values.pop_back();
      int u = values.back();
      values.push_back(action[u][rule[-pos][1]]);

      semantics(-pos);
    }
    else {
      //Error
    }
  } while(values.back() != 1 or token != EOF_TOKEN);
}

int main() {
  parse();
  return 0;
}
