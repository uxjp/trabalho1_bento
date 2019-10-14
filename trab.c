#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Metodo principal chama os demais metodos, armazena os resultados dos
// respectivos métodos em uma estrutura de dados
void call_metodos(double a_funcao, double E,double* R);


double call_isolamento(double a_funcao, double *a_intervalo, double *b_intervalo);
void isolamento(double a_funcao ,double* a_isolamento, double* b_isolamento);
double resolver_f(double a, double d);


double call_newton_raphson(double a_funcao, double raiz0, double E);
double newton_raphson(double x_barra, double f, double f_linha);
//     resolver_f
double resolver_f_linha(double a, double d);
double erro(double x_barra_anterior, double x_barra_novo);


double call_newton_raphson_modificado(double a_funcao, double raiz0, double E);
//     resolver_f
//     resolver_f_linha
//     newton_raphson
//	   erro


double call_metodo_secante(double a_funcao, double a_intervalo, double b_intervalo, double E);
//     erro
//     resolver_f
double numerador_secante(double a_funcao, double a_intervalo, double b_intervalo);
double denominador_secante(double a_funcao, double a_intervalo, double b_intervalo);
int validarA(double a);


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

  	printf("INSIRA O ERRO MAXIMO\n");
  	scanf("%lf",&E);



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

int validarA(double a){

	if(a < 0){
		return 0;
	}

	return 1;
}



void call_metodos(double a_funcao, double E, double * R) {	

	double a, b, isolamento;
	a = 0;
	b = 0;


	isolamento = call_isolamento(a_funcao, &a, &b);
	printf("\n\n a=%lf,isolamento=%lf \n\n",a_funcao,isolamento);

 
	R[0] = call_newton_raphson(a_funcao, isolamento, E);
	printf("RESULTADO NEWTON RAPHSON = %0.20lf\n\n========================================\n\n\n", R[0]);


	R[1] = call_newton_raphson_modificado(a_funcao, isolamento, E);
	printf("RESULTADO NEWTON RAPHSON MODIFICADO = %0.20lf\n\n========================================\n\n\n", R[1]);


	R[2] = call_metodo_secante(a_funcao, a, b, E);
	printf("\nRESULTADO SECANTE = %0.20lf\n\n========================================\n\n\n", R[2]);	

}


// ---------------------  Funçoes para Metodo Newton Raphson
double call_newton_raphson(double a_funcao, double raiz0, double E) {

  	printf("\n======== EXECUCAO NEWTON RAPHSON ========\n\n\n");

	double f, f_linha, err, x_anterio, x_atual;
	int k = 1;
  	int i=0;

	f = resolver_f(a_funcao, raiz0);
	f_linha = resolver_f_linha(a_funcao, raiz0);
	x_atual = newton_raphson(raiz0, f, f_linha);
	err = erro(raiz0, x_atual);
	
  	printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,raiz0,i,f);

	while(err > E || fabs(f) > E) {	
    i++;


		x_anterio = x_atual;
		f = resolver_f(a_funcao, x_anterio);
		f_linha = resolver_f_linha(a_funcao, x_anterio);
		x_atual = newton_raphson(x_anterio, f, f_linha);		
		err = erro(x_atual, x_anterio);

    	printf("x%d = %0.20lf f(x%d) = %0.20lf\n", i, x_anterio, i, f);	
		k++;
	}


  	f = resolver_f(a_funcao, x_atual);
  	printf("x%d = %0.20lf f(x%d) = %0.20lf\n\n",i+1,x_atual,i+1,f);	

	return x_atual;
}

double newton_raphson(double x_barra, double f, double f_linha) {
	/*
	 *Aplicação do método de Newton Raphson
	 */
	return x_barra - (f / f_linha);
}


//  ---------------------  Funçoes para Metodo Newton Raphson MODIFICADO  ----------
double call_newton_raphson_modificado(double a_funcao, double raiz0, double E) {	

    printf("\n=== EXECUCAO NEWTON RAPHSON MODIFICADO ===\n\n\n");

	double f, f_linha, err, x_anterio, x_atual;
	int k = 1;
  	int i = 0;

	f = resolver_f(a_funcao, raiz0);
	f_linha = resolver_f_linha(a_funcao, raiz0);
	x_atual = newton_raphson(raiz0, f, f_linha);
	err = erro(raiz0, x_atual);

    printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,raiz0,i,f);

	while(err > E || fabs(f) > E){			
        i++;	

		x_anterio = x_atual;
		f = resolver_f(a_funcao, x_anterio);
		x_atual = newton_raphson(x_anterio, f, f_linha);		
		err = erro(x_atual, x_anterio);


        printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,x_anterio,i,f);
		k++;
	}


    f = resolver_f(a_funcao, x_atual);
    printf("x%d = %0.20lf f(x%d) = %0.20lf\n\n",i+1,x_atual,i+1,f);	

	return x_atual;
}


// ----------------------  Funçoes para Metodo Secante  ----------------------------
double call_metodo_secante(double a_funcao, double a_intervalo, double b_intervalo, double E) {
	
	printf("\n=========== EXECUCAO SECANTE ===========\n\n\n");

	int k = 1;
    int i = 0;
	double x_anterio, x_atual,err,f;

	err = erro(a_intervalo,b_intervalo);

	printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,a_intervalo,i,f);
	f = resolver_f(a_funcao, a_intervalo);
	i++;
	f = resolver_f(a_funcao, b_intervalo);
	printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,b_intervalo,i,f);
	i++;

	while(err > E || fabs(f) > E) {
    	i++;


		x_atual = (numerador_secante(a_funcao, a_intervalo, b_intervalo) / 
			denominador_secante(a_funcao, a_intervalo, b_intervalo));

    a_intervalo = b_intervalo;
	b_intervalo = x_atual;

	k++;
	
	err = erro(a_intervalo, b_intervalo);

    f = resolver_f(a_funcao, x_atual);
    printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,x_atual,i,f);
	}


	return x_atual;
}

double numerador_secante(double a_funcao, double a_intervalo, double b_intervalo){
	return (a_intervalo * resolver_f(a_funcao, b_intervalo)) - (b_intervalo  * resolver_f(a_funcao, a_intervalo));
}

double denominador_secante(double a_funcao, double a_intervalo, double b_intervalo) {

	return resolver_f(a_funcao, b_intervalo) - resolver_f(a_funcao, a_intervalo);

}



// ----------------------  Funçoes usadas no isolamento  --------------------------
double call_isolamento(double a_funcao, double *a_intervalo, double *b_intervalo){
	double media;

	isolamento(a_funcao, a_intervalo, b_intervalo);		

	media = (*a_intervalo + *b_intervalo) / 2;
	if(resolver_f(a_funcao, media) > 0){		
		*a_intervalo = media;
	}else{		
		*b_intervalo = media;
	}

	return (*a_intervalo + *b_intervalo) / 2;
}

void isolamento(double a_funcao ,double* a_isolamento, double* b_isolamento){
	if(a_funcao <= 2){
		while(resolver_f(a_funcao, * a_isolamento) * resolver_f(a_funcao, * b_isolamento) > 0){
			*a_isolamento = *b_isolamento;
			*b_isolamento += 1;
		}		
	}else{		
		while(resolver_f(a_funcao, * a_isolamento) * resolver_f(a_funcao, * b_isolamento) > 0){
			*a_isolamento = *b_isolamento;
			*b_isolamento -= 1;
		}
	}
}



// ----------------------  Funçoes acessorias  ------------------------------------
double resolver_f(double a, double d){
	/*Resolve a equação:f(d) = a*e^d – 4*d^2
	 *M_E = Nº Euler
	 */
	return a * pow(M_E, d) - 4 * pow(d, 2);

}

double resolver_f_linha(double a, double d){
	/*
	 *Resolve a equação:f'(d) = a*e^d – 8*d
	 *M_E = Nº Euler
	 */
	return  a * pow(M_E, d) - 8 * d;
}

double erro(double x_barra_anterior, double x_barra_novo){
	/*
	 *Calcula o erro entre Xk e Xk+1
	 */
	return fabs(x_barra_novo - x_barra_anterior);
}
