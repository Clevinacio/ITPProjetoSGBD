void verificarTabelaExistente(char *nomeTabela);
void verificarTabelaInexistente(char *nomeTabela);
void verificarColuna(int i, char **colunas, char *coluna);
void listarTabelas();
void criarTabela();
void definirTipoColuna(int tipo, int i, char **tipos);
void menuBanco();
void opcoesmenu();
void inserirLinhasColuna(char *nometabela);
void apagarTabela(char *nomeArquivo);
// void separarColunas(char *nomeArquivo, char *colunas, Tabela tabela);
int contadorColunas(char *arquivo);
void criarNovoMetadados();
void listarDadosTabela(char *nomeTabela);

typedef struct {
  char colunas[50][100];
  char tipo[50][30];
} Tabela;
