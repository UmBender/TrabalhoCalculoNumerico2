#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// utilize '#define VERSAO_1 1' para a primeira função e '#define VERSAO_1 0' para a segunda

struct CofResult // Estrutura para armazenar os coeficientes a e b
{
	double a;
	double b;
};

typedef struct CofResult CofResult;

struct DadosLinha // Estrutura para armazenar os dados de cada linha do arquivo
{
	size_t valor_linha;
	double t_t;
	double y_i;
};

typedef struct DadosLinha DadosLinha;

#if VERSAO_1 // Definindo as funcoes g1 e g2 de acordo com a versao
double g1(double x)
{
	return exp(0.1 * x);
}
double g2(double x)
{
	return sin(x);
}
#endif /* if VERSAO_1 */

#if !VERSAO_1 // Se a versão = 1, utilizaremos g(x), se não, utilizaremos h(x)
double g1(double x)
{
	return pow(x, 2.0);
}
double g2(double x)
{
	return cos(x);
}
#endif /* if !VERSAO_1 */

double SumG1G2(DadosLinha *x) // Função da somatória de g1(x) com g2(x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g1(x[i].t_t) * g2(x[i].t_t);
	}
	return soma;
}

double SumG1G1(DadosLinha *x) // Função da somatória de g1(x) com g1(x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g1(x[i].t_t) * g1(x[i].t_t);
	}
	return soma;
}

double SumG2G2(DadosLinha *x) // Função da somatória de g2(x) com g2(x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g2(x[i].t_t) * g2(x[i].t_t);
	}
	return soma;
}

double SumG1F(DadosLinha *x) // Função da somatória de g1(x) com f(x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g1(x[i].t_t) * x[i].y_i;
	}
	return soma;
}

double SumG2F(DadosLinha *x) // Função da somatória de g2(x) com f(x)
{
	double soma = 0;
	for (int i = 0; i <= 100; i++)
	{
		soma += g2(x[i].t_t) * x[i].y_i;
	}
	return soma;
}

CofResult SistLin(DadosLinha *x) // Função para resolver o sistema linear e retornar os coeficientes a e b atavés de determinantes
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

	return resultado; // Retornando os coeficientes a e b
}

double SQres(DadosLinha *x, CofResult cofs) // Função para calcular o SQres
{
	double soma = 0;
	for (size_t i = 0; i < 101; i++)
	{
		soma += pow(x[i].y_i - (cofs.a * g1(x[i].t_t) + cofs.b * g2(x[i].t_t)), 2);
	}

	return soma;
}

double media(DadosLinha *x) // Função para calcular a média
{
	double soma = 0;
	for (size_t i = 0; i < 101; i++)
	{
		soma += x[i].y_i;
	}
	soma /= 101;
	return soma;
}

double SQtot(DadosLinha *x) // Função para calcular o SQtot
{
	double sq_media = media(x);
	double soma = 0;
	for (size_t i = 0; i < 101; i++)
	{
		soma += pow(x[i].y_i - sq_media, 2);
	}

	return soma;
}

double Cof_R(DadosLinha *x, CofResult cofs) // Função para calcular o R^2
{
	return 1.0 - (SQres(x, cofs) / SQtot(x));
}

int main(int argc, char **argv) // Função principal
{
	FILE *f;
	DadosLinha *arquivos;
	arquivos = (DadosLinha *)malloc(sizeof(DadosLinha) * 101);

	char buff[256];
	f = fopen("adicione o caminho do arquivo com os dados aqui", "r");
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

	CofResult cofs;

	cofs = SistLin(arquivos); // Chamada da função para resolver o sistema linear e imprimi-los
	double cof_r_novo = Cof_R(arquivos, cofs);
	double sqres_novo = SQres(arquivos, cofs);
	printf("SQres = %lf\n", sqres_novo); // Print do SQres
	printf("R^2 = %lf\n", cof_r_novo);	 // Print do R^2
	return 0;
}
