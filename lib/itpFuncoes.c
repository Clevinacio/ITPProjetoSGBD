#define ext ".itp"
#define pasta "data/"
#define extDadosTabela ".dat"
#include "itpFuncoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*################################################################
  #                      Funções do Banco                        #
  ################################################################
*/

//____________________________________________________________________________
// 1 - CRIAR TABELA
void criarTabela() {
  char *nomeTabela = malloc(sizeof(char) * 200),
       *caminho = malloc(sizeof(char) * 30),
       *caminhoDadosTabela = malloc(sizeof(char) * 30),
       *coluna = malloc(sizeof(char) * 100);
  int quantColunas, tipo;
  strcpy(caminho, pasta);
  strcpy(caminhoDadosTabela, pasta);
  // abrindo metadados: escreve no arquivo, lê o arquivo.
  FILE *metadados = fopen("data/Metadados.itp", "a+"), *arquivoTabela,
       *arquivoDadosTabela;
  if (metadados != NULL) { // Se arquivo NÂO estiver vazio: IF iniciado.

    printf("Digite o nome da tabela: ");
    scanf("%s", nomeTabela); // recebe do USUÁRIO o nome da tabela.

    verificarTabelaExistente(nomeTabela);

    /* caso entre no IF e o nome de tabela INSERIDO pelo USUÁRIO seja
       diferente de algu nome de tabela do arquivo ele sai do
       while e cria o arquivo da tabela */
    strcat(caminho, nomeTabela); // adicionando a extensão ao arquivo da tabela
    strcat(caminho, ext);
    strcat(caminhoDadosTabela,
           nomeTabela); // adicionando a extensão ao arquivo da tabela
    strcat(caminhoDadosTabela, extDadosTabela);
    arquivoTabela = fopen(caminho, "w"); // cria um arquivo com o nome da tabela
    arquivoDadosTabela = fopen(caminhoDadosTabela, "w");
    /* criando as colunas da tabela*/
    printf("Digite a quantidade de colunas(incluindo chave primária): ");
    scanf("%d", &quantColunas); // solicitação de quantidade de colunas
    char **colunas = malloc(sizeof(char *) * quantColunas),
         **tipos = malloc(sizeof(char *) * quantColunas);
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
               coluna); // passa valor digitado pra array de strings
      }
    }

    fprintf(metadados, "%s\n",
            nomeTabela); // escrevendo no arquivo metadados o nome da tabela
    for (int i = 0; i < quantColunas; i++) { // inserir colunas no arquivo
      if (i == 0) {
        fprintf(arquivoTabela, "%s* %s|", colunas[i], tipos[i]);
      } else
        fprintf(arquivoTabela, "%s %s|", colunas[i], tipos[i]);
    }
    printf("Tabela %s criada com sucesso.\n\n", nomeTabela);

    fclose(metadados);
    fclose(arquivoTabela);
    free(nomeTabela);
    free(coluna);
    free(colunas);
    free(tipos);
  } else
    printf("Erro na leitura ou criação do arquivo\n");
}
//____________________________________________________________________________
// 2 - LISTAR TABELAS
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
//____________________________________________________________________________
// 3 - ADICIONAR VALOR NA TABELA
void inserirLinhasColuna(char *nomeTabela) {
  Tabela tabela;
  char *caminho = malloc(sizeof(char) * 100),
       *colunas = malloc(sizeof(char) * 200);
  strcat(caminho, "data/");
  strcat(caminho, nomeTabela);
  strcat(caminho, ".itp");
  FILE *arquivoTabela = fopen(caminho, "a+"),
       *metadados = fopen("data/Metadados.itp", "r");
  /*fscanf(arquivoTabela, "%[^\n]s", colunas);
  int quantColunas = contadorColunas(caminho);
  sepColuna = strtok(colunas, delColuna);
  for (int i = 0; i < quantColunas; i++) {
    strcpy(tabela.colunas[i], sepColuna);
    strcat(tabela.colunas[i], " ");
    printf("%s\n", tabela.colunas[i]);
    sepColuna = strtok(NULL, delColuna);
  }*/
  free(caminho);
  free(colunas);
  fclose(arquivoTabela);
  fclose(metadados);
}
//____________________________________________________________________________
// 4- LISTAR DADOS DA TABELA

//____________________________________________________________________________
// 5- PESQUISAR VALOR NA TABELA

//____________________________________________________________________________
// 6- APAGAR VALOR DA TABELA

//____________________________________________________________________________
// 7- APAGAR TABELA
void apagarTabela(char *nomeArquivo) {
  // apagar arquivos da tabela
  char *caminho = malloc(sizeof(char) * 100),
       *caminhoDadosTabela = malloc(sizeof(char) * 100);
  strcpy(caminho, pasta);
  strcat(caminho, nomeArquivo);
  strcat(caminho, ext);
  strcpy(caminhoDadosTabela, pasta);
  strcat(caminhoDadosTabela, nomeArquivo);
  strcat(caminhoDadosTabela, extDadosTabela);
  remove(caminho);
  remove(caminhoDadosTabela);

  // apagar nome da tabela do metadados
  FILE *arquivoOriginal = fopen("data/Metadados.itp", "r");
  FILE *arquivoSaida = fopen("data/metadados.temp", "w");

  if (arquivoOriginal == NULL || arquivoSaida == NULL) {
    printf("Erro de Leitura ou Abertura de Arquivo\n");
  }
  char *buffer = malloc(sizeof(char) * 101),
       *arquivo = malloc(sizeof(char) * 200), *part;
  while (fgets(buffer, 100, arquivoOriginal) != NULL) {
    part = strtok(buffer, nomeArquivo);
    printf("%s\n", part);
    fprintf(arquivoSaida, "%s", buffer);
    printf("%s\n", buffer);
  }
  fclose(arquivoOriginal);
  copiaArquivo("data/Metadados.temp", "data/Metadados.itp");
  fclose(arquivoSaida);
  remove("data/metadados.temp");
  free(caminho);
  free(caminhoDadosTabela);
  free(buffer);
  free(arquivo);
}

void copiaArquivo(char *origem, char *destino) {
  FILE *arquivoOriginal = fopen(origem, "r");
  FILE *arquivoSaida = fopen(destino, "w");

  if (arquivoOriginal == NULL || arquivoSaida == NULL) {
    printf("Erro de Leitura ou Abertura de Arquivo\n");
  }

  char *buffer = malloc(sizeof(char) * 101);
  while (fgets(buffer, 100, arquivoOriginal) != NULL) {
    printf("%s\n", buffer);
    fprintf(arquivoSaida, "%s", buffer);
  }

  fclose(arquivoOriginal);
  fclose(arquivoSaida);
  free(buffer);
}

//____________________________________________________________________________
// 7- VERIFICAÇÕES
void verificarTabelaExistente(char *nomeTabela) {
  FILE *metadados = fopen("data/Metadados.itp", "r");
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

void verificarTabelaInexistente(char *nomeTabela) {
  FILE *metadados = fopen("data/Metadados.itp", "r");
  char *buffer = malloc(sizeof(char) * 100);
  // lê o arquivo até a quebra de linha  e entra no IF para checá-lo.
  while (fscanf(metadados, "%s", buffer) != EOF) {

    /* ENQUANTO nome da tabela inserido pelo USUÁRIO não existir no arquivo,
    ele recusa e pede um nome diferente para a tabela. */
    while (strcmp(nomeTabela, buffer) != 0) {
      printf("Tabela não existe existe! digite uma tabela existente: ");
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
//____________________________________________________________________________
// RELACIONADO A COLUNAS DO BANCO
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

int contadorColunas(char *nomeArquivo) {
  int i = 0;
  char *colunas = malloc(sizeof(char) * 200), *sep, del[] = "|";
  FILE *arquivo = fopen(nomeArquivo, "r");
  fscanf(arquivo, "%[^\n]s", colunas);
  sep = strtok(colunas, del);
  while (sep != NULL) {
    i++;
    sep = strtok(NULL, del);
  }
  fclose(arquivo);
  free(colunas);
  return i - 1;
}

void separarColunas(char *nomeArquivo, char *colunas, Tabela tabela) {
  char *sepColuna, *sepTipo, delColuna[] = "|";
  FILE *arquivo = fopen(nomeArquivo, "r");
  fscanf(arquivo, "%[^\n]s", colunas);
  int quantColunas = contadorColunas(nomeArquivo), i = 0;
  sepColuna = strtok(colunas, delColuna);
  while (sepColuna != NULL) {
    strcpy(tabela.colunas[i], sepColuna);
    strcat(tabela.colunas[i], " ");
    printf("%s\n", tabela.colunas[i]);
    sepColuna = strtok(NULL, delColuna);
    i++;
  }
}
//____________________________________________________________________________
// MENU
void menuBanco() {
  int op = 1;
  while (op != 0) {
    printf(">");
    scanf("%d", &op);
    switch (op) {
    case 1:
      criarTabela();
      opcoesmenu();
      break;
    case 2:
      listarTabelas();
      break;
    case 3:;
      char *nomeTabela = malloc(sizeof(char) * 100);
      printf("Insira o nome da tabela: ");
      scanf("%s", nomeTabela);
      inserirLinhasColuna(nomeTabela);
      free(nomeTabela);
      break;
    case 4:
      printf("Em desenvolvimento...\n");
      break;
    case 5:
      printf("Em desenvolvimento...\n");
      break;
    case 6:
      printf("Em desenvolvimento...\n");
      break;
    case 7:
      nomeTabela = malloc(sizeof(char) * 100);
      printf("Insira o nome da tabela: ");
      scanf("%s", nomeTabela);
      verificarTabelaInexistente(nomeTabela);
      apagarTabela(nomeTabela);
      free(nomeTabela);
      break;
    case 0:
      printf("Até a próxima!\n");
      break;
    default:
      printf("Opção inválida! Selecione uma das opções:\n");
      printf(
          "1- Criar Tabela\n2- Listar Tabelas\n3- Adicionar valor a tabela\n4- "
          "listar Dados da tabela\n5- Pesquisar valor de uma tabela\n6- Apagar "
          "valor da tabela\n7- Apagar tabela\n0- Sair\n");
      break;
    }
  }
}

void opcoesmenu() {
  printf("abaixo as opções do banco:\n");
  printf("1- Criar Tabela\n2- Listar Tabelas\n3- Adicionar valor a tabela\n4- "
         "listar Dados da tabela\n5- Pesquisar valor de uma tabela\n6- Apagar "
         "valor da tabela\n7- Apagar tabela\n0- Sair\n");
}
//____________________________________________________________________________
