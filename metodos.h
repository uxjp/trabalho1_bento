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