#include "itpFuncoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*################################################################
  #                      Funções do Banco                        #
  ################################################################
*/

void criarTabela() {
  char *nomeTabela = malloc(sizeof(char) * 200),
       *caminho = malloc(sizeof(char) * 30), ext[] = ".itp",
       *coluna = malloc(sizeof(char) * 100);
  int quantColunas, tipo;
  strcat(caminho, "data/");
  // abrindo metadados: escreve no arquivo, lê o arquivo.
  FILE *metadados = fopen("data/Metadados.itp", "a+"), *arquivoTabela;
  if (metadados != NULL) { // Se arquivo NÂO estiver vazio: IF iniciado.

    printf("Digite o nome da tabela: ");
    scanf("%s", nomeTabela); // recebe do USUÁRIO o nome da tabela.

    verificarTabela(nomeTabela);

    /* caso entre no IF e o nome de tabela INSERIDO pelo USUÁRIO seja
       diferente de algu nome de tabela do arquivo ele sai do
       while e cria o arquivo da tabela */
    fprintf(metadados, "%s\n\n",
            nomeTabela);     // escrevendo no arquivo metadados o nome da tabela
    strcat(nomeTabela, ext); // adicionando a extensão ao arquivo da tabela
    strcat(caminho, nomeTabela);
    arquivoTabela =
        fopen(caminho, "a+"); // cria um arquivo com o nome da tabela
    /* criando as colunas da tabela*/
    printf("Digite a quantidade de colunas(incluindo chave primária): ");
    scanf("%d", &quantColunas); // solicitação de quantidade de colunas
    char *colunas[quantColunas], *tipos[quantColunas];
    for (int i = 0; i < quantColunas; i++) {
      // define o comparador como zero para verificar todas as colunas
      colunas[i] =
          malloc(sizeof(char) * 100); // aloca memória para o vetor que irá
                                      // armazenar o nome das colunas
      tipos[i] = malloc(sizeof(char) * 20);
      if (i == 0) {
        printf("Digite o nome da chave primária: ");
        scanf("%s", colunas[i]); // recebe o nome da chave primária
        tipos[i] = "INT";
      } else {
        printf("Digite o nome da coluna %d: ", i + 1);
        scanf("%s", coluna);                 // recebe o nome da coluna
        verificarColuna(i, colunas, coluna); // verifica se coluna já existe
        printf("Digite o número referente ao tipo da coluna:\n"
               "1-INT\n"
               "2-CHAR\n"
               "3-FLOAT\n"
               "4-DOUBLE\n"
               "5-STRING\n>");
        scanf("%d", &tipo);
        definirTipoColuna(tipo, i, tipos);
        strcpy(colunas[i],
               coluna); // passa valor digitador pra array de strings
      }
    }

    for (int i = 0; i < quantColunas; i++) { // inserir colunas no arquivo
      if (i == 0) {
        fprintf(arquivoTabela, "%s*(%s)|", colunas[i], tipos[i]);
      } else
        fprintf(arquivoTabela, "%s(%s)|", colunas[i], tipos[i]);
    }

    printf("Tabela %s criada com sucesso.\n\n", nomeTabela);

    fclose(metadados);
    fclose(arquivoTabela);
    free(nomeTabela);
    free(coluna);
  } else
    printf("Erro na leitura ou criação do arquivo\n");
}

void verificarTabela(char *nomeTabela) {
  FILE *metadados = fopen("data/Metadados.itp", "a+"), *arquivoTabela;
  char *buffer = malloc(sizeof(char) * 100);
  // lê o arquivo até a quebra de linha  e entra no IF para checá-lo.
  while (fscanf(metadados, "%s", buffer) != EOF) {

    /* ENQUANTO nome da tabela inserido pelo USUÁRIO for igual a nome de
    alguma tabela existente no arquivo, ele recusa e pede um nome diferente
    para a tabela. */
    while (strcmp(nomeTabela, buffer) == 0) {
      printf("Tabela já existe! Dê outro nome: ");
      scanf("%s", nomeTabela); // recebe o novo nome.
    }
  }
  free(buffer);
  fclose(metadados);
}

void verificarColuna(int i, char **colunas, char *coluna) {
  int comparador = 0; // comparador usado para gerenciar comparação das colunas
  while (comparador < i) {
    if (strcmp(coluna, colunas[comparador]) == 0) {
      printf("Coluna existente! Digite um novo nome: ");
      scanf("%s", coluna); // recebe o nome da coluna
      comparador = 0;
    } else {
      comparador++;
    }
  }
}

void listarTabelas() {
  FILE *arquivo = fopen("data/Metadados.itp", "r");

  if (arquivo == NULL) {
    printf("ERRO\n");
  }
  printf("Todas as tabelas do banco:\n");
  char *buffer = malloc(sizeof(char) * 100);
  while (fgets(buffer, 100, arquivo) != NULL) {
    printf("%s", buffer);
  }
  free(buffer);
}

void definirTipoColuna(int tipo, int i, char **tipos) {
  int j = 0;
  while (j == 0) {
    switch (tipo) {
    case 1:
      tipos[i] = "INT";
      j = 1;
      break;
    case 2:
      tipos[i] = "CHAR";
      j = 1;
      break;
    case 3:
      tipos[i] = "FLOAT";
      j = 1;
      break;
    case 4:
      tipos[i] = "DOUBLE";
      j = 1;
      break;
    case 5:
      tipos[i] = "STRING";
      j = 1;
      break;
    default:
      printf("Tipo inválido! Digite novamente:\n>");
      scanf("%d", &tipo);
      break;
    }
  }
}

void menuBanco() {
  int op;
  printf("\n", );
}
