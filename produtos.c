#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#define ALF 26

struct printProd{
    char *a;
    int npalavras;
    int nsize;  
};

struct produto{
    codProd prod;
    struct produto *esq, *dir;
    int alt;
};

struct cat_produtos{
    Produto CatProduto[26];
};

PrintProd initPrintProd(int npal, int ntam){
    PrintProd x;
    x=(PrintProd) malloc(sizeof(struct printProd));
    x->a=(char *) calloc((npal*ntam),sizeof(char));
    x->nsize=ntam;
    return x;
}

int danpalavras(PrintProd c){
    return c->npalavras;
}

int contaNodosP( Produto t){
  if(t==NULL) return 0;
  else return 1+contaNodosP(t->esq)+ contaNodosP(t->dir);
}
 
/**	Devolve a altura da arvore */
static int alt( Produto n ){
    if( n == NULL )
        return -1;
    else
        return n->alt;
}
 
/**	Devolve o maximo de 2 inteiros */
static int max( int l, int r){
    return l > r ? l: r;
}
 
/**	Efetua uma rotaçao entre o nodo K2 e a sua sub-arvore esquerda */
static Produto single_rotate_with_esq (Produto k2){
    Produto k1 = NULL;
 
    k1 = k2->esq;
    k2->esq = k1->dir;
    k1->dir = k2;
 
    k2->alt = max( alt( k2->esq ), alt( k2->dir ) ) + 1;
    k1->alt = max( alt( k1->esq ), k2->alt ) + 1;
    return k1; /* new root */
}
 
/**	Efetua uma rotaçao entre o nodo K1 e a sua sub-arvore direita */
static Produto single_rotate_with_dir( Produto k1 ){
    Produto k2;
 
    k2 = k1->dir;
    k1->dir = k2->esq;
    k2->esq = k1;
 
    k1->alt = max( alt( k1->esq ), alt( k1->dir ) ) + 1;
    k2->alt = max( alt( k2->dir ), k1->alt ) + 1;
 
    return k2;
}
 
/**	Efetua uma dupla rotaçao esquerda-direita */
static Produto double_rotate_with_esq( Produto k3 ){
    /* Rotate between k1 and k2 */
    k3->esq = single_rotate_with_dir( k3->esq );
 
    /* Rotate between K3 and k2 */
    return single_rotate_with_esq( k3 );
}
 
/**	Efetua uma dupla rotaçao direita-esquerda */
static Produto double_rotate_with_dir( Produto k1 ){
    /* rotate between K3 and k2 */
    k1->dir = single_rotate_with_esq( k1->dir );
 
    /* rotate between k1 and k2 */
    return single_rotate_with_dir( k1 );
}
 
Produto insereProd(codProd e, Produto t ){
    int i=0;
    if( t == NULL )
    {
        t = (Produto)malloc(sizeof(struct produto));
        if( t == NULL )
        {
            fprintf (stderr, "Out of memory!!! (insereProd)\n");
            exit(1);
        }
        else
        {
            int n= strlen(e);
            t->prod = (char*) calloc(n,sizeof(char));
            strcpy(t->prod,e);
            t->alt = 0;
            t->esq = t->dir = NULL;
        }
    }
    else if( strcmp(e,t->prod)<0 )
    {
        t->esq = insereProd( e, t->esq );
        if( alt( t->esq ) - alt( t->dir ) == 2 )
            if( strcmp(e,t->esq->prod)<0 )
                t = single_rotate_with_esq( t );
            else
                t = double_rotate_with_esq( t );
        else i++;
    }
    else if( strcmp(e,t->prod)>0 )
    {
        t->dir = insereProd( e, t->dir );
        if( alt( t->dir ) - alt( t->esq ) == 2 )
            if( strcmp(e,t->dir->prod)>0 )
                t = single_rotate_with_dir( t );
            else
                t = double_rotate_with_dir( t );
        else i++;
    }
    t->alt = max( alt( t->esq ), alt( t->dir ) ) + 1;
    return t;
}

CatalogoProdutos initProd (){
    int i;
    CatalogoProdutos x;
    x=(CatalogoProdutos) malloc (sizeof(struct cat_produtos));
    for(i=0;i<ALF;i++)
        x->CatProduto[i]=NULL;
    return x;
}

void freeCatalogoProdutos (CatalogoProdutos root){
  int p;
  Produto current, pre;
  for(p=0;p<26;p++){
  if(root == NULL)
     return; 
  current = root->CatProduto[p];
  while(current != NULL)
  {                 
    if(current->esq == NULL)
    {
      free(current);
      current = current->dir;      
    }    
    else
    {
      pre = current->esq;
      while(pre->dir != NULL && pre->dir != current)
        pre = pre->dir;
 
      if(pre->dir == NULL)
      {
        pre->dir = current;
        current = current->esq;
      }
      else 
      {
        pre->dir = NULL;
        free(current);
        current = current->dir;      
      }
    }
  }
  }
  free(root);
}

CatalogoProdutos insereProduto(CatalogoProdutos x, codProd y){
    int letra;
    letra=y[0]%65;
    x->CatProduto[letra]=insereProd(y,x->CatProduto[letra]);
    return x;
}

Produto daProduto(CatalogoProdutos x, int n){
    return (x->CatProduto[n]);
}

int findProd(codProd e, Produto t){
    if( t == NULL )
        return 0;
    if( strcmp(e, t->prod)<0 )
        return findProd( e, t->esq );
    else if( strcmp(e, t->prod)>0 )
        return findProd( e, t->dir );
    else
        return 1;
}

Produto goEsqProd(Produto t){
    return (t->esq);
}

Produto goDirProd(Produto t){
    return (t->dir);
}

codProd getProd(Produto n){
    return n->prod;
}

Produto setDirProd(Produto ori, Produto dest){
    ori->dir=dest;
    return ori;
}

Produto setEsqProd(Produto ori, Produto dest){
    ori->esq=dest;
    return ori;
}

PrintProd MorrisTraversal(Produto root, PrintProd t) {
    int i=0;
    Produto current, pre; 
    if(root == NULL) return NULL; 
    current = root; 
    while(current != NULL) { 
        if(current->esq == NULL) { 
            strcpy((t->a)+i,current->prod);
            i=i+t->nsize;
            current = current->dir; 
        } 
        else { 
            pre = current->esq; 
            while(pre->dir != NULL && pre->dir != current) pre = pre->dir; 
            if(pre->dir == NULL) { 
                pre->dir = current; 
                current = current->esq; 
                } 
            else { 
                pre->dir = NULL; 
                strcpy((t->a)+i,current->prod);
                i=i+t->nsize;
                current = current->dir; 
            } 
        }
    }
    t->npalavras=i/t->nsize; 
    return t;
}
char* daarray ( PrintProd t){
    return t->a;
}

int dansize(PrintProd t){
    return t->nsize;
}