#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct DadosLinha
{
	size_t valor_linha;
	double t_t;
	double y_i;
};

typedef struct DadosLinha DadosLinha;

double Sum1(double *x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += 1;
	}
	return soma;
}

double SumExp(double *x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += exp(x[i]);
	}
	return soma;
}

double SumSen(double *x)
{
	double soma = 0;
	for (int i = 1; i <= 100; i++)
	{
		soma += sin(x[i]);
	}
	return soma;
}

double SumExpSen(double *x)
{
	double soma = 0;
	for (int i = 1; i <= 100; i++)
	{
		soma += exp(x[i]) * sin(x[i]);
	}
	return soma;
}

double SumExpG(double *x, double *y)
{
	double soma = 0;
	for (int i = 1; i <= 100; i++)
	{
		soma += exp(x[i]) * y[i];
	}
	return soma;
}

double SumSenG(double *x, double *y)
{
	double soma = 0;
	for (int i = 1; i <= 100; i++)
	{
		soma += sin(x[i]) * y[i];
	}
	return soma;
}

double SistLin(double *x, double *y)
{
	double a, b;
	double q1 = SumExp(x);
	double q2 = SumSen(x);
	double q3 = SumExpG(x, y);
	double q4 = SumSen(x);
	double q5 = SumExpSen(x);
	double q6 = SumSenG(x, y);

	double det = q1 * q4 - q2 * q3;
	a = (q5 * q4 - q2 * q6) / det;
	b = (q1 * q6 - q2 * q5) / det;
	return a, b;
}

int main(int argc, char **argv)
{
	FILE *f;
	DadosLinha *arquivos;
	arquivos = (DadosLinha *)malloc(sizeof(DadosLinha) * 101);

	char buff[256];
	f = fopen("C:\\Users\\joaov\\.vscode\\Projetos\\CN\\Trab\\TrabalhoCalculoNumerico2\\BancoCN.txt", "r");
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

	for (size_t i = 0; i < 101; i++)
	{

		printf("%zu,", arquivos[i].valor_linha);
		printf("%lf,", arquivos[i].t_t);
		printf("%lf\n", arquivos[i].y_i);
	}
	return 0;
}
