void menuBanco();
void opcoesmenu();

void criarTabela();

void listarTabelas();

void inserirLinhasColuna(char *nometabela);

void listarDadosTabela(char *nomeTabela);

void apagarTabela(char *nomeArquivo);

int verificarExistencia(char *nomeTabela);
void verificarTabelaExistente(char *nomeTabela);
void verificarTabelaInexistente(char *nomeTabela);
void verificarColuna(int i, char **colunas, char *coluna);
void definirTipoColuna(int tipo, int i, char **tipos);
void criarNovoMetadados();

void adicionarDadoTabela(char *nomeTabela);

typedef struct {
  char *colunas;
  char *tipo;
} Coluna;
