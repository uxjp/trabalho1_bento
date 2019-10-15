#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "metodos.h"

int main(int argc, char const *argv[]) {	
  	double RT[3] = {0, 0, 0};
  	int continuar1 = 1;
    int continuar2 = 1;
    int indiceInserirA = 1;

  	printf("DADO MOVIMENTO FÍSICO PELA EQUACAO:\n  f(d) = a*e^d - 4*d^2\n\n a: AMPLITUDE\n d: DESLOCAMENTO\n E: ERRO MAXIMO\n\n\n");
  
  	printf("=== CALIBRANDO PROGRAMA PARA a = 1 e E = 0.0001 ===\n\n\n\n");
	call_metodos(1.000000,0.0001,RT);
  
  	printf("a = %d | d1 = %0.20lf | d2 = %0.20lf | d3 = %0.20lf\n\n", 1, RT[0], RT[1], RT[2]);

  	int n,j,i;
  	double a,a_aux;
  	double E;
  	double * A;  // vetor de amplitudes
  	double ** R; // matriz da interaçoes 

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

  	  R = (double **) malloc(n * sizeof(double *));

      //inicializando a matriz R
  	  for(j=1; j<=n; j++) {
  	    R[j-1] = (double*) malloc(sizeof(double)*3);
  	    for ( i=0; i<=2; i++) {
  	      R[j-1][i]=0;
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

  	  for( j = 1; j <= n ; j++) {
  	    printf("\n\n===== EXECUTANDO PARA a = %lf e E = %lf =====\n\n\n", A   [j-1], E) ;
  	    call_metodos( A[j-1], E, R[j-1]);
  	  }

	  printf("\n\n================ RESUMO ================\n");
	  printf("d1: Resultado Newton-Raphson\nd2: Resultado Newton-Raphson        Modificado\nd3: Resultado Secante\n\n\n");

  	  for(j=1;j<=n;j++) {
  	    printf("a = %lf | d1 = %0.20lf | d2 = %0.20lf | d3 = %0.20lf\n",A     [j-1],R[j-1][0],R[j-1][1],R[j-1][2]);
  	  }
  	  free(A);

	  return 0;

  }
  }
}