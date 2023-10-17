#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#define ALF 26

struct cliente{
    codCli cli;
    struct cliente *esq, *dir;
    int alt;
};

struct cat_cliente{
    Cliente CatCliente[26];
};

struct printCli{
    char *a;
    int npalavras;
    int nsize;  
};

/** Devolve a altura da arvore */
int alt( Cliente n ){
    if( n == NULL )
        return -1;
    else
        return n->alt;
}
 
int contaNodosC( Cliente t){
  if(t==NULL) return 0;
  else return 1+contaNodosC(t->esq)+ contaNodosC(t->dir);
}

/** Devolve o maximo de 2 inteiros */
static int max( int l, int r){
    return l > r ? l: r;
}
 
/** Efetua uma rotaçao entre o nodo K2 e a sua sub-arvore esquerda */
 
static Cliente single_rotate_with_esq (Cliente k2){
    Cliente k1 = NULL;
 
    k1 = k2->esq;
    k2->esq = k1->dir;
    k1->dir = k2;
 
    k2->alt = max( alt( k2->esq ), alt( k2->dir ) ) + 1;
    k1->alt = max( alt( k1->esq ), k2->alt ) + 1;
    return k1; /* new root */
}
 
/** Efetua uma rotaçao entre o nodo K1 e a sua sub-arvore direita */
static Cliente single_rotate_with_dir( Cliente k1 ){
    Cliente k2;
 
    k2 = k1->dir;
    k1->dir = k2->esq;
    k2->esq = k1;
 
    k1->alt = max( alt( k1->esq ), alt( k1->dir ) ) + 1;
    k2->alt = max( alt( k2->dir ), k1->alt ) + 1;
 
    return k2;
}
 
/** Efetua uma dupla rotaçao esquerda-direita */
static Cliente double_rotate_with_esq( Cliente k3 ){
    /* Rotate between k1 and k2 */
    k3->esq = single_rotate_with_dir( k3->esq );
 
    /* Rotate between K3 and k2 */
    return single_rotate_with_esq( k3 );
}
 
/** Efetua uma dupla rotaçao direita-esquerda */
static Cliente double_rotate_with_dir( Cliente k1 ){
    /* rotate between K3 and k2 */
    k1->dir = single_rotate_with_esq( k1->dir );
 
    /* rotate between k1 and k2 */
    return single_rotate_with_dir( k1 );
}
 
/** Insere um novo produto na AVL t */
Cliente insereCli(codCli e, Cliente t){
    int i=0;
    if( t == NULL )
    {
        /* Create and return a one-Cliente tree */
        t = (Cliente)malloc(sizeof(struct cliente));
        if( t == NULL )
        {
            fprintf (stderr, "Out of memory!!! (insereCli)\n");
            exit(1);
        }
        else
        {
            int n = strlen(e);
            t->cli = (char*) calloc(n,sizeof(char));
            strcpy(t->cli,e);
            t->alt = 0;
            t->esq = t->dir = NULL;
        }
    }
    else if( strcmp(e,t->cli)<0 )
    {
        t->esq = insereCli( e, t->esq );
        if( alt( t->esq ) - alt( t->dir ) == 2 )
            if( strcmp(e,t->esq->cli)<0 )
                t = single_rotate_with_esq( t );
            else
                t = double_rotate_with_esq( t );
        else i++;
    }
    else if( strcmp(e,t->cli)>0 )
    {
        t->dir = insereCli( e, t->dir );
        if( alt( t->dir ) - alt( t->esq ) == 2 )
            if( strcmp(e,t->dir->cli)>0 )
                t = single_rotate_with_dir( t );
            else
                t = double_rotate_with_dir( t );
        else i++;
    }
    t->alt = max( alt( t->esq ), alt( t->dir ) ) + 1;
    return t;
}

CatalogoClientes insereCliente(CatalogoClientes x, codCli y){
    int letra;
    letra=y[0]%65;
    x->CatCliente[letra]=insereCli(y,x->CatCliente[letra]);
    return x;
}

CatalogoClientes initCli (){
    int i;
    CatalogoClientes x;
    x=(CatalogoClientes) malloc (sizeof(struct cat_cliente));
    for(i=0;i<ALF;i++)
        x->CatCliente[i]=NULL;
    return x;
}

Cliente daCliente(CatalogoClientes x, int n){
    return (x->CatCliente[n]);
}

int findCli(codCli e, Cliente t){
    if( t == NULL )
        return 0;
    if( strcmp(e, t->cli)<0 )
        return findCli( e, t->esq );
    else if( strcmp(e, t->cli)>0 )
        return findCli( e, t->dir );
    else
        return 1;
}

Cliente goEsqCli(Cliente t){
    return (t->esq);
}

Cliente goDirCli(Cliente t){
    return (t->dir);
}

codCli getCli(Cliente n){
    return n->cli;
}

void freeCatalogoClientes (CatalogoClientes root){
  int p;
  Cliente current, pre;
  for(p=0;p<26;p++){
  if(root == NULL)
     return; 
  current = root->CatCliente[p];
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
  free (root);
}

PrintCli TravessiaCli(Cliente root, PrintCli t) {
    int i=0;
    Cliente current, pre; 
    if(root == NULL) return NULL; 
    current = root; 
    t->nsize=strlen(current->cli);
    while(current != NULL) { 
        if(current->esq == NULL) { 
            strcpy((t->a)+i,current->cli);
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
                strcpy((t->a)+i,current->cli);
                i=i+t->nsize;
                current = current->dir; 
            }
        } /* End of if condition current->esq == NULL*/ 
    }
    t->npalavras=i/t->nsize; 
    return t;
}
char* daarrayCli (PrintCli t){
    return t->a;
}

int dansizeCli (PrintCli t){
    return t->nsize;
}

PrintCli initPrintCli(int npal, int ntam){
    PrintCli x;
    x=(PrintCli) malloc(sizeof(struct printCli));
    x->a=(char *) calloc((npal*ntam),sizeof(char));
    x->nsize=ntam;
    return x;
}

int danpalavrasCli(PrintCli c){
    return c->npalavras;
}
