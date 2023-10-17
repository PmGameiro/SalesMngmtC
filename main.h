/* API */

/** Faz um copia da arvore de produtos para a arvore de contabilidade com vendas e facturazação iniciadas a zero */
Cont insereaux (Cont t, Produto r);
/** Utiliza a insereaux para fazer uma copia dos produtos para todas as posicoes do array */
void inserePinCt(Contabilidade t, CatalogoProdutos r);
/** Faz um copia da arvore de produtos para a arvore Compra */
Compra insereaux1 (Compra t, Cliente r);
/** Utiliza a insereaux1 para fazer uma copia dos clientespara todas as posicoes do array */
void insereCinCmp (Compras t, CatalogoClientes r);
/** Dando um mês m e um codigo de produto valido v, determina e apresenta o número total de vendas em modo N e em modo P, e o total facturado com esse produto em tal mês */
void Querie3 (int m, codProd v);
/**	Dando um intervalo fechado de meses, por exemplo [2..6], determinar o total de compras registadas nesse intervalo e o total facturado */
void Querie7(int z, int y, Ftotal f);
/** Imprime as palavras de um array */
int imprimeaux(char v[], int q, int x, int z, int indice);
/** Faz a navegação das paginas */
void imprime( char *a, int nsize, int npalavras);
/** Determinar a lista de códigos de produtos (e o seu número total), que ninguém comprou */
void Querie4 ();
/**. Cria um ficheiro excell, contendo para cada mes em que ha compras registadas, o numero de compras realizadas e o numero total de clientes que realizam tais compras */
void Querie11(int n[]);
/** Determina o numero de clientes registados que não realizam compras bem como o número de produtos que ninguém comprou */
void Querie14();
/** Dando um codigo de cliente determina quais os 3 produtos que mais comprou durante o ano */
void Querie13 (codCli cliente);
/** Dando um codigo de cliente, cria uma tabela com o numero total de produtos comprados, mes a mes (para meses que nao comprou esta a 0) */
void Querie5(codCli client);
/** Funcao auxiliar da querie9 que vai imprimir a lista de codigos de produtos e as suas venda/s */
void imprime9(PrintCompras x);
/** Dando um código de cliente e um mes, determina a lista de codigos de produtos que mais comprou, por ordem descendente */
void Querie9 (codCli cliente, int mes);
/** Funcao auxiliar da querie 12 que vai efectuar a impressao dos codigos para o ecra */ 
float imprime12(Aux12 r, int N, int tam);
/** Determina a lista de codigos de clientes que realizam compras em todos os meses do ano */
void Querie10 ();
/** Dando um codigo de produto, determina os codigos dos clientes que o compram, distinguindo entre compra N e compra P */
void Querie8(codProd produto);
/** Cria uma lista dos N produtos mais vendidos em todo o ano, indicando o número total de clientes e o número de unidades vendidas */
void Querie12();