#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  int *primaryKey = malloc(sizeof(int) * 100);
  char nomeArquivo[] = "Banco.txt", *nomeTabela = malloc(sizeof(char) * 200);
  FILE *arquivo = fopen(nomeArquivo, "w");
  if (arquivo != NULL) {
    printf("Digite o nome da tabela: ");
    scanf("%s", nomeTabela);
    printf("Digite o nome da chave primária: ");
    scanf("%d", primaryKey);

    printf("Tabela %s criada com sucesso.\n", nomeTabela);
    fclose(arquivo);
    free(nomeTabela);
    free(primaryKey);
  } else
    printf("Erro na leitura ou criação do arquivo\n");

  return 0;
}
