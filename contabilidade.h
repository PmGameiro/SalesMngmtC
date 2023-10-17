typedef struct mes* Mensal;
typedef struct contree* Cont;
typedef struct cont* Contabilidade;
typedef struct factTotal* Fmes;
typedef struct factTotal* Ftotal [12];
typedef struct printct* PrintCt;
typedef struct aux12* Aux12;

/* API */

/** Movimentação para a esquerda na arvore*/
Cont goEsqct(Cont t);
/** Movimentação para a direita na arvore*/
Cont goDirct(Cont t);
/**Copia o código do array para o nodo da árvore*/
Cont setstring(Cont t, char x[]);
/**Inicializa o nodo da árvore contabilidade*/
Cont initCont();
/**Inicializa a Struct Mês*/
Cont initMes(Cont k);
/**Devolve o Produto que está no nodo da Árvore*/
char* getKey(Cont k);
/**Mete o nodo direito da Árvore a apontar para dest*/
Cont setDirct(Cont ori, Cont dest);
/**Mete o nodo esquerdo da Árvore a apontar para dest*/
Cont setEsqct(Cont ori, Cont dest);
/**Inicializa a Struct factTotal*/
void initFtotal(Ftotal x);
/** Insere a compra na Árvore de Contabilidade e actualiza a Struct factTotal*/
Contabilidade insereConta(Contabilidade x, char* cliente, char* produto, char tipo, int mes,int quant,float preco,Ftotal f);
/**Devolve a facturação total do Mês n*/
double getFactT(Ftotal f, int n);
/**Devolve o total de vendas do Mês n*/
int getVendasT(Ftotal f, int n);
/**Devolve a facturação feita através de Promoções do mês n*/
double getfacturacaoP(Cont k, int x);
/**Devolve a facturação feita através de compras Normais do mês n*/
double getfacturacaoN(Cont k, int x);
/** Procura um código na Árvore */
Cont findcodigo(char v[], Cont t);
/**Vai verificar se as vendas foram todos incializadas a 0*/
int verificavendas(Cont t);
/**Insere o nodo Cont na posição n da Contabilidade*/
Contabilidade meteEmCont(Contabilidade x, Cont p, int n);
/**Retorna a àrvore na posição n da Contabilidade*/
Cont daCont(Contabilidade x, int n);
/**Inicializa a Struct Cont*/
Contabilidade initContabilidade ();
/**Procura os Produtos que não foram Comprados e retorna o número de produtos que não forma comprados*/
int catorzeAux(Cont root);
/**Devovle a Estrutura com os códigos dos Produtos que não forma comprados*/
PrintCt quatroAux(Contabilidade root, PrintCt t);
/**Incializa a Struct PrintCt*/
PrintCt initPrintCt(int npal, int ntam);
/**Retorna o parametro npalavras da Struct PrintCt*/
int getTam(PrintCt t);
/**Devolve o Array da Struct PrintCt*/
char* getArray(PrintCt t);
/**Incializa a Struct Aux12, insere os códigos dos Produtos no array da Struct Aux12 e as suas respetivas vendas totais*/
Aux12 dozeAux(int numero, Contabilidade root, int N);
/**Devolve o número de vendas feitas em Promoção do mês x*/
int getVendasP(Cont k, int x);
/**Devolve o número de vendas Normais do mês x*/
int getVendasN(Cont k, int x);
/**Retorna o número da palavra na posição g do ArrayD*/
int getAux12D(Aux12 t, int g);
/**Retorna o máximo na posição g do Array C da Struct Aux12*/
int getAux12C(Aux12 t, int g);
/**Devolve o número de vendas  na posição g do Array B da Struct Aux12*/
int getAux12B(Aux12 t, int g);
/**Retorna o character na posição g do Array A da Struct Aux12*/
char getRChara(Aux12 t, int g);
/**Encontra o máximo  e a sua posição no Array B , guardando-o no Array C e a sua posição no Array D, pondo  o maximo do array B a 0*/
Aux12 nmaximos(Aux12 t,int indice);
/**Conta os nodos da Árvore Cont*/
int contaaux(Cont x);
/**Utiliza a contaaux para contar os nodos Todos da Struct Contabilidade*/
int contanodosCT( Contabilidade t);
/**Retorn array da struct*/
char * daArrayAux12(Aux12 t);
/** libertacao de memoria de todos os elementos da Struct Contabilidade */
void freeContabilidade (Contabilidade root);
