typedef struct cliente* Cliente;
typedef struct cat_cliente* CatalogoClientes;
typedef char* codCli;
typedef struct printCli* PrintCli;

/* API */

/** Inicializa Catalogo de Clientes */
CatalogoClientes initCli ();
/** Procura codigo de Cliente na arvore da sua respetiva letra retornando 1 caso encontre e 0 caso contrario */
int findCli(codCli, Cliente t);
/** Devolve o codigo do cliente do nodo da arvore dado */
codCli getCli(Cliente n);
/** Retorna sub-Arvore esquerda */
Cliente goEsqCli(Cliente t);
/** Retorna sub-Arvore direita */
Cliente goDirCli(Cliente t);
/** Retorna a arvore de clientes da posicao n do catalogo */
Cliente daCliente(CatalogoClientes x, int n);
/** Insere um codigo de cliente no catalogo de clientes */
CatalogoClientes insereCliente(CatalogoClientes x, codCli y);
/** Retorna a struct com os codigos dos clientes da arvore */
PrintCli TravessiaCli(Cliente root, PrintCli t);
/** Retorna o tamanho de cada palavras da struct */
int dansizeCli (PrintCli t);
/** Retorna array da struct */
char* daarrayCli (PrintCli t);
/** Inicializa a struct Print com npal palavras de tamanho ntam */
PrintCli initPrintCli(int npal, int ntam);
/** Retorna o numero de palavras da struct */
int danpalavrasCli(PrintCli c);
/** Retorna o numero de nodos da arvore dada */
int contaNodosC( Cliente t);
/** libertacao de memoria de todos os elementos da Struct CatalogoClientes */
void freeCatalogoClientes (CatalogoClientes root);
