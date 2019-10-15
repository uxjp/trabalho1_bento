#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "metodos.h"

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

	while((err > E || fabs(f) > E) && i < 99) {	
    		i++;
		x_anterio = x_atual;
		f = resolver_f(a_funcao, x_anterio);
		f_linha = resolver_f_linha(a_funcao, x_anterio);
		x_atual = newton_raphson(x_anterio, f, f_linha);		
		err = erro(x_atual, x_anterio);

	    	printf("x%d = %0.20lf f(x%d) = %0.20lf\n", i, x_anterio, i, f);	
		k++;
	}

	if (i == 99) printf("\nERRO: O NUMERO MAXIMO DE ITERAÇÕES FOI EXCEDIDA\n");
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

	while((err > E || fabs(f) > E) && k < 99){			
        	i++;	

		x_anterio = x_atual;
		f = resolver_f(a_funcao, x_anterio);
		x_atual = newton_raphson(x_anterio, f, f_linha);		
		err = erro(x_atual, x_anterio);

		printf("x%d = %0.20lf f(x%d) = %0.20lf\n",i,x_anterio,i,f);
		k++;
	}

	if (i == 99) printf("\nERRO: O NUMERO MAXIMO DE ITERAÇÕES FOI EXCEDIDA\n");
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

	while((err > E || fabs(f) > E) && k < 99) {
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

	if (i == 99) printf("\nERRO: O NUMERO MAXIMO DE ITERAÇÕES FOI EXCEDIDA\n");
	
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