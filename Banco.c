#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*################################################################
  #                      PROJETO ITP 2018.2                      #
  #            Componentes: Cleverton Inácio Bezerra             #
  #                         Nataly Enne da Costa Gonçalo         #
  ################################################################
*/

void verificarTabela(char *nomeTabela);

void verificaColuna(int i, char **colunas, char *coluna);

int main(int argc, char const *argv[]) {
  // metadados é um arquivo que vai salvar o nome da tabela, as colunas e as
  // linhas.
  char *nomeArquivo = "Metadados.itp", *nomeTabela = malloc(sizeof(char) * 200),
       *primaryKey = malloc(sizeof(char) * 100), ext[] = ".itp",
       *coluna = malloc(sizeof(char) * 100);
  int quantColunas;
  // abrindo metadados: escreve no arquivo, lê o arquivo.
  FILE *metadados = fopen(nomeArquivo, "a+"), *arquivoTabela;
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
    arquivoTabela = fopen(nomeTabela,
                          "a+"); // cria um arquivo com o nome da tabela

    /* criando as colunas da tabela*/
    printf("Digite a quantidade de colunas(incluindo chave primária): ");
    scanf("%d", &quantColunas); // solicitação de quantidade de colunas
    char *colunas[quantColunas];
    for (int i = 0; i < quantColunas; i++) {
      // define o comparador como zero para verificar todas as colunas
      colunas[i] =
          malloc(sizeof(char) * 100); // aloca memória para o vetor que irá
                                      // armazenar o nome das colunas
      if (i == 0) {
        printf("Digite o nome da chave primária: ");
        scanf("%s", colunas[i]); // recebe o nome da chave primária
      } else {
        printf("Digite o nome da coluna %d: ", i + 1);
        scanf("%s", coluna); // recebe o nome da coluna

        verificaColuna(i, colunas, coluna);
        strcpy(colunas[i],
               coluna); // passa valor digitador pra array de strings
      }
    }

    for (size_t i = 0; i < quantColunas; i++) { // inserir colunas no arquivo
      if (i == 0) {
        fprintf(arquivoTabela, "%s*|", colunas[i]);
      } else
        fprintf(arquivoTabela, "%s|", colunas[i]);
    }

    printf("Tabela %s criada com sucesso.\n\n", nomeTabela);

    fclose(metadados);
    free(nomeTabela);
    free(primaryKey);
    free(coluna);
  } else
    printf("Erro na leitura ou criação do arquivo\n");

  return 0;
}

void verificarTabela(char *nomeTabela) {
  FILE *metadados = fopen("Metadados.itp", "a+"), *arquivoTabela;
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
}
void verificaColuna(int i, char **colunas, char *coluna) {
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
