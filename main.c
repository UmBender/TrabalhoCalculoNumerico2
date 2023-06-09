#include <stdio.h>
#include <stdlib.h>

struct DadosLinha {
	size_t valor_linha;
	float t_t;
	float y_i;
};


typedef struct DadosLinha DadosLinha;

int main(void)
{
	FILE *f;
	DadosLinha *arquivos;
	arquivos = (DadosLinha*) malloc(sizeof(DadosLinha) * 100);

	char buff[256];
	f = fopen("./dadosEx2.txt", "r");
	if(f == NULL) {
		printf("Erro na abertura\n");
		return -1;
	}
	fscanf(f, "%s",buff);
	for (size_t i = 0; i < 101; i++) {
		DadosLinha *atualPos = &arquivos[i];
		fscanf(f, "%zu,%f,%f",&atualPos->valor_linha,&atualPos->t_t, &atualPos->y_i);
	}

	for (size_t i = 0; i < 101; i++) {
		
		printf("%zu,", arquivos[i].valor_linha);
		printf("%f,", arquivos[i].t_t);
		printf("%f\n", arquivos[i].y_i);
	}
	fclose(f);
	return 0;
}
