#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct CofResult {
	double a;
	double b;
};

typedef struct CofResult CofResult;

struct DadosLinha
{
	size_t valor_linha;
	double t_t;
	double y_i;
};

typedef struct DadosLinha DadosLinha;

#define VERSAO_1 1 

#if VERSAO_1
double g1(double x) {
	return exp(0.1 * x);
}
double g2(double x) {
	return sin(x);
}
#endif /* if VERSAO_1 */

#if !VERSAO_1
double g1(double x) {
	return pow(x, 2.0);
}
double g2(double x) {
	return cos(x * (1.0/2.0));
}
#endif /* if !VERSAO_1 */


double SumG1G2(DadosLinha *x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g1(x[i].t_t) * g2(x[i].t_t);
	}
	return soma;
}

double SumG1G1(DadosLinha *x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g1(x[i].t_t) * g1(x[i].t_t);
	}
	return soma;
}

double SumG2G2(DadosLinha *x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g2(x[i].t_t) * g2(x[i].t_t);
	}
	return soma;
}

double SumG1F(DadosLinha *x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g1(x[i].t_t) * x[i].y_i;
	}
	return soma;
}

double SumG2F(DadosLinha *x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g2(x[i].t_t) * x[i].y_i;
	}
	return soma;
}

CofResult SistLin(DadosLinha *x)
{
	double a, b;
	double q1 = SumG1G1(x);
	double q2 = SumG1G2(x);
	double q3 = SumG1G2(x);
	double q4 = SumG2G2(x);
	double q5 = SumG1F(x);
	double q6 = SumG2F(x);

	double det = q1 * q4 - q2 * q3;
	a = (q5 * q4 - q2 * q6) / det;
	b = (q1 * q6 - q2 * q5) / det;
	printf("valor a: %lf\n", a);
	printf("valor b: %lf\n", b);

	CofResult resultado;
	resultado.a = a;
	resultado.b = b;

	return resultado;
	
}

double SQres(DadosLinha* x, CofResult cofs) {
	double soma =0;
	for (size_t i = 0; i < 101; i++) {
		soma += pow(x[i].y_i - (cofs.a * g1(x[i].t_t) + cofs.b * g2(x[i].t_t)) , 2);
	}

	return soma;
}

double media(DadosLinha *x) {
	double soma = 0;
	for (size_t i = 0; i < 101; i++) {
		soma += x[i].y_i;
	}
	soma /= 101;
	return soma;
}

double SQtot(DadosLinha *x) {
	double sq_media = media(x);
	double soma =0;
	for (size_t i = 0; i < 101; i++) {
		soma += pow(x[i].y_i - sq_media, 2);
	}

	return soma;
}

double Cof_R(DadosLinha* x, CofResult cofs) {
	return 1.0 - (SQres(x, cofs) / SQtot(x));
}



int main(int argc, char **argv)
{
	FILE *f;
	DadosLinha *arquivos;
	arquivos = (DadosLinha *)malloc(sizeof(DadosLinha) * 101);

	char buff[256];
	//f = fopen("C:\\Users\\joaov\\.vscode\\Projetos\\CN\\Trab\\TrabalhoCalculoNumerico2\\BancoCN.txt", "r");
	f = fopen("./BancoCN.txt", "r");
	if (f == NULL)
	{
		printf("Erro na abertura\n");
		return -1;
	}
	fscanf(f, "%s", buff);
	int i = 0;
	int valor = 1;
	DadosLinha *atualPos = &arquivos[i];

	while ((valor = fscanf(f, "%zu,%lf,%lf",
						   &atualPos->valor_linha,
						   &atualPos->t_t,
						   &atualPos->y_i)) != -1)
	{
		i++;
		atualPos = &arquivos[i];
	}
	fclose(f);
	/*

	for (size_t i = 0; i < 101; i++)
	{

		printf("%zu,", arquivos[i].valor_linha);
		printf("%lf,", arquivos[i].t_t);
		printf("%lf\n", arquivos[i].y_i);
	}
	*/

	CofResult cofs;



	cofs = SistLin(arquivos);
	double cof_r_novo = Cof_R(arquivos, cofs);
	printf("R^2 = %lf\n", cof_r_novo);
	return 0;
}
