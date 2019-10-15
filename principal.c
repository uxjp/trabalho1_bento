#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "metodos.h"

int main(int argc, char const *argv[]) {	
  	double RT[3] = {0, 0, 0};
    int IT[3] = {0,0,0};
    double ER[3] = {0,0,0};
  	int continuar1 = 1;
    int continuar2 = 1;
    int indiceInserirA = 1;

  	printf("DADO MOVIMENTO FÍSICO PELA EQUACAO:\n  f(d) = a*e^d - 4*d^2\n\n a: AMPLITUDE\n d: DESLOCAMENTO\n E: ERRO MAXIMO\n\n\n");
  
  	printf("=== CALIBRANDO PROGRAMA PARA a = 1 e E = 0.0001 ===\n\n\n\n");
	call_metodos(1.000000,0.0001,RT,IT,ER);
  
  	printf("a = %d :\n d1 = %0.20lf com %d iter.\n d2 = %0.20lf com %d iter.\n d3 = %0.20lf com %d iter.\n\n", 1, RT[0], IT[0], RT[1], IT[1], RT[2], IT[2]);

    printf("Erro Relativo:\n ER1 = %0.20lf \n ER2 = %0.20lf \n ER3 = %0.20lf\n\n",ER[0],ER[1],ER[2]);

  	int n,j,i;
  	double a,a_aux;
  	double E;
  	double * A;  // vetor de amplitudes
  	double ** R; // matriz de resultados
    	int ** I; // matriz de iteracoes 
    	double ** ER2; // matriz de erros relativos
	/*    
		Inicia intereração com usuario 
	*/  
  	printf("=========== PRONTO PARA EXECUCAO ===========\n\n\n\n");
	printf("INSIRA O ERRO MAXIMO TAL QUE SEJA POSITIVO MAIOR DO QUE 0\n");
	do {
  		scanf("%lf",&E);
	
	} while (E <= 0);



    while(continuar1){

    printf("\nINSIRA O NUMERO DE AMPLITUDES\n");
  	scanf("%d",&n);


    //validando n
    if (n <=0) {
      printf("INSIRA UM VALOR > 0 \n");

    }

    else { 

      continuar1 = 0;

      //matriz com resultados de d
  	  R = (double **) malloc(n * sizeof(double *));

      //matriz com resultados de k (iteracoes)
      I = (int **) malloc(n * sizeof(int *));

      //matriz com erros relativos
      ER2 = (double **) malloc(n * sizeof(double *));

      //inicializando a matriz R, I e ER2
  	  for(j=1; j<=n; j++) {
  	    R[j-1] = (double*) malloc(sizeof(double)*3);
        I[j-1] = (int*) malloc(sizeof(int)*3);
        ER2[j-1] = (double*) malloc(sizeof(double)*3);
  	    for ( i=0; i<=2; i++) {
  	      R[j-1][i]=0;
          I[j-1][i]=0;
          ER2[j-1][i]=0;
  	    }
  	  }


  	  A = (double *) malloc(n * sizeof(double));
	    printf("INSIRA UM VALOR ENTRE [0 - INFINITO]\n");
  	  while(continuar2){
  	  printf("\nINSIRA O %dº VALOR DE A: ",indiceInserirA);
      scanf("%lf",&a_aux);

      if (validarA(a_aux)){
    	  A[indiceInserirA-1] = a_aux;
    	  indiceInserirA++;

    	  if(indiceInserirA == n + 1){
    		  continuar2 = 0;
    	  }
      }else{
    	  printf("INSIRA UM VALOR ENTRE [0 - INFINITO]\n");
      }  

    }  
  		//exibindo A
  	  printf("\nVETOR DE AMPLITUDES A:\n\n  A = [");
  	  for(j=1;j<=n-1;j++){
  	    printf("%lf,",A[j-1]);
  	  }
  	  printf("%lf]\n\n",A[j-1]);
      		// fim da exibicao de A


  	  for( j = 1; j <= n ; j++) {
  	    printf("\n\n===== EXECUTANDO PARA a = %lf e E = %lf =====\n\n\n", A   [j-1], E) ;
  	    call_metodos( A[j-1], E, R[j-1], I[j-1],ER2[j-1]);
  	  }

	  printf("\n\n================ RESUMO ================\n");
	  printf("d1: Resultado Newton-Raphson\nd2: Resultado Newton-Raphson        Modificado\nd3: Resultado Secante\n\n\n");

  	  for(j=1;j<=n;j++) {
  	    printf("a = %lf: \n\n d1 = %0.20lf com %d iter.\n d2 = %0.20lf com %d iter.\n d3 = %0.20lf com %d iter.\n",A[j-1],R[j-1][0],I[j-1][0],R[j-1][1],I[j-1][1],R[j-1][2],I[j-1][2]);
        printf("\n Erro Relativo:\n ER0 = %0.20lf \n ER1 = %0.20lf \n ER2 = %0.20lf\n\n",ER2[j-1][0],ER2[j-1][1],ER2[j-1][2]);
  	  }
  	  free(A);

	  return 0;

  }
  }
}
