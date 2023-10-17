#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contabilidade.h"

struct printct{
    char *a;
    int npalavras;
    int nsize;  
};

struct mes{
	int vendasN;
	int vendasP;
	double facturacaoN;
	double facturacaoP;
};

struct aux12 {
  char *a;
  int *b;
  int *c;
  int *d;
  int e;
};

struct contree{
	char* key;
	Mensal mes[12];
	struct contree *esq, *dir;
};

struct cont{
	Cont contabil [26];
};

struct factTotal{
	int vendasT;
	double facturacaoT;
};

int contaaux(Cont x){
  if(x==NULL) return 0;
  return 1+(contaaux(x->esq))+(contaaux(x->dir));
}
int contanodosCT( Contabilidade t){
  int n=0;
  int i=0;
  for(i=0; i<26; i++){
    n=n+contaaux(t->contabil[i]);
  }
  return n;
}
int soma(Cont x){
	int soma=0,i;
	for(i=0;i<12;i++){
		if(x->mes[i]!=NULL)
			soma+=x->mes[i]->vendasN+x->mes[i]->vendasP;
	}
	return soma;
}

void initFtotal(Ftotal x){
	int i;
	for (i=0;i<12;i++){
		x[i]=(Fmes) malloc(sizeof(struct factTotal));
		x[i]->vendasT=0;
		x[i]->facturacaoT=0;
	}
}

int getVendasT(Ftotal f, int n){
	return f[n]->vendasT;
}

double getFactT(Ftotal f, int n){
	return f[n]->facturacaoT;
}

Cont insereTok(char* prods, float preco, int quantidade, char tipo, char* clis, int mes, Cont k, Ftotal f){
	if(strcmp(prods, k->key)==0){
		if(tipo=='N'){
			k->mes[mes]->vendasN++;
			k->mes[mes]->facturacaoN = ((k->mes[mes])->facturacaoN) + (quantidade*preco);
			f[mes]->facturacaoT = (f[mes]->facturacaoT) + (quantidade*preco);
			f[mes]->vendasT++;
		}
		else{
			k->mes[mes]->vendasP++;
			k->mes[mes]->facturacaoP = ((k->mes[mes])->facturacaoP)+(quantidade*preco);
			f[mes]->facturacaoT = (f[mes]->facturacaoT) + (quantidade*preco);
			f[mes]->vendasT++;
		}
	}
	else {
		if(strcmp(prods, k->key)<0){
			k->esq=insereTok(prods,preco,quantidade,tipo,clis,mes, k->esq,f);
		}
		else k->dir=insereTok(prods,preco,quantidade,tipo,clis,mes, k->dir,f);
	}
	return k;
}

Contabilidade insereConta(Contabilidade x, char* cliente, char* produto, char tipo, int mes,int quant,float preco,Ftotal f){
  int letra;
  letra=produto[0]%65;
  x->contabil[letra]=insereTok(produto,preco,quant,tipo,cliente,mes, x->contabil[letra],f);
  return x;
}

Cont findcodigo(char v[], Cont t){
    if(strcmp(v, t->key)<0 )
        return findcodigo( v, t->esq);
    else if( strcmp(v, t->key)>0 )
        return findcodigo( v, t->dir);
    	else
        return t;
}

Contabilidade initContabilidade (){
	int i;
	Contabilidade x;
	x=(Contabilidade) malloc (sizeof(struct cont));
	for(i=0;i<26;i++) x->contabil[i]=NULL;
	return x;
}

Cont daCont(Contabilidade x, int n){
    return (x->contabil[n]);
}

Contabilidade meteEmCont(Contabilidade x, Cont p, int n){
    x->contabil[n]=p;
    return x;
}

char* getKey(Cont k){
 	return k->key;
}

Cont initMes(Cont k){
 	int i;
 	for(i=0;i<12;i++){
 	k->mes[i]=(Mensal)malloc(sizeof(struct mes));
 	(k->mes[i])->vendasN=0;
 	(k->mes[i])->vendasP=0;
 	(k->mes[i])->facturacaoN=0;
 	(k->mes[i])->facturacaoP=0;
 	}
 	return k;
}

Cont initCont(){
 	Cont t;
 	t=(Cont)malloc(sizeof(struct contree));
 	return t;
}

Cont goEsqct(Cont t){
 	return t->esq;
}

Cont goDirct(Cont t){
 	return t->dir;
}

Cont setDirct(Cont ori, Cont dest){
	ori->dir=dest;
 	return ori;
}

Cont setEsqct(Cont ori, Cont dest){
 	ori->esq=dest;
 	return ori;
}

int verificavendas(Cont t){
 	int i, n=0, p=0;
 	for(i=0;i<12;i++){
 		if(t->mes[i]->vendasP==0) p++;
 		if(t->mes[i]->vendasN==0) n++;
 	}
 	return (p==12 && n==12);
}

int catorzeAux(Cont root){
  int i=0;
  Cont current, pre;
  if(root == NULL)
     return 0; 
 
  current = root;
  while(current != NULL)
  {                 
    if(current->esq == NULL)
    {
      if(verificavendas(current))
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
        if(verificavendas(current))
      		i++;
        current = current->dir;      
      } /* End of if condition pre->dir == NULL */
    } /* End of if condition current->esq == NULL*/
  } /* End of while */
  return i;
}

double getfacturacaoN(Cont k, int x){
  	return ((k->mes[x])->facturacaoN);
}

double getfacturacaoP(Cont k, int x){
  return ((k->mes[x])->facturacaoP);
}

int getVendasN(Cont k, int x){
    return ((k->mes[x])->vendasN);
}

int getVendasP(Cont k, int x){
    return ((k->mes[x])->vendasP);
}

Cont setstring(Cont t, char x[]){
 	t->key=(char *) calloc(strlen(x),sizeof(char));
 	strcpy(t->key,x);
 	return t;
}

PrintCt quatroAux(Contabilidade root, PrintCt t){
  int size=300,i=0,p;
  Cont current, pre;
  if(root == NULL) return 0;
  for(p=0;p<26;p++){
  current = root->contabil[p];
  if(current!=NULL) t->nsize=strlen(current->key);
  while(current != NULL)
  {                 
    if(current->esq == NULL)
    {
      if(verificavendas(current)){
        if(i>size/2){
          size=size*2;
          t->a=(char *)realloc(t->a, sizeof(char)*size);
        }
        strcpy((t->a)+i,current->key);
        i=i+6;
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
        if(verificavendas(current)){
          if(i>size/2){
            size=size*2;
            t->a=(char*)realloc(t->a, sizeof(char)*size);
          }
          strcpy((t->a)+i,current->key);
          i=i+6;
        }
        current = current->dir;      
      } /* End of if condition pre->dir == NULL */
    } /* End of if condition current->esq == NULL*/
  } /* End of while */
  }
  t->npalavras=i/t->nsize;
  return t;
}

PrintCt initPrintCt(int npal, int ntam){
    PrintCt x;
    x=(PrintCt) malloc(sizeof(struct printct));
    x->a=(char *) calloc((npal*ntam),sizeof(char));
    x->nsize=ntam;
    return x;
}

int getTam(PrintCt t){
  return t->npalavras;
}

char * getArray(PrintCt t){
  return t->a;
}

char * daArrayAux12(Aux12 t){
  return t->a;
}

Aux12 nmaximos(Aux12 t,int indice){
  int i,j=0;
  int max=0;
  for(i=0; i<(t->e); i++){
    if((t->b[i])>max){
      max=t->b[i];
      j=i;
    }
  }
  t->b[j]=0;
  t->c[indice]=max;
  t->d[indice]=j;
  return t;
}

void freeContabilidade (Contabilidade root){
  int p;
  Cont current, pre;
  for(p=0;p<26;p++){
  if(root == NULL)
     return; 
  current = root->contabil[p];
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

Aux12 dozeAux(int numero, Contabilidade root, int N){
  int i,j=0, l=0;
  int h;
  Aux12 t=(Aux12) malloc(sizeof (struct aux12));
  t->a=(char*) calloc(numero*6,sizeof(char*));
  t->b=(int *) calloc(numero, sizeof(int));
  t->c=(int *) calloc(N, sizeof(int));
  t->d=(int *) calloc(N, sizeof(int));
  for(i=0;i<26;i++){
  Cont current, pre;
  if(root == NULL)
     return 0;
  
  current = root->contabil[i];
  while(current != NULL)
  {                
    if(current->esq == NULL)
    {
      for(h=0; current->key[h]; h++){
        t->a[j]=current->key[h];
        j++;
      }
      t->b[l]=soma(current);
      l++;
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
        for(h=0; current->key[h]; h++){
        t->a[j]=current->key[h];
        j++;
      }
      t->b[l]=soma(current);
        l++;
        current = current->dir;     
      } 
    } 
  }
    }
    t->e=l;
  return t;
}
char getRChara(Aux12 t, int g){
  return t->a[g];
}
int getAux12B(Aux12 t, int g){
  return t->b[g];
}
int getAux12C(Aux12 t, int g){
  return t->c[g];
}
int getAux12D(Aux12 t, int g){
  return t->d[g];
}
