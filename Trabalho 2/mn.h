void *criar_vetor(int n);
void informar_valores_vetor_B(void *vetor, int n);
void atribuir_vetor(void *vetor, int indice, double valor);
double obter_vetor(void *vetor, int indice);

void *criar_matriz(int n);
void atribuir_matriz(void *matriz, int x, int y, double valor, int quantColunas);
double obter_matriz(void *matriz, int x, int y, int quantColunas);
void informar_valores_matriz_A(void *matriz, int n);

void iniciar(void *matriz, void *vetor);
void liberar_matriz(void *matriz);
void *multiplicar_matriz_com_vetor(void *matriz, void *vetor, int n);
void *criar_matriz_identidade(int n);
void *criar_vetor_x0_gauss_jacobi(void *matriz, void *vetor, int n);
void *criar_vetor_xk_gauss_jacobi(void *matriz_a, void *vetor_b, void *vetor_xk, int n);
void *vetor_diferenca_entre_dois_vetores(void *vetor_anterio, void *vetor_atual, int n);
double maior_valor_abs_vetor(void *vetor, int n);
double erro_gauss_jacobi(void *vetor_anterio, void *vetor_diferenca, int n);
void call_Gauss_Jacobi(void *matriz_a, void *vetor_b, int n, double erro);
void *Gauss_Jacobi(void *matriz_a, void *vetor_b, int n, double erro);
void imprimir_matriz(void *matriz, int n);
void imprimir_vetor(void *vetor, int n);
void *Gauss_Seidel(void *matriz_a, void *vetor_b, int n, double erro);
void *criar_vetor_x0_gauss_seidel(void *matriz, void *vetor, int n);
void *criar_vetor_xk_gauss_seidel(void *matriz_a, void *vetor_b, void *vetor_xk, int n);
void call_Gauss_Seidel(void *matriz_a, void *vetor_b, int n, double erro);