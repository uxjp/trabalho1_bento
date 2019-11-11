#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mn.h"

int main(){

	void *matriz = NULL; 
	void *vetor = NULL;		
	
	iniciar(matriz, vetor);

	liberar_matriz(matriz);
	liberar_matriz(vetor);

	return 0;
}


void iniciar(void *matriz, void *vetor){
	int n;
	double erro;	

	printf("Informe o erro desejado: ");
	scanf("%lf",&erro);

	printf("Informe a dimensao da matriz: ");
	scanf("%d",&n);

	matriz = criar_matriz(n);
	vetor = criar_vetor(n);	

	if(matriz != NULL && vetor != NULL){
		informar_valores_matriz_A(matriz, n);
		informar_valores_vetor_B(vetor,n);

    /*
    // modifica aki


    void *vetorResposta = NULL;

		vetorResposta=Gauss_Jacobi(matriz, vetor, n, erro);		
    

    printf("Vetor Resposta\n");
	  imprimir_vetor(vetorResposta, n);	
	  printf("****************************************\n");

    // ate aki*/


    ///*ORIGINAL
      printf("\n\n\nGAUSS-JACOBI \n\n\n");
    	call_Gauss_Jacobi(matriz, vetor, n, erro);	
      printf("\n\n\nGAUSS-SEIDEL \n\n\n");
      call_Gauss_Seidel(matriz, vetor, n, erro);
    //*/


	}else{
		printf("FALHA AO CRIAR MATRIZ OU AO CRIAR VETOR");
	}	
}

void call_Gauss_Jacobi(void *matriz_a, void *vetor_b, int n, double erro){
	int linhas = 0, i, j, k;
	double valor;
	void *vetorResposta = NULL;
	void *vetorValidar = NULL;
	void *vetorDif = NULL;
	void *matrizIdentidade = NULL;	
	void *vetor_linha_identidade = criar_vetor(n);
	void *vetor_linha_inversa = criar_vetor(n);
	void *matrizInversa = criar_matriz(n);
	
	matrizIdentidade = criar_matriz_identidade(n);

	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){			
			valor = obter_matriz(matrizIdentidade, i, j, n);
			atribuir_vetor(vetor_linha_identidade, j,valor);			
		}
		
    printf("\nCALCULO COLUNA %d DA INVERSA:\n\n",i);
		vetor_linha_inversa = Gauss_Jacobi(matriz_a, vetor_linha_identidade, n, erro);
	
		for(k = 0; k < n; k++){
			valor = obter_vetor(vetor_linha_inversa, k);
			atribuir_matriz(matrizInversa, k, i, valor, n);			
		}
	}


	vetorResposta = multiplicar_matriz_com_vetor(matrizInversa, vetor_b, n);

	//Verificar a corretude dos valores encontrados
	vetorValidar = multiplicar_matriz_com_vetor(matriz_a, vetorResposta, n);
	vetorDif = vetor_diferenca_entre_dois_vetores(vetor_b, vetorValidar, n);

	printf("****************************************\n");
	printf("Matriz A\n");
	imprimir_matriz(matriz_a, n);

	printf("Vetor B\n");
	imprimir_vetor(vetor_b, n);

	printf("Matriz Inversa\n");
	imprimir_matriz(matrizInversa, n);

	printf("Vetor resposta\n");
	imprimir_vetor(vetorResposta, n);

	printf("Vetor diferenca\n");
	imprimir_vetor(vetorDif, n);	
	printf("****************************************\n");

}

void imprimir_vetor(void *vetor, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%0.10lf   ", obter_vetor(vetor, i));
	}
	printf("\n");
}

void imprimir_matriz(void *matriz, int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%0.10lf   ",obter_matriz(matriz, i, j, n));
		}
		printf("\n");
	}	
}

void *Gauss_Jacobi(void *matriz_a, void *vetor_b, int n, double erro){
		//Encontra os valores usando o método de Gauss Jacobe e retorna os valores em um vetor
		int i=0;
		void *vetor_x0;
		void *vetor_xk;
		void *vetor_diferenca;
		
		vetor_x0 = criar_vetor_x0_gauss_jacobi(matriz_a, vetor_b, n);		
    printf("vetor x%d: ",i);
    imprimir_vetor(vetor_x0,n);
    i++;
		vetor_xk = criar_vetor_xk_gauss_jacobi(matriz_a, vetor_b, vetor_x0, n);
		vetor_diferenca = vetor_diferenca_entre_dois_vetores(vetor_x0, vetor_xk, n);

		while(erro_gauss_jacobi(vetor_xk, vetor_diferenca, n) > erro){		

			vetor_x0 = vetor_xk;
      printf("vetor x%d: ",i);
      imprimir_vetor(vetor_x0,n);
      i++;
			vetor_xk = criar_vetor_xk_gauss_jacobi(matriz_a, vetor_b, vetor_x0, n);		
			vetor_diferenca = vetor_diferenca_entre_dois_vetores(vetor_x0, vetor_xk, n);				
		}		

  printf("vetor x%d: ",i);
  imprimir_vetor(vetor_xk,n);

	return vetor_xk;
}

void informar_valores_vetor_B(void *vetor, int n){
	int i;
	double valor; 

	for(i = 0; i < n; i++){
		printf("Informe o valor do vetor[%d]: ", i + 1);
		scanf("%lf", &valor);
		atribuir_vetor(vetor, i, valor);
	}
}

void *criar_vetor(int n){
	//n = tamanho do vetor
	return (double*) (malloc(sizeof(double) * n));
}

void atribuir_vetor(void *vetor, int indice, double valor){
	//Preenchendo o vetor[indice] = valor
	*(double*)(vetor + sizeof(double) * indice) = valor;
}

double obter_vetor(void *vetor, int indice){
	//Retorna o vetor[indice] = valor
	return *(double*)(vetor + sizeof(double) * indice);
}

void informar_valores_matriz_A(void *matriz, int n){
	int i, j;
	double valor;

	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("Informe o valor da matriz A[%d][%d]: ", i + 1, j + 1);
			scanf("%lf",&valor);
			atribuir_matriz(matriz, i, j, valor, n);
		}
	}
}


void *criar_matriz(int n){
	//n = tamanho da matriz quadrada
	return (double*) malloc(sizeof(double) * pow(n, 2));
}

void atribuir_matriz(void *matriz, int x, int y, double valor, int quantColunas){
	//Preenchendo a matriz[x][y] = valor
	int indicador =  y + x  * quantColunas;
    *(double*) (matriz + sizeof(double) * indicador) = valor;
}

double obter_matriz(void *matriz, int i, int j, int quantColunas){
	//Retorna o valor da matriz[x][y]	
	int indicador =  j + i  * quantColunas;
    return *(double*) (matriz + sizeof(double) * indicador);
}

void *multiplicar_matriz_com_vetor(void *matriz, void *vetor, int n){
	//Faz a maltiplicacao entre uma matriz e vetor e retorna o vetor multiplicacao
	int i, j;
	double multiplicacao = 0;
	void *vetorMultiplicacao;
	vetorMultiplicacao = criar_vetor(n); 

	if(vetorMultiplicacao != NULL){
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				multiplicacao += obter_matriz(matriz, i, j, n) * obter_vetor(vetor, j);			
			}		
			atribuir_vetor(vetorMultiplicacao, i, multiplicacao);
			multiplicacao = 0;
		}
		return vetorMultiplicacao;

	}else{
		printf("FALHA AO CRIAR A MATRIZ MULTIPLICAR VETOR E MATRIZ");
		return NULL;
	}	
}

void *criar_matriz_identidade(int n){
	//Criar retornar a matriz identidade
	int i, j;
	void *matrizIdentidade;
	matrizIdentidade = criar_matriz(n);

	if(matrizIdentidade != NULL){

		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				if(i == j){
					atribuir_matriz(matrizIdentidade, i, j, 1, n);
				}else{
					atribuir_matriz(matrizIdentidade, i, j, 0, n);
				}				
			}					
		}

		return matrizIdentidade;

	}else{
		printf("FALHA AO CRIAR A MATRIZ IDENTIDADE");
		return NULL;
	}	
}

void *criar_vetor_x0_gauss_jacobi(void *matriz, void *vetor, int n){
	//Retorna o vetor X0 e tem como entrada a matriz A, vetor B e o tamanho(n)
	int i;
	void *vetor_x0 = criar_vetor(n);
	double valor;
	double valor_matriz;

	if(vetor_x0 != NULL){

		for(i = 0; i < n; i++){
			valor_matriz = obter_matriz(matriz, i, i, n);
			if(valor_matriz != 0){
				valor = obter_vetor(vetor, i) / valor_matriz;
				atribuir_vetor(vetor_x0, i, valor);
			}else{
				atribuir_vetor(vetor_x0, i, 0);	
			}			
		}
		return vetor_x0;

	}else{
		printf("FALHA AO CRIAR O VETOR X0 NO GAUSS JACOBI");
		return NULL;
	}
}

void *criar_vetor_xk_gauss_jacobi(void *matriz_a, void *vetor_b, void *vetor_xk, int n){
	/*
	* Retorna o vetor com os novos valores
	* vetor_xk = vetor com os valores anteriores
	*/

	void *vetor_xk_atual = criar_vetor(n);
	int i, j;
	double valor, pivo_matriz, valor_matriz, valor_vetor;

	if(vetor_xk_atual != NULL){

		for(i = 0; i < n; i++){

			pivo_matriz = obter_matriz(matriz_a, i, i, n);
			valor = obter_vetor(vetor_b, i);			

			for(j = 0; j < n; j++){		

				if(i != j){
					valor_matriz = obter_matriz(matriz_a, i, j, n);		
				}else{
					valor_matriz = 0;
				}							
				
				valor -= (valor_matriz * obter_vetor(vetor_xk, j));
								
			}	

			if(pivo_matriz != 0){
					valor = valor / pivo_matriz;
				}else{
					valor = 0;
				}

			atribuir_vetor(vetor_xk_atual, i, valor);
		}

		return vetor_xk_atual;
	}else{
		printf("FALHA AO CRIAR O VETOR XK NO GAUSS JACOBI");
		return NULL;
	}
}


void *vetor_diferenca_entre_dois_vetores(void *vetor_anterio, void *vetor_atual, int n){
	//Calcular e retorna um vetor com a difereca entre outros dois
	int i;
	double valor;
	void *vetor_diferenca = criar_vetor(n);

	if(vetor_diferenca != NULL){

		for(i = 0; i < n; i++){
			valor = obter_vetor(vetor_atual, i) - obter_vetor(vetor_anterio, i);
			atribuir_vetor(vetor_diferenca, i, valor);
		}

		return vetor_diferenca;
	}else{
		printf("FALHA AO CRIAR O VETOR DIFERENCA");
		return NULL;
	}
}

double maior_valor_abs_vetor(void *vetor, int n){
	//Retorna o maior valor absoluto do vetor
	int i;
	double valor;

	valor = fabs(obter_vetor(vetor, 0));

	for(i = 1; i < n; i++){
		if(fabs(obter_vetor(vetor, i)) > valor){
			valor = fabs(obter_vetor(vetor, i));
		}
	}
	return valor;
}

double erro_gauss_jacobi(void *vetor_anterio, void *vetor_diferenca, int n){
	//Retorna o erro para Gauss Jacobi
	double maior_anterio = maior_valor_abs_vetor(vetor_anterio, n);

	if(maior_anterio != 0){		
		return maior_valor_abs_vetor(vetor_diferenca, n) / maior_valor_abs_vetor(vetor_anterio, n);
	}else{
		return 0;
	}
}

void liberar_matriz(void *matriz){
    free(matriz);
}



//TESTE



void *Gauss_Seidel(void *matriz_a, void *vetor_b, int n, double erro){
		//Encontra os valores usando o método de Gauss Jacobe e retorna os valores em um vetor
		int i = 0;
		void *vetor_x0;
		void *vetor_xk;
		void *vetor_diferenca;
		
		vetor_x0 = criar_vetor_x0_gauss_seidel(matriz_a, vetor_b, n);		
    printf("vetor x%d: ",i);
    imprimir_vetor(vetor_x0,n);
    i++;
		vetor_xk = criar_vetor_xk_gauss_seidel(matriz_a, vetor_b, vetor_x0, n);
		vetor_diferenca = vetor_diferenca_entre_dois_vetores(vetor_x0, vetor_xk, n);

		while(erro_gauss_jacobi(vetor_xk, vetor_diferenca, n) > erro){		
      
			vetor_x0 = vetor_xk;
      printf("vetor x%d: ",i);
      imprimir_vetor(vetor_x0,n);
      i++;
			vetor_xk = criar_vetor_xk_gauss_seidel(matriz_a, vetor_b, vetor_x0, n);		
			vetor_diferenca = vetor_diferenca_entre_dois_vetores(vetor_x0, vetor_xk, n);				
		}		

  printf("vetor x%d: ",i);
  imprimir_vetor(vetor_xk,n);

	return vetor_xk;
}


void *criar_vetor_x0_gauss_seidel(void *matriz, void *vetor, int n){
	//Retorna o vetor X0 e tem como entrada a matriz A, vetor B e o tamanho(n)
	int i;
	void *vetor_x0 = criar_vetor(n);
	double valor;
	double valor_matriz;

	if(vetor_x0 != NULL){

		for(i = 0; i < n; i++){
			valor_matriz = obter_matriz(matriz, i, i, n);
			if(valor_matriz != 0){
				valor = obter_vetor(vetor, i) / valor_matriz;
				atribuir_vetor(vetor_x0, i, valor);
			}else{
				atribuir_vetor(vetor_x0, i, 0);	
			}			
		}
		return vetor_x0;

	}else{
		printf("FALHA AO CRIAR O VETOR X0 NO GAUSS SEIDEL");
		return NULL;
	}
}

void *criar_vetor_xk_gauss_seidel(void *matriz_a, void *vetor_b, void *vetor_xk, int n){
	/*
	* Retorna o vetor com os novos valores
	* vetor_xk = vetor com os valores anteriores
	*/

	void *vetor_xk_atual = criar_vetor(n);
	int i, j;
	double valor, pivo_matriz, valor_matriz, valor_vetor;

	if(vetor_xk_atual != NULL){

		for(i = 0; i < n; i++){

			pivo_matriz = obter_matriz(matriz_a, i, i, n);
			valor = obter_vetor(vetor_b, i);			

			for(j = 0; j < n; j++){		

				if(i != j){
					valor_matriz = obter_matriz(matriz_a, i, j, n);		
				}else{
					valor_matriz = 0;
				}							
				
        if (i<j) {
				  valor -= (valor_matriz * obter_vetor(vetor_xk, j));
        }
        else {
          valor -= (valor_matriz * obter_vetor(vetor_xk_atual, j));
        }
								
			}	

			if(pivo_matriz != 0){
					valor = valor / pivo_matriz;
				}else{
					valor = 0;
				}

			atribuir_vetor(vetor_xk_atual, i, valor);
		}

		return vetor_xk_atual;
	}else{
		printf("FALHA AO CRIAR O VETOR XK NO GAUSS SEIDEL");
		return NULL;
	}
}

void call_Gauss_Seidel(void *matriz_a, void *vetor_b, int n, double erro){
	int linhas = 0, i, j, k;
	double valor;
	void *vetorResposta = NULL;
	void *vetorValidar = NULL;
	void *vetorDif = NULL;
	void *matrizIdentidade = NULL;	
	void *vetor_linha_identidade = criar_vetor(n);
	void *vetor_linha_inversa = criar_vetor(n);
	void *matrizInversa = criar_matriz(n);
	
	matrizIdentidade = criar_matriz_identidade(n);

	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){			
			valor = obter_matriz(matrizIdentidade, i, j, n);
			atribuir_vetor(vetor_linha_identidade, j,valor);			
		}
		
    printf("\nCALCULO COLUNA %d DA INVERSA:\n\n",i);
		vetor_linha_inversa = Gauss_Seidel(matriz_a, vetor_linha_identidade, n, erro);
	
		for(k = 0; k < n; k++){
			valor = obter_vetor(vetor_linha_inversa, k);
			atribuir_matriz(matrizInversa, k, i, valor, n);			
		}
	}


	vetorResposta = multiplicar_matriz_com_vetor(matrizInversa, vetor_b, n);

	//Verificar a corretude dos valores encontrados
	vetorValidar = multiplicar_matriz_com_vetor(matriz_a, vetorResposta, n);
	vetorDif = vetor_diferenca_entre_dois_vetores(vetor_b, vetorValidar, n);

	printf("****************************************\n");
	printf("Matriz A\n");
	imprimir_matriz(matriz_a, n);

	printf("Vetor B\n");
	imprimir_vetor(vetor_b, n);

	printf("Matriz Inversa\n");
	imprimir_matriz(matrizInversa, n);

	printf("Vetor resposta\n");
	imprimir_vetor(vetorResposta, n);

	printf("Vetor diferenca\n");
	imprimir_vetor(vetorDif, n);	
	printf("****************************************\n");

}