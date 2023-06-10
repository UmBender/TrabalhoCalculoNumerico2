#include <stdio.h>
#include <stdlib.h>
#include <math.h>



struct DadosLinha {
	size_t valor_linha;
	double t_t;
	double y_i;
};

typedef struct DadosLinha DadosLinha;


int main(int argc, char ** argv)
{
	FILE *f;
	DadosLinha *arquivos;
	arquivos = (DadosLinha*) malloc(sizeof(DadosLinha) * 101);

	char buff[256];
	f = fopen("./dadosEx2.txt", "r");
	if(f == NULL) {
		printf("Erro na abertura\n");
		return -1;
	}
	fscanf(f, "%s",buff);
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


	

	for (size_t i = 0; i < 101; i++) {
		
		printf("%zu,", arquivos[i].valor_linha);
		printf("%lf,", arquivos[i].t_t);
		printf("%lf\n", arquivos[i].y_i);
	}
	return 0;
}
