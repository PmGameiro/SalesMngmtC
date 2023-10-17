#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "clientes.h"
#include "produtos.h"
#include "contabilidade.h"
#include "compras.h"
#include "main.h"

#define MAXBUFFERPROD 12
#define MAXBUFFERCLI 12
#define MAXBUFFERCOMPRAS 64

CatalogoProdutos prod;
CatalogoClientes cli;
Contabilidade ct;
Compras comp;

Cont insereaux (Cont t, Produto r){
  if(r==NULL) return NULL;
  else{
    t=initCont();
    t=setstring(t,getProd(r));
    t=initMes(t);
    setEsqct(t,insereaux(goEsqct(t),goEsqProd(r)));
    setDirct(t,insereaux(goDirct(t),goDirProd(r)));
    return t;
  }
}

void inserePinCt(Contabilidade t, CatalogoProdutos r){
  int i;
  Produto x;
  Cont y;
  for(i=0;i<26;i++){
    x=daProduto(r,i);
    y=daCont(t,i);
    y=insereaux(y,x);
    t=meteEmCont(t,y,i);
  }
}

Compra insereaux1 (Compra t, Cliente r){
  if(r==NULL) return NULL;
  t=initCompra();
  t=setstring1(t,getCli(r));
  t=initArvProdutos(t);
  setEsqCmp(t,insereaux1(goEsqCompra(t),goEsqCli(r)));
  setDirCmp(t,insereaux1(goDirCompra(t),goDirCli(r)));
  return t;
}

void insereCinCmp (Compras t, CatalogoClientes r){
  int i;
  Cliente x;
  Compra y;
  for(i=0;i<26;i++){
    x=daCliente(r,i);
    y=daCompra(t,i);
    y=insereaux1(y,x);
    t=meteEmCompra(t,y,i);
  }
}

void Querie3 (int m, codProd v){
  int letra;
  Cont c,aux;
  letra=v[0]%65;
  aux=daCont(ct,letra);
  c=findcodigo(v,aux);
  printf("No mes %d em normal efetuou-se %d venda/s e facturou-se %.2f\n",m,getVendasN(c,m-1),getfacturacaoN(c,m-1));
  printf("No mes %d em promocao efetuou-se %d venda/s e facturou-se %.2f\n",m,getVendasN(c,m-1),getfacturacaoP(c,m-1));
}

/** Funçao que devolve faturaçao de um intervalo de meses (7) */
void Querie7(int z, int y, Ftotal f){
  int maxV,x;
  double maxF;
  maxV=maxF=0;
  if (y<z || z<1 || y>12) return;
  x=z;
  while (x<=y){
    maxV+=getVendasT(f,(x-1));
    maxF+=getFactT(f,(x-1));
    x++;
  }
  printf("Entre %d e %d efetuou-se %d vendas e facturou-se %.2f\n",z,y,maxV,maxF);
}

int imprimeaux(char v[], int q, int x, int z, int indice){
  int i=z;
  int r=x; 
  int k=0;
  while(r<q && v[i]!='\0'){
    putchar(v[i]);
    if (k==indice){
      putchar('\n');
      r++;
      k=0;
      i++;
    }
    else{
    i++;
    k++;
    }
  }
  return i;
}



void imprime( char *a, int nsize, int npalavras){
  int f=1;
  int p1=0;
  int l=0;
  int p=20;
  int pagina=1;
  int paginaT=(npalavras/20);
  char flag, flag1;
  if( (npalavras%20)!=0) paginaT++;

  l=imprimeaux(a,p, p1, l, nsize-1);
  while(f!=0){
    printf("página %d           [%d/%d]\n", pagina, pagina, paginaT);
    printf("Deseja continuar a Imprimir? [s/n]  ");
    if(scanf(" %c", &flag));
    if(flag=='n') f=0;
    else{
      
      printf("Deseja ir para a proxima pagina ou voltar para a pagina anterior? [p/a] ");
      
      if(scanf (" %c" ,&flag1));

      if(flag1=='p'){ 
        p1=p;
        p=p+20; 
        l=imprimeaux(a,p, p1, l, nsize-1);
        pagina++;
    }
      else{
        if(p==20) printf("Não existe pagina anterior \n");
        if(pagina==paginaT) printf("Chegou ao fim, não pode avançar\n");
        else {
          p1=p1-20;         
          p=p-20;
          l=l-240;
          l=imprimeaux(a,p, p1, l, nsize-1);
          pagina--;
        }
      }
    }
  }
}

void Querie4 (){
  float seconds;
  clock_t start, end;
  int j;
  PrintCt r;
  start = clock();
  j=strlen(getKey(daCont(ct,0)));
  r=initPrintCt(50,j);
  r=quatroAux(ct, r);
  end = clock();
  imprime(getArray(r),j,getTam(r));
  printf("\nNao foram comprados %d produtos\n",getTam(r));
  seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("time %.4f s\n", seconds);
  free(r);
}

void Querie11(int n[]){
  FILE * fd;
  int i;
  fd = fopen ("compras11.csv", "w+");
  fprintf(fd,"Mes\tCompras\tClientes\n");
  for(i=0;i<12;i++){
    fprintf(fd,"%d\t%d\t%d\n",i+1,n[i],calculaClientes(comp,i));
  }
  fclose(fd);
  printf("Ficheiro csv foi criado com o nome \"compras.csv\" \n");
}

void Querie14(){
  int i,produtos=0,clientes=0;
  Compra x;
  Cont y;
  for (i=0;i<26;i++){
    x=daCompra(comp,i);
    y=daCont(ct,i);
    produtos+=catorzeAux(y);
    clientes+=catorzeAux2(x);
  }
  if(produtos==0)
    printf("Todods os produtos foram comprados\n");
  else
    printf("Ninguem comprou %d produtos\n",produtos);
  if(clientes==0)
    printf("Todos os clientes efetuaram compras\n");
  else
    printf("%d Cliente nao compraram nada\n",clientes);
}

void Querie13 (codCli cliente){
  int posP;
  ArvProdutos b;
  Compra a;
  PrintCompras c,q;
  int i,e,t,o;
  t=i=o=0;
  posP=(cliente[0]%65);
  a=procuraCompra(daCompra(comp,posP),cliente);
  if(a==NULL) printf("O Cliente %s não existe\n",cliente);
  else {
    for (e=0; e<12;e++)
    {
      b=dames(a,e);
      if(b!=NULL) {
        i=i+contanodos(b);
        t=strlen(getProduto(b));
      }
    }
    c=initcPrint(i,t);
    q=initcPrint(i,t);
    i=0;
    for (e=0; e<12; e++)
    {
      b=dames(a,e);
      if(b!=NULL){
      c=MorrisTraversal1(b,c,i);
      i=i+contanodos(b);
      }
    }
    q=eliminaRepetidos(c,q);
    q=sort(q);
    for(i=0;i<3*getnsizePrintCompras(q);i=i+getnsizePrintCompras(q)){
        printf("%s com %d venda/s\n",criaPalavra(daArrayPrintCompras(q),i,i+getnsizePrintCompras(q)),getVendasInd(q,o++));
    }
    free(c);
    free(q);
  }
}

void Querie5(codCli client){
	int letra,i,perc[12];
  float seconds;
  char m;
  Compra x,y;
  FILE * fd;
  clock_t start1, end1, start2, end2;
  start1 = clock();
	letra=client[0]%65;
	x=daCompra(comp,letra);
	y=procuraCompra(x,client);
  for(i=0;i<12;i++)
    perc[i]=percorre(y,i);
	  printf(" -------------------#Cliente: %s#----------------------------------\n",client);
	  printf("|   Mes   | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 | 11 | 12 |\n");
  	printf(" ---------------------------------------------------------------------\n");
	  printf("| Compras |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |\n",perc[0],perc[1],perc[2],perc[3],perc[4],perc[5],perc[6],perc[7],perc[8],perc[9],perc[10],perc[11]);
  	printf(" ---------------------------------------------------------------------\n");
  end1 = clock();
  seconds = ((float)(end1 - start1) / CLOCKS_PER_SEC) * 1e9;
  printf("Deseja guardar a tabela num Ficheiro[s/n]  ");
  if(scanf(" %c",&m));
  if(m=='s'){
    start2 = clock();
    fd = fopen ("tabela.txt", "w+");
    fprintf(fd," -------------------#Cliente: %s#----------------------------------\n",client);
    fprintf(fd,"|   Mes   | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 | 11 | 12 |\n");
    fprintf(fd," ---------------------------------------------------------------------\n");
    fprintf(fd,"| Compras |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |\n",perc[0],perc[1],perc[2],perc[3],perc[4],perc[5],perc[6],perc[7],perc[8],perc[9],perc[10],perc[11]);
    fprintf(fd," ---------------------------------------------------------------------\n");
    fclose(fd);
    printf("A sua tabela foi guardada no ficheiro \"tabela.txt\"\n");
    end2 = clock();
    seconds = ((float)(end1 - start1 + end2 - start2) / CLOCKS_PER_SEC) * 1e9;
  }
    printf("time %.0f ns\n", seconds);
}

void imprime9(PrintCompras x){
  int a,i=0,j=0;
  a=getnpalavrasPrintCompras(x)*getnsizePrintCompras(x);
  for(i=0;i<a;i=i+getnsizePrintCompras(x)){
    printf("%s com %d venda/s\n",criaPalavra(getArrayPrintCompras(x),i,i+getnsizePrintCompras(x)),getVendasInd(x,j++));
  }
}

float imprime12(Aux12 r, int N, int tam){
  int i,inda,npalavras,ciclo1,ciclo2,flag,pagina,p;
  Aux8 j;
  char flag2;
  float seconds;
  clock_t start, end;
  inda=npalavras=i=0;
  seconds=0;
  j=initAux8(5,5,5);
  if(N<=20){
    start = clock();
    printf("Os maximos são:\n");
    while(i<N){
      ciclo1=getAux12D(r,i);
      while(npalavras<ciclo1){
        
        if(inda==0){
          inda=inda+tam-1;
          npalavras++;
        }
        else{
          inda=inda+tam;
          npalavras++;
        } 
      }
      inda++;
      j=oitoAux(comp,j,criaPalavra(daArrayAux12(r),inda,inda+6));
      printf("%s com %d vendas feitas por %d clientes\n",criaPalavra(daArrayAux12(r),inda,inda+6),getAux12C(r,i),getPalP(j)+getPalN(j)); 
      inda=0;
      npalavras=0;
      i++;
      }
      end = clock();
      seconds = (float)(end - start) / CLOCKS_PER_SEC;
    }
    else{
      int paginaT=N/20;
      if(N%20!=0){
        paginaT++;
      }
        flag=pagina=i=0;
        printf("Os Maximos são:\n");
        while(flag!=1){
          start = clock();
            while(p<20 &&i<N){
              if(i>=N) flag=1;
              ciclo2=getAux12D(r,i);
              while(npalavras<ciclo2){
                if(inda==0){
                  inda=inda+tam-1;
                  npalavras++;
                }
                else{
                  inda=inda+tam;
                  npalavras++;
                } 
              }

              inda++;
              j=oitoAux(comp,j,criaPalavra(daArrayAux12(r),inda,inda+6));
              printf("%s com %d vendas feitas por %d clientes\n",criaPalavra(daArrayAux12(r),inda,inda+6),getAux12C(r,i),getPalP(j)+getPalN(j)); 
              inda=0;
              npalavras=0;
              p++;
              i++; 
            }
            pagina++;
            printf("                      pagina [%d/%d]\n\n", pagina, paginaT);
            printf("Deseja continuar a imprimir? [s/n]\n");
            end = clock();
            seconds += (float)(end - start) / CLOCKS_PER_SEC;
            if(scanf(" %c", &flag2));
            if(flag2!='s')flag=1;
            
            if(pagina>=paginaT){
              flag=1; 
              break;
            }
            else p=0;
        }
      }
      free(j);
      return seconds;
}
void Querie9 (codCli cliente, int mes){
  int posP,i,t;
  ArvProdutos b;
  Compra a;
  PrintCompras c;
  posP=(cliente[0]%65);
  a=procuraCompra(daCompra(comp,posP),cliente);
  if(a==NULL) printf("O Cliente %s não existe\n",cliente);
  else {
    b=dames(a,mes-1);
    i=contanodos(b);
    t=strlen(getProduto(b));
    c=initcPrint(i,t);
    c=TravessiaCompra(b,c);
    c=sort(c);
    imprime9(c);
    free(c);
  }
}

void Querie10 (){
  float seconds;
  clock_t start, end;
  PrintCompras c;
  start = clock();
  c=verifica(comp);
  end = clock();
  imprime(getArrayPrintCompras(c),getnsizePrintCompras(c),getnpalavrasPrintCompras(c));
  printf("%d clientes efeturam compras todos os meses\n",getnpalavrasPrintCompras(c));
  seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("time %.4f s\n", seconds);
  free(c);
}

void Querie8(codProd produto){
  int o,i;
  Aux8 r;
  r=initAux8(5,5,5);
  r=oitoAux(comp,r,produto);
  printf("%d Cliente efetuaram compras em Promoçao:\n",getPalP(r));
  o=getPalP(r)*getSize(r);
  for(i=0;i<o;i+=getSize(r))
  printf("%s\n",criaPalavra(getArrayP(r),i,i+getSize(r)));
  printf("%d Cliente efeturam compras Normais:\n",getPalN(r));
  o=getPalN(r)*getSize(r);
  for(i=0;i<o;i+=getSize(r))
  printf("%s\n",criaPalavra(getArrayN(r),i,i+getSize(r)));
  free(r);
}
void Querie12(){
  int z,i=0;
  Aux12 t;
  float seconds;
  clock_t start, end;
  printf("Quantos máximos deseja?  ");
  if(scanf(" %d",&z));
  start = clock();
  t=dozeAux(contanodosCT(ct),ct,z);
  while(i<z){
    t=nmaximos(t,i);
    i++;
  }
  end = clock();
  seconds = (float)(end - start) / CLOCKS_PER_SEC;
  seconds+=imprime12(t, z,strlen(getProd(daProduto(prod,0))));
  printf("time %.4f s\n", seconds);
  free(t);
}

int main(){
  float seconds;
  clock_t start, end;

  PrintProd vv;
  PrintCli h;
  FILE *cpFile,*pFile, *cFile;
  int f=0,i,l,p,flag,k=0,posP,posC,u,jj,cmp[12],quantidade,mes,ok,c;
  float preco;
  char tipo,produto[MAXBUFFERPROD],cliente[MAXBUFFERCLI],pp[50],cc[50],ff[50],*token,q2,q5[MAXBUFFERCLI],gr[MAXBUFFERCOMPRAS];
  codProd prods,mycodProd;
  codCli clis,mycodCli;
  Ftotal ft;
  Cliente x;
  Produto y;
  printf(" \n   ### GUESTHIPER ###     \n");
  printf("\t1: Leitura dos Ficheiros (Produtos, Clientes e Compras);\n");
  printf("\t2: Lista de produtos começados por uma dada letra;\n");
  printf("\t3: Numero total de vendas N e P e total faturado de um determinado produto num certo mes;\n");
  printf("\t4: Lista de Produto que ninuem comprou;\n");
  printf("\t5: Tabela com total de produtos comprados mes a mes de um cliente;\n");
  printf("\t6: Lista de Cliente começados por uma dada letra;\n");
  printf("\t7: Total de compras registadas num determinado intervalo de meses e o total faturado;\n");
  printf("\t8: Lista de clientes que compraram um determinado Produto;\n");
  printf("\t9: Lista de Produto que um cliente mais comprou;\n");
  printf("\t10: Lista de Cliente que realizaram compras todos os meses do ano;\n");
  printf("\t11: Criaçao de ficheiro CSV contendo para cada mes o numero de compras realizadas e o numero total de cliente que efetuaram tais compras;\n");
  printf("\t12: Lista com os N produtos mais vendidos em todo o ano;\n");
  printf("\t13: Determinar os 3 produtos mais comprados um determinado cliente;\n");
  printf("\t14: Numero de clientes que nao realizaram compras bem como o numero de produtos que ninguem comprou;\n");
  printf("\nQual o numero da operaçao que deseja realizar:  ");
  if(scanf("%d",&flag));
  while(flag!=-1){
  switch (flag){
    case 1:
      if(f==1) {
        freeCompras(comp);
        freeCatalogoClientes(cli);
        freeCatalogoProdutos(prod);
        freeContabilidade(ct);
      }
      printf("Qual o nome do ficheiro que contem os produtos: ");
      if(scanf("%s", pp));
      printf("Qual o nome do ficheiro que contem os clientes: ");
      if(scanf("%s", cc));
      printf("Qual o nome do ficheiro que contem as compras:  ");
      if(scanf("%s", ff));
      start = clock();  
      prod=initProd();
      cli=initCli();
      ct=initContabilidade();
      comp=initCompras();
      initFtotal(ft);
      mycodProd=clis=prods=mycodCli="\0";
      p=0;
      pFile = fopen (pp , "r");
      if (pFile == NULL) perror ("Error opening file");
      else {
        while (fgets (produto, MAXBUFFERPROD, pFile) != NULL){
          mycodProd = strtok(produto, "\r\n");
          prod=insereProduto(prod,mycodProd);
          p++;
        }
        prods=(char *) calloc(strlen(mycodProd),sizeof(char));
        fclose (pFile);
      }
      printf("Foram lidos %d produtos do ficheiro \"%s\"\n",p,pp);
      c=0;
      cFile = fopen (cc , "r");
      if (cFile == NULL) perror ("Error opening file");
      else {
        while (fgets (cliente , MAXBUFFERCLI , cFile) != NULL){
          mycodCli = strtok(cliente, "\r\n");
          cli=insereCliente(cli,mycodCli);
          c++;
        }
        clis=(char *) calloc(strlen(mycodCli),sizeof(char));
        fclose (cFile);
      }
      printf("Foram lidos %d clientes do ficheiro \"%s\"\n",c,cc);
      inserePinCt(ct,prod);
      insereCinCmp(comp,cli);
      cpFile =fopen(ff, "r");
      u=preco=quantidade=0;
      tipo='\0';
      for (jj=0;jj<12;jj++)
        cmp[jj]=0;
      if( cpFile == NULL) perror ("Error opening file");
      else{
        while(fgets (gr , 64, cpFile)!=NULL){
          token = strtok(gr, " ");
          while ((token != NULL) && (k<6)){
            switch(k){
              case 0: 
                posP=(token[0]%65);
                y=daProduto(prod,posP);
                if(findProd(token,y)) strcpy(prods,token);
                else {
                  k=6;
                }
                break;
              case 1:
                if(atof(token)>=0) preco=atof(token); 
                else k=6;
                break;
              case 2:
                if(atoi(token)>0) quantidade=atoi(token);
                else k=6;
                break;
              case 3:
                tipo=token[0]; 
                break;
              case 4:
                posC=(token[0]%65);
                x=daCliente(cli,posC);
                if(findCli(token,x)) strcpy(clis,token);
                else {
                  k=6;
                }
                break;
              case 5:
                if(atoi(token)>0 && atoi(token)<13) {
                  mes=atoi(token);
                  cmp[mes-1]++;
                  ct=insereConta(ct,clis,prods,tipo,mes-1,quantidade,preco,ft);
                  comp=insereCompra(comp,clis,prods,tipo,mes-1);
                  u++;
                }
                else k=6;
                break;
            } 
            token= strtok(NULL, " ");
            k++;
          }
          k=0;
        }
      }
      fclose(cpFile);
      f=1;
      printf("Foram lidas %d compras validas do ficheiro \"%s\"\n",u,ff);
      end=clock();
      seconds = (float)(end - start) / CLOCKS_PER_SEC;
      printf("time %.4f s\n", seconds);
      break;
    case 2:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      printf("Qual letra deseja ver (Maiuscula) :  ");
      if(scanf(" %c",&q2));
      start=clock();
      y=daProduto(prod,(q2%65));
      if (y==NULL){
        printf("Nao existem produtos começados por essa letra\n");
        break;
      }
      vv=initPrintProd(contaNodosP(y),strlen(getProd(y)));
      vv=MorrisTraversal(y, vv);
      end=clock();
      seconds = (float)(end - start) / CLOCKS_PER_SEC;
      imprime(daarray(vv),dansize(vv), danpalavras(vv));
      printf("time %.4f s\n", seconds);
      free(vv);
      break;
    case 3:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      printf("Qual e o codigo do produto:  ");
      if(scanf("%s",q5));
      printf("Para qual mes:  ");
      if(scanf("%d",&ok));
      start=clock();
      Querie3(ok,q5);
      end=clock();
      seconds = ((float)(end - start) / CLOCKS_PER_SEC)*1e9;
      printf("time %0.f ns\n", seconds);
      break;
    case 4:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      Querie4();
      break;
    case 5:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      printf("Qual e o codigo do cliente:  ");
      if(scanf("%s",q5));
      Querie5(q5);
      break;
    case 6:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      printf("Qual letra deseja ver:  ");
      if(scanf(" %c",&q2));
      if(q2>=97 && q2<=122) q2-=32;
      start=clock();
      x=daCliente(cli,(q2%65));
      if (x==NULL){
        printf("Nao existem clientes começados por essa letra\n");
        break;
      }
      h=initPrintCli(contaNodosC(x),strlen(getCli(x)));
      h=TravessiaCli(x, h);
      end=clock();
      imprime(daarrayCli(h),dansizeCli(h), danpalavrasCli(h));
      seconds = (float)(end - start) / CLOCKS_PER_SEC;
      printf("time %.4f s\n", seconds);
      free(h);
      break;
    case 7:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      printf("Qual o intervalo de meses que deseja ver:   ");
      if(scanf("%d %d",&i,&l));
      start=clock();
      Querie7(i,l,ft);
      end=clock();
      seconds = ((float)(end - start) / CLOCKS_PER_SEC)*1e9;
      printf("time %.0f ns\n", seconds);
      break;
    case 8:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      printf("Qual e o codigo do produto:  ");
      if(scanf("%s",q5));
      start=clock();
      Querie8(q5);
      end=clock();
      seconds = (float)(end - start) / CLOCKS_PER_SEC;
      printf("time %.4f s\n", seconds);
      break;
    case 9:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      printf("Qual e o codigo do cliente:  ");
      if(scanf("%s",q5));
      printf("Para qual mes:  ");
      if(scanf("%d",&ok));
      start=clock();
      Querie9(q5, ok);
      end=clock();
      seconds = ((float)(end - start) / CLOCKS_PER_SEC)*1e9;
      printf("time %.0f ns\n", seconds);
      break;
    case 10:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      Querie10();
      break;
    case 11:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      start=clock();
      Querie11(cmp);
      end=clock();
      seconds = (float)(end - start) / CLOCKS_PER_SEC;
      printf("time %.4f s\n", seconds);
      break;
    case 12:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      Querie12();
      break;
    case 13:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      printf("Qual e o codigo do cliente:  ");
      if(scanf("%s",q5));
      start=clock();
      Querie13(q5);
      end=clock();
      seconds = ((float)(end - start) / CLOCKS_PER_SEC)*1e9;
      printf("time %0.f ns\n", seconds);
      break;
    case 14:
      if(f==0) {
        printf("Primeiro necessita de efetuar a leitura dos ficheiros (Opçao 1) \n");
        break;
      }
      start=clock();
      Querie14();
      end=clock();
      seconds = (float)(end - start) / CLOCKS_PER_SEC;
      printf("time %.4f s\n", seconds);
      break;
    case 0:
      printf(" \n   ### GUESTHIPER ###     \n");
      printf("\t1: Leitura dos Ficheiros (Produtos, Clientes e Compras);\n");
      printf("\t2: Lista de produtos começados por uma dada letra;\n");
      printf("\t3: Numero total de vendas N e P e total faturado de um determinado produto num certo mes;\n");
      printf("\t4: Lista de Produto que ninuem comprou;\n");
      printf("\t5: Tabela com total de produtos comprados mes a mes de um cliente;\n");
      printf("\t6: Lista de Cliente começados por uma dada letra;\n");
      printf("\t7: Total de compras registadas num determinado intervalo de meses e o total faturado;\n");
      printf("\t8: Lista de clientes que compraram um determinado Produto;\n");
      printf("\t9: Lista de Produto que um cliente mais comprou;\n");
      printf("\t10: Lista de Cliente que realizaram compras todos os meses do ano;\n");
      printf("\t11: Criaçao de ficheiro CSV contendo para cada mes o numero de compras realizadas e o numero total de cliente que efetuaram tais compras;\n");
      printf("\t12: Lista com os N produtos mais vendidos em todo o ano;\n");
      printf("\t13: Determinar os 3 produtos mais comprados um determinado cliente;\n");
      printf("\t14: Numero de clientes que nao realizaram compras bem como o numero de produtos que ninguem comprou;\n");
      break;
    default:
      printf("Nao existe essa opçao, por favor escolha novamente:");
      break;
    }
    printf("\nCaso deseje visualizar novamente o menu insira o valor 0");
    printf("\nPara sair insira -1");
    printf("\nQual o numero da operaçao que deseja realizar: ");
    if(scanf("%d",&flag));
  }
  return 0;
}