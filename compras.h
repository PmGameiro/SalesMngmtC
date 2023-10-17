typedef struct produtos_compra *ArvProdutos;
typedef struct compra *Compra;
typedef struct compras *Compras;
typedef struct aux8* Aux8;
typedef struct printCompras *PrintCompras;

/* API */

/** Inicializa a arvore de produtos contida no compra para os 12 meses */
Compra initArvProdutos(Compra k);
/** Direciona o nodo esquerda da arvore Compra apontar para dest */
Compra setDirCmp(Compra ori, Compra dest);
/** Direciona o nodo direito da arvore Compra apontar para dest */
Compra setEsqCmp(Compra ori, Compra dest);
/** Inicializa um nodo da arvore Compra */
Compra initCompra();
/** Coloca o codigo de cliente do Compra t igual a string dada */
Compra setstring1(Compra t, char x[]);
/** Coloca a Compra p na posicao do array n na struct das Compras */
Compras meteEmCompra(Compras x, Compra p, int n);
/** Devolve a struct compra, dado um indice e a struct Compras */
Compra daCompra(Compras x, int n);
/** Movimentação para a direita da struct Compra */
Compra goDirCompra(Compra t);
/** Movimentação para a esquerda da struct Compra */
Compra goEsqCompra(Compra t);
/** Inicializa a struct Compras */
Compras initCompras ();
/** Insere a compra na struct de Compras */
Compras insereCompra(Compras x, char* cliente, char* produto, char tipo, int mes);
/** Percorre a arvore Compra devolvendo o numero de clientes que nunca compraram nada */
int catorzeAux2(Compra root);
/** Procura por um dado cliente na struct Compra, devolvendo o nodo onde encontra o cliente */
Compra procuraCompra(Compra j, char* cliente);
/** Retorna o valor das vendas no nodo t para o mes n */
int percorre (Compra t, int n);
/**Calcula o numero de clientes registados que não efectuaram compras */
int calculaClientes(Compras t, int n);
/** Retorna a struct com os codigos de clientes que compraram o produto com o codigo dado */
Aux8 oitoAux(Compras root,Aux8 t, char* produto);
/** Retorna o numero de codigos de clientes que efetuaram compras P da struct Aux8 */
int getPalP(Aux8);
/** Retorna o numero de codigos de clientes que efetuaram compras N da struct Aux8 */
int getPalN(Aux8 t);
/** Retorna o tamanho do codigo inserido na struct Aux8 */
int getSize(Aux8 t);
/** Retorna o array de codigos de clientes que efetuaram compras N da struct Aux8 */
char * getArrayN(Aux8 t);
/** Retorna o numero de codigos de clientes que efetuaram compras P da struct Aux8 */
char * getArrayP(Aux8 t);
/** Devolve uma string dando um array com steings começando no indice i e acabando no indice f */
char* criaPalavra(char* a ,int i, int f);
/** Incializa a struct Aux8 que vai server de auxilio a querie 8 */
Aux8 initAux8(int npaln, int npalp, int ntam);
/** Ordena os valores do array "b" por ordem decrescente */
PrintCompras sort(PrintCompras x);
/** Retorna struct PrintCompras com o codigo de produtos contigos naquela ArvProdutos */
PrintCompras TravessiaCompra(ArvProdutos root, PrintCompras t);
/** Inicializa a struct PrintCompras dando um numero de palavras e um tamanho */
PrintCompras initcPrint(int npal, int ntam);
/** Devolve o codigo do produto contido nesse nodo da arvore ArvProdutos */
char* getProduto(ArvProdutos x);
/** Devolve o numero de nodos contidos na struct ArvProdutos */
int contanodos(ArvProdutos t);
/** Devolve a ArvProdutos de um dado cliente no mes indicado */
ArvProdutos dames (Compra j, int mes);
/** Devolve as strings que estão no array "a" da struct PrintCompras */
char* getArrayPrintCompras(PrintCompras x);
/** Devolve o tamanho das strings que estão na struct PrintCompras */
int getnsizePrintCompras(PrintCompras x);
/** Devolve o numero de palavras contidas no array "a" da struct PrintCompras */
int getnpalavrasPrintCompras(PrintCompras x);
/** verifica os clientes que compraram todos os meses colocando-os na struct PrintCompras */
PrintCompras verifica (Compras root);
/** Da o valor que esta na posicao do array "b" da struct PrintCompras */
int getVendasInd(PrintCompras t, int pos);
/** Coloca os produtos e vendas da ArvProdutos no array "a" da struct PrintCompras */
PrintCompras MorrisTraversal1(ArvProdutos root, PrintCompras t,int i);
/** Retira os elementos retidos, colocando-os numa nova struct */
PrintCompras eliminaRepetidos(PrintCompras x,PrintCompras e);
/** retorna o array de produtos/clientes */
char* daArrayPrintCompras(PrintCompras t);
/** libertacao de memoria de todos os elementos da arvore compras */
void freeCompras (Compras root);