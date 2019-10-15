#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "metodos.h"

void menu() {
	double RT[3] = {0, 0, 0};
    int IT[3] = {0,0,0};
    double ER[3] = {0,0,0};
  	int continuar1 = 1;
    int continuar2 = 1;
    int indiceInserirA = 1;

  	printf("=========== O PROBLEMA ===========\n\nDado o movimento físico pela equação:\n\tf(d) = a*e^d - 4*d^2\n\na: Amplitude\nd: Deslocamento\nE: Erro Máximo\n\nPrimeiramente executaremos o código conforme o item d).\n");
  
  	printf("\n=== CALIBRANDO PROGRAMA PARA a = 1 e E = 0.0001 ===\n\n");
	call_metodos(1.000000,0.0001,RT,IT,ER);

  	printf("\n================ RESUMO ================\nd1: Resultado Newton-Raphson\nd2: Resultado Newton-Raphson Modificado\nd3: Resultado Secante\n\n~> a = %d:\n\td1 = %0.20lf com %d iter.\n\td2 = %0.20lf com %d iter.\n\td3 = %0.20lf com %d iter.\n\n", 1, RT[0], IT[0], RT[1], IT[1], RT[2], IT[2]);

    printf("   Erro Relativo:\n\tER1 = %0.20lf \n\tER2 = %0.20lf \n\tER3 = %0.20lf\n\n",ER[0],ER[1],ER[2]);

  	int n,j,i;
  	double a,a_aux;
  	float n_aux;
  	double E;
  	double * A;  // vetor de amplitudes
  	double ** R; // matriz de resultados
    int ** I; // matriz de iteracoes 
    double ** ER2; // matriz de erros relativos
	/*    
		Inicia intereração com usuario 
	*/  
  	printf("=========== PRONTO PARA EXECUCAO ===========\n\n");
	
	do {
		printf("~> Insira um Erro Máximo que seja positivo maior do que 0: ");
  		scanf("%lf",&E);
	
	} while (E <= 0);

	printf("\n");
	
	do {
	    printf("~> Insira um número de Amplitudes que seja um inteiro positivo: ");
	  	scanf("%f",&n_aux);
	  	n = n_aux;

	} while (n <= 0 || n != n_aux); // enquanto n for negativo ou não for um inteiro 
	
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
		
		for ( i = 0; i <= 2; i++) {
			R[j-1][i]	= 0;
			I[j-1][i]	= 0;
			ER2[j-1][i]	= 0;
		}
	}

	// vetor de amplitudes
	A = (double *) malloc(n * sizeof(double));

	printf("\n~> Insira um valor pertencente ao intervalo [0-INFINITO] a cada posição do nosso vetor de Amplitudes!\n\n");
	
	while (indiceInserirA != n+1) {
		printf("%dº pos. = ", indiceInserirA);
		scanf("%lf",&a_aux);

		if (a_aux >= 0) {
			A[indiceInserirA-1] = a_aux;
			indiceInserirA++;
		} 
		else {
			printf("ERROR: valor entrado não pertencente ao intervalo [0-INFINITO]!\n");
		}
	}
	
	//exibindo A
	printf("\n~> Vetor de amplitudes A:\nA = [");
	
	for(j=1; j <= n-1; j++)	printf("%lf, ", A[j-1]);

	printf("%lf]\n\n", A[j-1]);
	// fim da exibicao de A

	for( j = 1; j <= n ; j++) {
		printf("\n===============================================================\n\t EXECUTANDO PARA a = %lf e E = %lf\n===============================================================\n", A[j-1], E) ;
		call_metodos( A[j-1], E, R[j-1], I[j-1], ER2[j-1]);
	}

	printf("\n================ RESUMO ================\nd1: Resultado Newton-Raphson\nd2: Resultado Newton-Raphson Modificado\nd3: Resultado Secante\n\n");

	for(j=1; j <= n; j++) {
		printf("~> a = %lf:\n\td1 = %0.20lf com %d iter.\n\td2 = %0.20lf com %d iter.\n\td3 = %0.20lf com %d iter.\n",A[j-1],R[j-1][0],I[j-1][0],R[j-1][1],I[j-1][1],R[j-1][2],I[j-1][2]);
	
		printf("   Erro Relativo:\n\tER0 = %0.20lf \n\tER1 = %0.20lf \n\tER2 = %0.20lf\n",ER2[j-1][0],ER2[j-1][1],ER2[j-1][2]);
	}

	free(A);
}

void call_metodos(double a_funcao, double E, double * R, int* I, double * ER) {	

	double a, b, isolamento;
	a = 0;
	b = 0;
	int k0[1] = {0};
	int k1[1] = {0};
	int k2[1] = {0};
	double er0[1] = {0};
	double er1[1] = {0};
	double er2[1] = {0};

	isolamento = call_isolamento(a_funcao, &a, &b);
	printf("a = %lf, isolamento = %lf\n",a_funcao,isolamento);
 
	R[0] = call_newton_raphson(a_funcao, isolamento, E, k0, er0);
	printf("Resultado Newton Raphson: %0.20lf\n", R[0]);
	I[0] = k0[0];
  	ER[0] = er0[0];


	R[1] = call_newton_raphson_modificado(a_funcao, isolamento, E, k1, er1);
	printf("Resultado Newton Raphson Modificado: %0.20lf\n", R[1]);
	I[1] = k1[0];
	ER[1] = er1[0];

	R[2] = call_metodo_secante(a_funcao, a, b, E, k2, er2);
	printf("\nResultado Secante: %0.20lf\n", R[2]);
	I[2] = k2[0];	
	ER[2] = er2[0];

}

// ---------------------  Funçoes para Metodo Newton Raphson
double call_newton_raphson(double a_funcao, double raiz0, double E, int* K, double * ER) {

  	printf("\n~> NEWTON RAPHSON\n\n");

	double f, f_linha, err, x_anterio, x_atual;
	int k = 0;
  	int i=0;
	
	f = resolver_f(a_funcao, raiz0);
	f_linha = resolver_f_linha(a_funcao, raiz0);
	x_atual = newton_raphson(raiz0, f, f_linha);
	err = erro(raiz0, x_atual);
	
  	printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,raiz0,i,f);

	while((err > E || fabs(f) > E) && k < 99) {	
    	i++;
		x_anterio = x_atual;
		f = resolver_f(a_funcao, x_anterio);
		f_linha = resolver_f_linha(a_funcao, x_anterio);
		x_atual = newton_raphson(x_anterio, f, f_linha);		
		err = erro(x_atual, x_anterio);

	    printf("x%d = %0.20lf f(x%d) = %0.20lf\n", i, x_anterio, i, f);	
		k++;
	}

  	K[0] = k+1; 
	
	if (k == 99) printf("\nO NUMERO MAXIMO DE ITERAÇÕES FOI EXCEDIDA\n\n");

	f = resolver_f(a_funcao, x_atual);

	printf("x%d = %0.20lf f(x%d) = %0.20lf\n\n",i+1,x_atual,i+1,f);
	//printf("Erro Relativo: %0.20lf\n\n",err/x_atual);	
	
	ER[0] = fabs(err/x_atual);

	return x_atual;
}

double newton_raphson(double x_barra, double f, double f_linha) {
	/*
	 *Aplicação do método de Newton Raphson
	 */
	return x_barra - (f / f_linha);
}


//  ---------------------  Funçoes para Metodo Newton Raphson MODIFICADO  ----------
double call_newton_raphson_modificado(double a_funcao, double raiz0, double E, int* K, double* ER) {	

    printf("\n~> NEWTON RAPHSON MODIFICADO\n\n");

	double f, f_linha, err, x_anterio, x_atual;
	int k = 0;
  	int i = 0;

	f = resolver_f(a_funcao, raiz0);
	f_linha = resolver_f_linha(a_funcao, raiz0);
	x_atual = newton_raphson(raiz0, f, f_linha);
	err = erro(raiz0, x_atual);

    printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,raiz0,i,f);

	while((err > E || fabs(f) > E) && k < 99){			
        i++;	

		x_anterio = x_atual;
		f = resolver_f(a_funcao, x_anterio);
		x_atual = newton_raphson(x_anterio, f, f_linha);		
		err = erro(x_atual, x_anterio);

		printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,x_anterio,i,f);
		k++;
	}

	K[0] = k+1;

	if (k == 99) printf("\nO NUMERO MAXIMO DE ITERAÇÕES FOI EXCEDIDA\n\n");

	f = resolver_f(a_funcao, x_atual);

	printf("x%d = %0.20lf f(x%d) = %0.20lf\n\n",i+1,x_atual,i+1,f);
	
	//printf("Erro Relativo: %0.20lf\n\n",err/x_atual);	
	
	ER[0] = fabs(err/x_atual);

	return x_atual;
}


// ----------------------  Funçoes para Metodo Secante  ----------------------------
double call_metodo_secante(double a_funcao, double a_intervalo, double b_intervalo, double E, int* K, double* ER) {
	printf("\n~> MÉTODO DA SECANTE\n\n");

	int k = 0;
	int i = 0;
	double x_anterio, x_atual,err,f;

	err = erro(a_intervalo,b_intervalo);

	f = resolver_f(a_funcao, a_intervalo);
	printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,a_intervalo,i,f);
	i++;

	f = resolver_f(a_funcao, b_intervalo);
	printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,b_intervalo,i,f);
	i++;

	while((err > E || fabs(f) > E) && k < 99) {
		x_atual = (numerador_secante(a_funcao, a_intervalo, b_intervalo)/denominador_secante(a_funcao, a_intervalo, b_intervalo));

		a_intervalo = b_intervalo;
		b_intervalo = x_atual;

		k++;

		err = erro(a_intervalo, b_intervalo);

		f = resolver_f(a_funcao, x_atual);
		printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,x_atual,i,f);

		i++;
	}

	//printf("\nErro Relativo: %0.20lf\n\n",err/x_atual);	
	ER[0] = fabs(err/x_atual);

	K[0] = k;

	if (k == 99) printf("\nO NUMERO MAXIMO DE ITERAÇÕES FOI EXCEDIDA\n\n");

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