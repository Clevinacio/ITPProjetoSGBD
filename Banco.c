#include "itpFuncoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*################################################################
  #                      PROJETO ITP 2018.2                      #
  #            Componentes: Cleverton Inácio Bezerra             #
  #                         Nataly Enne da Costa Gonçalo         #
  ################################################################
*/

int main(int argc, char const *argv[]) {
  printf("#######################################\n");
  printf("#                                     #\n");
  printf("# BEM VINDO AO GERENCIADOR DE BANCOS! #\n");
  printf("#                                     #\n");
  printf("#######################################\n\n");
  printf("abaixo as opções do banco:\n");
  printf("1- Criar Tabela\n2- Listar Tabelas\n3- Adicionar valor a tabela\n4- "
         "listar Dados da tabela\n5- Pesquisar valor de uma tabela\n6- Apagar "
         "valor da tabela\n7- Apagar tabela\n0- Sair\n");
  menuBanco();

  return 0;
}
