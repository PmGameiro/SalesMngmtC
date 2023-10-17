#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compras.h"

struct produtos_compra{
	char* prod;
	int vendasN,vendasP;
	int alt;
	struct produtos_compra *esq, *dir;
} ;

struct printCompras{
    char* a;
    int* b;
    int npalavras;
    int nsize;
};

struct aux8{
    char* venN;
    char* venP;
    int npalavrasn;
    int npalavrasp;
    int nsize;  
};

struct compra{
	char* cli;
	ArvProdutos prodCompras [12];
	struct compra *esq, *dir;
};

struct compras{
	Compra Comp[26];
};

int getVendasInd(PrintCompras t, int pos){
  return t->b[pos];
}

int getnsizePrintCompras(PrintCompras x){
    return x->nsize;
}

int getPalN(Aux8 t){
  return t->npalavrasn;
}

int getSize(Aux8 t){
  return t->nsize;
}

int getPalP(Aux8 t){
  return t->npalavrasp;
}

char * getArrayN(Aux8 t){
  return t->venN;
}

char * getArrayP(Aux8 t){
  return t->venP;
}

char* criaPalavra(char* a ,int i, int f){
    int h=0;
    char* b;
    b=(char *) calloc(f-i,sizeof(char));
    while(i<f){
        b[h]=a[i];
        h++;
        i++;
    }
    b[h]='\0';
    return b;
}

/** Devolve a altura da arvore */
static int alt( ArvProdutos n ){
    if( n == NULL )
        return -1;
    else
        return n->alt;
}
 
/** Devolve o maximo de 2 inteiros */
static int max( int l, int r){
    return l > r ? l: r;
}
 
/** Efetua uma rotaçao entre o nodo K2 e a sua sub-arvore esquerda */
 
static ArvProdutos single_rotate_with_esq (ArvProdutos k2){
    ArvProdutos k1 = NULL;
 
    k1 = k2->esq;
    k2->esq = k1->dir;
    k1->dir = k2;
 
    k2->alt = max( alt( k2->esq ), alt( k2->dir ) ) + 1;
    k1->alt = max( alt( k1->esq ), k2->alt ) + 1;
    return k1; /* new root */
}
 
/** Efetua uma rotaçao entre o nodo K1 e a sua sub-arvore direita */
static ArvProdutos single_rotate_with_dir( ArvProdutos k1 ){
    ArvProdutos k2;
 
    k2 = k1->dir;
    k1->dir = k2->esq;
    k2->esq = k1;
 
    k1->alt = max( alt( k1->esq ), alt( k1->dir ) ) + 1;
    k2->alt = max( alt( k2->dir ), k1->alt ) + 1;
 
    return k2;
}
 
/** Efetua uma dupla rotaçao esquerda-direita */
static ArvProdutos double_rotate_with_esq( ArvProdutos k3 ){
    /* Rotate between k1 and k2 */
    k3->esq = single_rotate_with_dir( k3->esq );
 
    /* Rotate between K3 and k2 */
    return single_rotate_with_esq( k3 );
}
 
/** Efetua uma dupla rotaçao direita-esquerda */
static ArvProdutos double_rotate_with_dir( ArvProdutos k1 ){
    /* rotate between K3 and k2 */
    k1->dir = single_rotate_with_esq( k1->dir );
 
    /* rotate between k1 and k2 */
    return single_rotate_with_dir( k1 );
}

/** Insere um novo produto na AVL t */
ArvProdutos insereAux(char* e, ArvProdutos t, char tipo){
  int i;
  i=0;
    if( t == NULL )
    {
        /* Create and return a one-ArvProdutos tree */
        t = (ArvProdutos)malloc(sizeof(struct produtos_compra));
        if( t == NULL )
        {
            fprintf (stderr, "Out of memory!!! (insereAux)\n");
            exit(1);
        }
        else
        {
            int n = strlen(e);
            t->prod = (char*) calloc(n,sizeof(char));
            strcpy(t->prod,e);
            t->alt = 0;
            t->esq = t->dir = NULL;
            if (tipo=='N'){
            	t->vendasN=1;
            	t->vendasP=0;
            }
            else {
            	t->vendasP=1;
            	t->vendasN=0;
            }
        }
    }
    else if( strcmp(e,t->prod)<0 )
    {
        t->esq = insereAux( e, t->esq,tipo );
        if( alt( t->esq ) - alt( t->dir ) == 2 )
            if( strcmp(e,t->esq->prod)<0 )
                t = single_rotate_with_esq( t );
            else
                t = double_rotate_with_esq( t );
        else i++;
    }
    else if( strcmp(e,t->prod)>0 )
    {
        t->dir = insereAux( e, t->dir, tipo );
        if( alt( t->dir ) - alt( t->esq ) == 2 )
            if( strcmp(e,t->dir->prod)>0 )
                t = single_rotate_with_dir( t );
            else
                t = double_rotate_with_dir( t );
        else i++;
    }
    else 
    {
    	if (tipo=='N')
    		t->vendasN++;
    	else 
    		t->vendasP++;
    }
 
    t->alt = max( alt( t->esq ), alt( t->dir ) ) + 1;
    return t;
}

Compra insereCompraAux(Compra c, char* cliente, char* produto, char tipo, int mes){
	if (c==NULL) return NULL;
	if (strcmp(c->cli,cliente)==0)
		c->prodCompras[mes]=insereAux(produto,c->prodCompras[mes],tipo);
	else if(strcmp(cliente,c->cli)<0)
		c->esq = insereCompraAux(c->esq,cliente,produto,tipo,mes);
	else
		c->dir = insereCompraAux(c->dir,cliente,produto,tipo,mes);
	return c;
}

Compra initCompra(){
 	Compra t;
 	t=(Compra)malloc(sizeof(struct compra));
 	return t;
 }

Compras initCompras (){
    int i;
    Compras x;
    x=(Compras) malloc (sizeof(struct compras));
    for(i=0;i<26;i++)
        x->Comp[i]=NULL;
    return x;
}

Compra procuraCompra(Compra j, char* cliente){
    if( j == NULL )
        return NULL;
    if( strcmp(cliente, j->cli)<0 )
        return procuraCompra( j->esq,cliente );
    else if( strcmp(cliente, j->cli)>0 )
        return procuraCompra(j->dir,cliente );
    else
        return j;
}

Compra setstring1(Compra t, char x[]){
 	t->cli=(char *) calloc(strlen(x),sizeof(char));
 	strcpy(t->cli,x);
 	return t;
}

Compra initArvProdutos(Compra k){
 	int i;
 	for(i=0;i<12;i++){
	 	k->prodCompras[i]=NULL;
 	}
 	return k;
}

 Compra setEsqCmp(Compra ori, Compra dest){ 
 	ori->esq=dest;
 	return ori;
 }

 Compra setDirCmp(Compra ori, Compra dest){
 	ori->dir=dest;
 	return ori;
 }

Compra daCompra(Compras x, int n){
	return (x->Comp[n]);
}

Compras meteEmCompra(Compras x, Compra p, int n){
    x->Comp[n]=p;
    return x;
}

Compras insereCompra(Compras x, char* cliente, char* produto, char tipo, int mes){
  int letra;
  letra=cliente[0]%65;
  x->Comp[letra]=insereCompraAux(x->Comp[letra],cliente,produto,tipo,mes);
  return x;
}


Compra goEsqCompra(Compra t){
 	return (t->esq);
}

Compra goDirCompra(Compra t){
 	return (t->dir);
}

ArvProdutos procuraProdutoNaArvore(ArvProdutos j, char* produto){
  ArvProdutos k=j;
  if( k == NULL )
    return NULL;
  if( strcmp(produto, k->prod)<0 )
    return procuraProdutoNaArvore( k->esq,produto );
  else if( strcmp(produto, k->prod)>0 )
    return procuraProdutoNaArvore(k->dir,produto );
  else 
    return k;
}

int cmpAux(ArvProdutos t, char* produto){
  int k=5;
  ArvProdutos j=procuraProdutoNaArvore(t,produto);
  if (j==NULL) return k;
  if(j->vendasN>0 && j->vendasP==0) k=1;
  if(j->vendasN>0 && j->vendasP>0) k=0;
  if(j->vendasN==0 && j->vendasP>0) k= -1;
  return k;
}

int veVendas(Compra t, char* produto){
  int i,j,a,n,p;
  int k=5;
  a=n=p=0;
  for(i=0;(i<12 && a==0);i++){
    j=cmpAux(t->prodCompras[i],produto);
    if(j==0) a=1;
    if(j==1) n=1;
    if(j==-1) p=1;
    if(n==1 && p==1) a=1;
  }
  if(a==1) k=0;
  if(n==1 && p!=1) k=1;
  if(n!=1 && p==1) k=-1;
  return k;
}

Aux8 initAux8(int npaln, int npalp, int ntam){
    Aux8 x;
    x=(Aux8) malloc(sizeof(struct aux8));
    x->venP=(char *) calloc((npalp*ntam),sizeof(char));
    x->venN=(char *) calloc((npaln*ntam),sizeof(char));
    x->nsize=ntam;
    return x;
}

ArvProdutos cloneArv(ArvProdutos p, ArvProdutos t){
  if(p==NULL) return NULL;
  t=(ArvProdutos) malloc(sizeof(struct produtos_compra));
  t->prod=(char *) calloc(strlen(p->prod),sizeof(char));
  strcpy(t->prod,p->prod);
  t->vendasN=p->vendasN;
  t->vendasP=p->vendasP;
  t->alt=p->alt;
  t->dir=cloneArv(p->dir,t->dir);  
  t->esq=cloneArv(p->esq,t->esq);
  return t;
}

Compra cloneAux(Compra t, Compra n){
  int i;
  if(t==NULL) return NULL;
  n=(Compra) malloc(sizeof(struct compra));
  n->cli=(char *) calloc(strlen(t->cli),sizeof(char));
  strcpy(n->cli,t->cli);
  for(i=0;i<12;i++){
      n->prodCompras[i]=cloneArv(t->prodCompras[i],n->prodCompras[i]);
  }
  n->esq=cloneAux(t->esq,n->esq);
  n->dir=cloneAux(t->dir,n->dir);
  return n;
}

Aux8 oitoAux(Compras root,Aux8 t, char* produto){
  int sizen=50,sizep=50,n=0,p=0;
  int j,i;
  Compra current, pre;
  for(i=0;i<26;i++){
  current = cloneAux(root->Comp[i],current);
  if (current!=NULL) t->nsize=strlen(current->cli);
  while(current != NULL){                 
    if(current->esq == NULL)
    {
      j=veVendas(current,produto);
      if(j!=5){
        if(j==0){
          if(n>sizen/2){
            sizen=sizen*2;
            t->venN=(char *)realloc(t->venN, sizeof(char)*sizen);
          }
          if(p>sizep/2){
            sizep=sizep*2;
            t->venP=(char *)realloc(t->venP, sizeof(char)*sizep);
          }
          strcpy((t->venN)+n,current->cli);
          n=n+t->nsize;
          strcpy((t->venP)+p,current->cli);
          p=p+t->nsize;
        }
        if(j==1){
          if(n>sizen/2){
            sizen=sizen*2;
            t->venN=(char *)realloc(t->venN, sizeof(char)*sizen);
          }
          strcpy((t->venN)+n,current->cli);
          n=n+t->nsize;
        }
        if(j==-1){
          if(p>sizep/2){
            sizep=sizep*2;
            t->venP=(char *)realloc(t->venP, sizeof(char)*sizep);
          }
          strcpy((t->venP)+p,current->cli);
          p=p+t->nsize;
        }
      }
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
        j=veVendas(current,produto);
        if(j!=5){
          if(j==0){
            if(n>sizen/2){
              sizen=sizen*2;
              t->venN=(char *)realloc(t->venN, sizeof(char)*sizen);
            }
            if(n>sizep/2){
              sizep=sizep*2;
              t->venP=(char *)realloc(t->venP, sizeof(char)*sizep);
            }
            strcpy((t->venN)+n,current->cli);
            n=n+t->nsize;
            strcpy((t->venP)+p,current->cli);
            p=p+t->nsize;
          }
          if(j==1){
            if(n>sizen/2){
              sizen=sizen*2;
              t->venN=(char *)realloc(t->venN, sizeof(char)*sizen);
            }
            strcpy((t->venN)+n,current->cli);
            n=n+t->nsize;
          }
          if(j==-1){
            if(p>sizep/2){
              sizep=sizep*2;
              t->venP=(char *)realloc(t->venP, sizeof(char)*sizep);
            }
            strcpy((t->venP)+p,current->cli);
            p=p+t->nsize;
          }
        }
        current = current->dir;      
      } /* End of if condition pre->dir == NULL */
    } /* End of if condition current->esq == NULL*/
  } /* End of while */
  }
  t->npalavrasn=n/t->nsize;
  t->npalavrasp=p/t->nsize;
  return t;
}

int verificaArvore(Compra t){
 	int i, n=0;
 	for(i=0;i<12;i++){
 		if(t->prodCompras[i]==NULL) n++;
 	}
 	return (n==12);
}

int catorzeAux2(Compra root){
  int i=0;
  Compra current, pre;
  if(root == NULL)
     return 0;
 
  current = root;
  while(current != NULL)
  {                 
    if(current->esq == NULL)
    {
      if(verificaArvore(current))
      	i++;
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
        if(verificaArvore(current))
      		i++;
        current = current->dir;      
      } /* End of if condition pre->dir == NULL */
    } /* End of if condition current->esq == NULL*/
  } /* End of while */
  return i;
}

int daVendas (ArvProdutos t){
    if (t==NULL) return 0;
    return (t->vendasN+t->vendasP+daVendas(t->esq)+daVendas(t->dir));
}

int percorre (Compra t, int n){
    return (daVendas(t->prodCompras[n]));
}

int calculaAux(Compra root, int mes){
  int i=0;
  Compra current, pre;
  if(root == NULL)
     return 0;
 
  current = root;
  while(current != NULL)
  {                 
    if(current->esq == NULL)
    {
      if(root->prodCompras[mes]!=NULL)
        i++;
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
        if(root->prodCompras[mes]!=NULL)
            i++;
        current = current->dir;      
      } /* End of if condition pre->dir == NULL */
    } /* End of if condition current->esq == NULL*/
  } /* End of while */
  return i;
}

int calculaClientes(Compras t, int n){
    int i,j=0;
    for(i=0;i<26;i++)
        j+=calculaAux(t->Comp[i],n);
    return j;
}

ArvProdutos dames (Compra j, int mes){
    return (j->prodCompras[mes]);
}

int contanodos(ArvProdutos t){
    if(t==NULL) return 0;
    return 1+(contanodos(t->esq))+(contanodos(t->dir));
}

char* getArrayPrintCompras(PrintCompras x){
  return x->a;
}

char* getProduto(ArvProdutos x){
    return x->prod;
}

PrintCompras initcPrint(int npal, int ntam){
    PrintCompras x;
    x=(PrintCompras) malloc(sizeof(struct printCompras));
    x->a=(char *) calloc((npal*ntam),sizeof(char));
    x->b=(int *) calloc((npal),sizeof(int));
    x->npalavras=npal;
    x->nsize=ntam;
    return x;
}

PrintCompras TravessiaCompra(ArvProdutos root, PrintCompras t) {
    int i=0,p=0;
    ArvProdutos current, pre; 
    if(root == NULL) return NULL; 
    current = root; 
    while(current != NULL) { 
        if(current->esq == NULL) {
            strcpy((t->a)+i,current->prod);
            t->b[p]=(current->vendasN+current->vendasP);
            i=i+t->nsize;
            p++;
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
                t->b[p]=(current->vendasN+current->vendasP);
                i=i+t->nsize;
                p++;
                current = current->dir; 
            }
        }
    }
    return t;
}

PrintCompras trocas (PrintCompras x,int i,int j){
    int e;
    char p;
    e=x->b[i];
    x->b[i]=x->b[j];
    x->b[j]=e;
    i=i*x->nsize;
    j=j*x->nsize;
    for (e=0; e<x->nsize; e++){
        p=x->a[i+e];
        x->a[i+e]=x->a[j+e];
        x->a[j+e]=p;
    }
    return x;
}

PrintCompras sort(PrintCompras x){
    int i,j;
    for(i=0; i<x->npalavras; i++){
        for(j=i+1;j<x->npalavras;j++){
            if(x->b[i]<x->b[j]){
                x=trocas(x,i,j);
            }
        }
    }
    return x;
}

int getnpalavrasPrintCompras(PrintCompras x){
    return x->npalavras;
}


int verificacompras(Compra t){
    int i, x=1;
    for (i=0; i<12; ++i){
       if(t->prodCompras[i]==NULL){
        i=13;
        x=0;
       }
    }
    return x;
} 

PrintCompras verifica (Compras root){
  Compra current, pre;
  int size=300,i=0;
  int p=0;
  PrintCompras t;
  t=(PrintCompras) malloc(sizeof (struct printCompras));
  t->a=(char*) calloc (size,sizeof(char));
  for(p=0;p<26;p++){
  if(root == NULL)
     return 0; 
  current = root->Comp[p];
  if(current!=NULL) t->nsize=strlen(current->cli);
  while(current != NULL)
  {                 
    if(current->esq == NULL)
    {
      if(verificacompras(current)){
        if(i>size/2){
          size=size*2;
          t->a=(char *)realloc(t->a, sizeof(char)*size);
        }
        strcpy((t->a)+i,current->cli);
        i=i+t->nsize;
      }
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
        if(verificacompras(current)){
          if(i>size/2){
            size=size*2;
            t->a=(char*)realloc(t->a, sizeof(char)*size);
          }
          strcpy((t->a)+i,current->cli);
          i=i+t->nsize;
        }
        current = current->dir;      
      } /* End of if condition pre->dir == NULL */
    } /* End of if condition current->esq == NULL*/
  } /* End of while */
  }
  t->npalavras=i/t->nsize;
  return t;
}

void freeCompras (Compras root){
  int p;
  Compra current, pre;
  for(p=0;p<26;p++){
  if(root == NULL)
     return; 
  current = root->Comp[p];
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
      } /* End of if condition pre->dir == NULL */
    } /* End of if condition current->esq == NULL*/
  } /* End of while */
  }
  free (root);
}

PrintCompras eliminaRepetidos(PrintCompras x,PrintCompras e){
    int p,i,t;
    char* b,*r;
    p=t=0;
    b=(char*) calloc(x->nsize,sizeof(char));
    r=(char*) calloc(x->nsize,sizeof(char));
    for(;p<(x->nsize*x->npalavras);p=p+(x->nsize)){
        if(x->a[p]!='\0'){
        strcpy((e->a)+p,criaPalavra(x->a,p,p+(x->nsize)));
        e->b[t]=x->b[t];
        for (i=p+(x->nsize);i<(x->nsize*x->npalavras);i=i+(x->nsize)){
            strcpy(b,criaPalavra(x->a,p,p+(x->nsize)));
            strcpy(r,criaPalavra(x->a,i,i+(x->nsize)));
            if(strcmp(b,r)==0) {
                e->b[t]=e->b[t]+x->b[t];
                x->a[i]='\0';
            }
        }
        t++;
    }
    }
    return e;
}

char* daArrayPrintCompras(PrintCompras t){
  return t->a;
}

PrintCompras MorrisTraversal1(ArvProdutos root, PrintCompras t,int i) { 
  int p;
  ArvProdutos current, pre; 
  p=i;
  i=i*t->nsize;
  if(root == NULL) return NULL; 
  current = root; 
  while(current != NULL) {
    if(current->esq == NULL) {
      strcpy((t->a)+i,current->prod);
      t->b[p]=(current->vendasN+current->vendasP);
      i=i+t->nsize;
      p++;
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
        t->b[p]=(current->vendasN+current->vendasP);
        i=i+t->nsize;
        p++;
        current = current->dir; 
      } 
    } 
  } 
  return t;
}