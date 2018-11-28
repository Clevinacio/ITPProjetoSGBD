#define ext ".itp"
#define pasta "data/"
#define extDadosTabela ".dat"
#define temp "data/metadados.temp"
#define caminhoMetadados "data/Metadados.itp"
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
  FILE *metadados = fopen(caminhoMetadados, "a+"), *arquivoTabela,
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
        fprintf(arquivoTabela, "%s %s\n", colunas[i], tipos[i]);
      } else
        fprintf(arquivoTabela, "%s %s\n", colunas[i], tipos[i]);
    }
    system("clear");
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
  FILE *arquivo = fopen(caminhoMetadados, "r");

  if (arquivo == NULL) {
    printf("Ainda não existem tabelas\n");
  } else {
    printf("Todas as tabelas do banco:\n");
    char *buffer = malloc(sizeof(char) * 100);
    while (fgets(buffer, 100, arquivo) != NULL) {
      printf("%s", buffer);
    }
    printf("\n");
    free(buffer);
  }
}
//____________________________________________________________________________
// 3 - ADICIONAR VALOR NA TABELA
void adicionarDadoTabela(char *nomeTabela) {
  char *caminho = malloc(sizeof(char) * 50),
       *caminhoDadosTabela = malloc(sizeof(char) * 50),
       *buffer = malloc(sizeof(char) * 100),
       *valores = malloc(sizeof(char) * 100),
       *nomeColuna = malloc(sizeof(char) * 100);
  int cont = 0;
  strcpy(caminho, pasta);
  strcat(caminho, nomeTabela);
  strcat(caminho, ext);
  strcpy(caminhoDadosTabela, pasta);
  strcat(caminhoDadosTabela, nomeTabela);
  strcat(caminhoDadosTabela, extDadosTabela);
  FILE *arquivoColunas = fopen(caminho, "r"),
       *arquivoDadosTabela = fopen(caminhoDadosTabela, "a+");
  while (fgets(buffer, 20, arquivoColunas) != NULL) {

    cont++;
  }
  fseek(arquivoColunas, 0, SEEK_SET);
  for (int i = 0; i < cont; i++) {
    fscanf(arquivoColunas, "%s", nomeColuna);
    printf("Digite o valor a ser inserido para a coluna %s: ", nomeColuna);
    scanf("%s", valores);
    fprintf(arquivoDadosTabela, "%s|", valores);
    fscanf(arquivoColunas, "%s", nomeColuna);
  }
  fclose(arquivoColunas);
  fclose(arquivoDadosTabela);
  free(caminho);
  free(caminhoDadosTabela);
  free(buffer);
  free(valores);
}
//____________________________________________________________________________
// 4- LISTAR DADOS DA TABELA
void listarDadosTabela(char *nomeTabela) {
  char *caminho = malloc(sizeof(char) * 100),
       *caminhoDadosTabela = malloc(sizeof(char) * 100),
       *nomeColuna = malloc(sizeof(char) * 100);
  strcpy(caminho, pasta);
  strcat(caminho, nomeTabela);
  strcat(caminho, ext);
  strcpy(caminhoDadosTabela, pasta);
  strcat(caminhoDadosTabela, nomeTabela);
  strcat(caminhoDadosTabela, extDadosTabela);
  FILE *arquivoDadosTabela = fopen(caminhoDadosTabela, "r"),
       *arquivoTabela = fopen(caminho, "r");

  if (arquivoDadosTabela == NULL || arquivoTabela == NULL) {
    printf("Tabela Digitada não encontrada\n");
  } else {
    printf("Todas os atributos da tabela:\n");
    char *buffer = malloc(sizeof(char) * 100);
    while (fscanf(arquivoTabela, "%s", nomeColuna) != EOF) {
      printf("%s|", nomeColuna);
      fscanf(arquivoTabela, "%s", nomeColuna);
    }
    printf("\n");
    while (fgets(buffer, 100, arquivoDadosTabela) != NULL) {
      printf("%s\n", buffer);
    }
    printf("\n");
    fclose(arquivoDadosTabela);
    fclose(arquivoTabela);
    free(buffer);
    free(nomeColuna);
  }
}
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
  FILE *arquivoOriginal = fopen(caminhoMetadados, "r");
  FILE *arquivoSaida = fopen(temp, "w");

  if (arquivoOriginal == NULL || arquivoSaida == NULL) {
    printf("Erro de Leitura ou Abertura de Arquivo\n");
  }
  char *buffer = malloc(sizeof(char) * 101);
  while (fscanf(arquivoOriginal, "%s", buffer) != EOF) {
    if (strcmp(buffer, nomeArquivo) != 0) {
      printf("%s\n", buffer);
      fprintf(arquivoSaida, "%s\n", buffer);
    }
  }
  system("clear");
  printf("Tabela %s excluída\n\n", nomeArquivo);
  fclose(arquivoOriginal);
  fclose(arquivoSaida);
  arquivoOriginal = fopen(caminhoMetadados, "w");
  arquivoSaida = fopen(temp, "r");
  criarNovoMetadados();
  fclose(arquivoOriginal);
  fclose(arquivoSaida);
  remove(temp);
  free(caminho);
  free(caminhoDadosTabela);
  free(buffer);
}

void criarNovoMetadados() {
  FILE *arquivoOriginal = fopen(temp, "r");
  FILE *arquivoSaida = fopen(caminhoMetadados, "w");

  if (arquivoOriginal == NULL || arquivoSaida == NULL) {
    printf("Erro de Leitura ou Abertura de Arquivo\n");
  }

  char *buffer = malloc(sizeof(char) * 101);
  while (fgets(buffer, 100, arquivoOriginal) != NULL) {
    fprintf(arquivoSaida, "%s", buffer);
  }

  fclose(arquivoOriginal);
  fclose(arquivoSaida);
  free(buffer);
}

//____________________________________________________________________________
// VERIFICAÇÕES
void verificarTabelaExistente(char *nomeTabela) {
  int find = verificarExistencia(nomeTabela);
  while (find == 1) {
    printf("Tabela já existe! Dê outro nome: ");
    scanf("%s", nomeTabela); // recebe o novo nome.
    find = verificarExistencia(nomeTabela);
  }
}

void verificarTabelaInexistente(char *nomeTabela) {
  int find = verificarExistencia(nomeTabela);
  while (find == 0) {
    printf("Tabela não existe! Digite outro nome: ");
    scanf("%s", nomeTabela); // recebe o novo nome.
    find = verificarExistencia(nomeTabela);
  }
}

int verificarExistencia(char *nomeTabela) {
  FILE *metadados = fopen(caminhoMetadados, "r");
  char *buffer = malloc(sizeof(char) * 100);
  int find = 0;
  // lê o arquivo até a quebra de linha  e entra no IF para checá-lo.
  while (fgets(buffer, 100, metadados) != NULL) {
    buffer[strlen(buffer) - 1] = '\0';
    if (strcmp(nomeTabela, buffer) == 0) {
      find = 1;
      free(buffer);
      fclose(metadados);
      return find;
    } else {
    }
  }
  free(buffer);
  fclose(metadados);
  return find;
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
//____________________________________________________________________________
// MENU
void menuBanco() {
  int op = 1;
  while (op != 0) {
    printf(">");
    scanf("%d", &op);
    switch (op) {
    case 1:
      system("clear");
      criarTabela();
      opcoesmenu();
      break;
    case 2:
      system("clear");
      listarTabelas();
      opcoesmenu();
      break;
    case 3:;
      char *nomeTabela = malloc(sizeof(char) * 100);
      printf("Insira o nome da tabela: ");
      scanf("%s", nomeTabela);
      system("clear");
      verificarTabelaInexistente(nomeTabela);
      adicionarDadoTabela(nomeTabela);
      free(nomeTabela);
      opcoesmenu();
      break;
    case 4:
      nomeTabela = malloc(sizeof(char) * 100);
      system("clear");
      printf("Insira o nome da tabela: ");
      scanf("%s", nomeTabela);
      listarDadosTabela(nomeTabela);
      free(nomeTabela);
      opcoesmenu();
      break;
    case 5:
      system("clear");
      printf("Em desenvolvimento...\n");
      opcoesmenu();
      break;
    case 6:
      system("clear");
      printf("Em desenvolvimento...\n");
      opcoesmenu();
      break;
    case 7:
      nomeTabela = malloc(sizeof(char) * 100);
      system("clear");
      printf("Insira o nome da tabela: ");
      scanf("%s", nomeTabela);
      verificarTabelaInexistente(nomeTabela);
      apagarTabela(nomeTabela);
      free(nomeTabela);
      opcoesmenu();
      break;
    case 0:
      system("clear");
      printf("Até a próxima!\n");
      break;
    default:
      system("clear");
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
  printf("Abaixo as opções do banco:\n");
  printf("1- Criar Tabela\n2- Listar Tabelas\n3- Adicionar valor a tabela\n4- "
         "listar Dados da tabela\n5- Pesquisar valor de uma tabela\n6- Apagar "
         "valor da tabela\n7- Apagar tabela\n0- Sair\n");
}
//____________________________________________________________________________
