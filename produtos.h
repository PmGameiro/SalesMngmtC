typedef struct produto* Produto;
typedef struct cat_produtos* CatalogoProdutos;
typedef char* codProd;
typedef struct printProd* PrintProd;

/* API */

/** Inicializa Catalogo de Produto */
CatalogoProdutos initProd ();
/** Procura codigo de Produto na arvore da sua respetiva letra retornando 1 caso encontre e 0 caso contrario */
int findProd(codProd e, Produto t);
/** Devolve o codigo do produto do nodo da arvore dado */
codProd getProd(Produto n);
/** Retorna sub-Arvore esquerda */
Produto goEsqProd(Produto t);
/** Retorna sub-Arvore esquerda */
Produto goDirProd(Produto t);
/** Retorn a arvore da posicao n do catalogo */
Produto daProduto(CatalogoProdutos x, int n);
/** Insere um codigo de produto no catalogo de produtos */
CatalogoProdutos insereProduto(CatalogoProdutos x, codProd y);
/** Retorna a struct com os codigos dos produtos da arvore */
PrintProd MorrisTraversal(Produto root, PrintProd t);
/** Inicializa a struct PrintProd com npal palavras de tamanho ntam */
PrintProd initPrintProd(int npal, int ntam);
/** Retorna array da struct */
char* daarray ( PrintProd t);
/** Retorna o numero de nodos da arvore dada */
int contaNodosP( Produto t);
/** Retorna o numero de palavras da struct */
int danpalavras(PrintProd c);
/** Retorna o tamanho de cada palavras da struct */
int dansize(PrintProd t);
/** libertacao de memoria de todos os elementos da Struct CatalogoProdutos */
void freeCatalogoProdutos (CatalogoProdutos root);
