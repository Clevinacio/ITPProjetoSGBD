#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *nomeArquivo = "Metadados.txt";

  FILE *arquivo = fopen(nomeArquivo, "r");

  if (arquivo == NULL) {
    printf("ERRO\n");
    return 1;
  }
  printf("Todas as tabelas do banco:\n");
  char *buffer = malloc(sizeof(char) * 100);
  while (fgets(buffer, 100, arquivo) != NULL) {
    printf("%s", buffer);
  }

  fclose(arquivo);
  free(buffer);
  return 0;
}
