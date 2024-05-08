#include <stdio.h>
#include <stdlib.h>

void derivacao_progressiva(float *x, float *y, int qtd_valores){
    float derivada = 0, delta_X = 0;

    delta_X = x[1] - x[0];
    
    printf("\nDerivação Progressiva: \n");
    printf("\u0394x: %g\n", delta_X);
    printf("x\u2081: %g    y\u2081: %g\n", x[qtd_valores - qtd_valores], x[qtd_valores - (qtd_valores - 1)]);
    printf("x\u2082: %g    y\u2082: %g\n", y[qtd_valores - qtd_valores], y[qtd_valores - (qtd_valores - 1)]);

    derivada = ( (y[1] - (y[0]) ) / delta_X);
    printf("Derivada: %g\n", derivada);
}

void derivacao_central(float *x, float *y, int qtd_valores){
    float derivada = 0, delta_X = 0;
    
    for(int i = 1; i < qtd_valores - 1; i++){
        printf("\nDerivação Central %d: \n", i);
        delta_X = (x[i] - x[i - 1]);
        printf("\u0394x: %g\n", delta_X);
        printf("x\u2081: %g    y\u2081: %g\n", x[i-1], y[i-1]);
        printf("x\u2082: %g    y\u2082: %g\n", x[i+1], y[i+1]);
        
        derivada = ( (y[i + 1] - y[i - 1]) / (2 * delta_X));
        printf("Derivada %d: %g\n", i, derivada);
    }
}

void derivacao_regressiva(float *x, float *y, int qtd_valores){
    float derivada = 0, delta_X = 0;
    
    delta_X = x[qtd_valores - 1] - x[qtd_valores - 2];

    printf("\nDerivação Regressiva: \n");
    printf("\u0394x: %g\n", delta_X);
    printf("x\u2082: %g    y\u2082: %g\n", x[qtd_valores - 2], y[qtd_valores - 2]);
    printf("x\u2082: %g    y\u2082: %g\n", x[qtd_valores - 1], y[qtd_valores - 1]);
    
    derivada = ( (y[qtd_valores - 1] - y[qtd_valores - 2]) / delta_X);
    printf("Derivada: %g\n", derivada);
}

int leitura_valores(const char *nome_arquivo, float **x, float **y){
    FILE *arquivo = fopen(nome_arquivo, "r");
    int capacidade = 10, tamanho = 0;
    float valor_X, valor_Y;
    if(arquivo == NULL){
        perror("Erro ao abrir arquivo!");
        exit(1);
    }

    *x = malloc(capacidade * sizeof(float));
    *y = malloc(capacidade * sizeof(float));

    while(fscanf(arquivo, "%f %f", &valor_X, &valor_Y) == 2){
        if(tamanho >= capacidade){
            capacidade *= 2;
            *x = realloc(*x, capacidade * sizeof(float));
            *y = realloc(*y, capacidade * sizeof(float));
        }

        (*x)[tamanho] = valor_X;
        (*y)[tamanho] = valor_Y;
        tamanho++;
    }

    return tamanho;
}

int main(){
    float *x, *y;
    int qtd_valores = leitura_valores("teste.txt", &x, &y);
    
    if(qtd_valores > 0){
        printf("Quantidade de valores: %d\n", qtd_valores);
        printf("Valores lidos:\n");
        for(int i = 0; i < qtd_valores; i++){
            printf("%g %g\n", x[i], y[i]);
        }
    } else {
        printf("Nenhum valor foi lido do arquivo.\n");
    }

    derivacao_progressiva(x, y, qtd_valores);
    derivacao_central(x, y, qtd_valores);
    derivacao_regressiva(x, y, qtd_valores);

    free(x);
    free(y);
    
    return 0;
}
/*#ifndef DERIVACAO_H_INCLUDED
#define DERIVACAO_H_INCLUDED

void derivacao_progressiva(float *x, float *y, int numValores);
void derivacao_central(float *x, float *y, int numValores);
void derivacao_regressiva(float *x, float *y, int numValores);

#endif // DERIVACAO_H_INCLUDED*/
