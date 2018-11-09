#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*################################################################
  #                      PROJETO ITP 2018.2                      #
  #            Componentes: Cleverton Inácio Bezerra             #
  #                         Nataly Enne                          #
  ################################################################
*/
int main(int argc, char const *argv[]) {
  // metadados é um arquivo que vai salvar o nome da tabela, as colunas e as
  // linhas.
  char *nomeArquivo = "Metadados.txt", *nomeTabela = malloc(sizeof(char) * 200),
       *primaryKey = malloc(sizeof(char) * 100),
       *nomeColuna = malloc(sizeof(char) * 100);
  int quantColunas;
  // abrindo metadados: escreve no arquivo, lê o arquivo.
  FILE *arquivo = fopen(nomeArquivo, "a+");
  if (arquivo != NULL) { // Se arquivo NÂO estiver vazio: IF iniciado.

    printf("Digite o nome da tabela: ");
    scanf("%s", nomeTabela); // recebe do USUÁRIO o nome da tabela.

    char *buffer = malloc(sizeof(char) * 100);
    // lê o arquivo até a quebra de linha  e entra no IF para checá-lo.
    while (fscanf(arquivo, "%s", buffer) != EOF) {

      /* SE nome da tabela inserido pelo USUÁRIO for igual a nome de alguma
      tabela existente no arquivo, ele recusa e pede um nome diferente para a
      tabela. */
      if (strcmp(nomeTabela, buffer) == 0) {
        printf("Tabela já existe! Dê outro nome: ");
        scanf("%s", nomeTabela); // recebe o novo nome.
      }
    }
    /* caso entre no IF e o nome de tabela INSERIDO pelo USUÁRIO seja
       diferente de algu nome de tabela do arquivo ele sai do
       while e digita o nome da chave primária. */
    printf("Digite o nome da chave primária: ");
    scanf("%s", primaryKey); // recebe o nome da chave primária
    fprintf(arquivo, "%s\n Colunas:\n %s ", nomeTabela, primaryKey);
    /*[isso aqui ta imprimindo os valores da tabela]*/

    printf("Digite a quantidade de colunas: ");
    scanf("%d", &quantColunas); // Solicitação de quantidade de colunas
    for (int i = 0; i < quantColunas; i++) {
      printf("Digite o nome da coluna: ");
      scanf("%s", nomeColuna);
      while (fscanf(arquivo, "%s", buffer) != EOF) {
        if (strcmp(nomeColuna, buffer) == 0) {
          printf("Coluna já existe! Dê outro nome: ");
          scanf("%s", nomeColuna); // recebe o novo nome.
        }
      }
      fprintf(arquivo, "%s ", nomeColuna);
    }
    fprintf(arquivo, "\n\n");

    printf("Tabela %s criada com sucesso.\n\n", nomeTabela);

    fclose(arquivo);
    free(nomeTabela);
    free(primaryKey);
    free(buffer);
    free(nomeColuna);
  } else
    printf("Erro na leitura ou criação do arquivo\n");

  return 0;
}
