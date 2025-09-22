#define TAM_MAX 256

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Estrutura contendo os valores RGB de um pixel.
typedef struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

/// @brief Estrutura contendo os atributos de uma imagem .ppm (P3).
typedef struct Imagem {
    int largura;
    int altura;
    unsigned char quantizacao;
    Pixel **pixels;
} Imagem;

Imagem *imagemFundo, *imagemFrente, *imagemSaida;
Pixel *chave = NULL;
unsigned int limiarInferior = 0, limiarSuperior = 0;

/// @brief Pula uma quantidade especificada de linhas dentro de um arquivo.
void pularLinha(FILE *arquivo, int linhas);

void lerValores(unsigned char valorR,
                unsigned char valorG,
                unsigned char valorB,
                unsigned int valorInferior,
                unsigned int valorSuperior);

/// @brief Abre uma imagem com o caminho especificado e salva seus atributos no struct fornecido.
void lerImagem(char caminho[TAM_MAX], Imagem **imagem);

/// @brief Gera uma imagem no caminho especificado.
void gerarImagem(char caminho[TAM_MAX], Imagem **imagem);

/// @brief Libera a memória alocada para armazenar os atributos da imagem.
void liberarImagem(Imagem **imagem);

int main(int argc, char *argv[]) {
    lerImagem(argv[1], &imagemFundo);
    lerImagem(argv[2], &imagemFrente);
    lerValores(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]));
    gerarImagem(argv[3], &imagemSaida);
    liberarImagem(&imagemFundo);
    liberarImagem(&imagemFrente);
    liberarImagem(&imagemSaida);
    return 0;
}

void pularLinha(FILE *arquivo, int linhas) {
    char buffer[TAM_MAX];

    for (int i = 0; i < linhas; i++) {
        fgets(buffer, sizeof(buffer), arquivo);
    }
}

void lerValores(unsigned char valorR,
                unsigned char valorG,
                unsigned char valorB,
                unsigned int valorInferior,
                unsigned int valorSuperior) {
    chave = (Pixel *)malloc(sizeof(Pixel));

    if (chave == NULL) {
        printf("Não foi possível alocar espaço para o pixel chave!");
        exit(1);
    }

    chave->r = valorR;
    chave->g = valorG;
    chave->b = valorB;

    limiarInferior = valorInferior;
    limiarSuperior = valorSuperior;
}

void lerImagem(char caminho[TAM_MAX], Imagem **imagem) {
    *imagem = (Imagem *)malloc(sizeof(Imagem));

    if (*imagem == NULL) {
        printf("Não foi possível alocar espaço para a imagem!");
        exit(1);
    }

    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo!");
        liberarImagem(imagem);
        exit(1);
    }

    pularLinha(arquivo, 1);
    fscanf(arquivo, "%d %d", &(*imagem)->largura, &(*imagem)->altura);
    pularLinha(arquivo, 1);
    fscanf(arquivo, "%hhu", &(*imagem)->quantizacao);

    (*imagem)->pixels = (Pixel **)malloc((*imagem)->largura * sizeof(Pixel *));

    if ((*imagem)->pixels == NULL) {
        printf("Não foi possível alocar espaço para as colunas de pixels!");
        liberarImagem(imagem);
        exit(1);
    }

    for (int i = 0; i < (*imagem)->largura; i++) {
        (*imagem)->pixels[i] = (Pixel *)malloc((*imagem)->altura * sizeof(Pixel));

        if ((*imagem)->pixels[i] == NULL) {
            printf("Não foi possível alocar espaço para as linhas de pixels!");
            liberarImagem(imagem);
            exit(1);
        }
    }

    for (int i = 0; i < (*imagem)->largura; i++) {
        for (int j = 0; j < (*imagem)->altura; j++) {
            fscanf(arquivo,
                   "%hhu %hhu %hhu",
                   &(*imagem)->pixels[i][j].r,
                   &(*imagem)->pixels[i][j].g,
                   &(*imagem)->pixels[i][j].b);
        }
    }

    fclose(arquivo);
}

void gerarImagem(char caminho[TAM_MAX], Imagem **imagem) {
    *imagem = (Imagem *)malloc(sizeof(Imagem));

    if (*imagem == NULL) {
        printf("Não foi possível alocar espaço para a imagem!");
        exit(1);
    }

    (*imagem)->largura = (imagemFundo->largura < imagemFrente->largura) ? imagemFundo->largura : imagemFrente->largura;
    (*imagem)->altura = (imagemFundo->altura < imagemFrente->altura) ? imagemFundo->altura : imagemFrente->altura;
    (*imagem)->quantizacao =
        (imagemFundo->quantizacao < imagemFrente->quantizacao) ? imagemFundo->quantizacao : imagemFrente->quantizacao;

    (*imagem)->pixels = (Pixel **)malloc((*imagem)->largura * sizeof(Pixel *));

    if ((*imagem)->pixels == NULL) {
        printf("Não foi possível alocar espaço para as colunas de pixels!");
        liberarImagem(imagem);
        exit(1);
    }

    for (int i = 0; i < (*imagem)->largura; i++) {
        (*imagem)->pixels[i] = (Pixel *)malloc((*imagem)->altura * sizeof(Pixel));

        if ((*imagem)->pixels[i] == NULL) {
            printf("Não foi possível alocar espaço para as linhas de pixels!");
            liberarImagem(imagem);
            exit(1);
        }
    }

    unsigned int distancia = 0;

    for (int i = 0; i < (*imagem)->largura; i++) {
        for (int j = 0; j < (*imagem)->altura; j++) {
            distancia = sqrtl(powl(imagemFrente->pixels[i][j].r - chave->r, 2) +
                              powl(imagemFrente->pixels[i][j].g - chave->g, 2) +
                              powl(imagemFrente->pixels[i][j].b - chave->b, 2));

            if (distancia < limiarInferior) {
                (*imagem)->pixels[i][j].r = imagemFundo->pixels[i][j].r;
                (*imagem)->pixels[i][j].g = imagemFundo->pixels[i][j].g;
                (*imagem)->pixels[i][j].b = imagemFundo->pixels[i][j].b;
            }

            else if (distancia > limiarSuperior) {
                (*imagem)->pixels[i][j].r = imagemFrente->pixels[i][j].r;
                (*imagem)->pixels[i][j].g = imagemFrente->pixels[i][j].g;
                (*imagem)->pixels[i][j].b = imagemFrente->pixels[i][j].b;
            }

            else {
                (*imagem)->pixels[i][j].r = abs((imagemFrente->pixels[i][j].r + imagemFundo->pixels[i][j].r)) / 2;
                (*imagem)->pixels[i][j].g = abs((imagemFrente->pixels[i][j].g + imagemFundo->pixels[i][j].g)) / 2;
                (*imagem)->pixels[i][j].b = abs((imagemFrente->pixels[i][j].b + imagemFundo->pixels[i][j].b)) / 2;
            }
        }
    }

    printf("%d", distancia);

    FILE *arquivo = fopen(caminho, "w");

    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "%d %d\n", (*imagem)->largura, (*imagem)->altura);
    fprintf(arquivo, "%hhu\n", (*imagem)->quantizacao);

    for (int i = 0; i < (*imagem)->largura; i++) {
        for (int j = 0; j < (*imagem)->altura; j++) {
            fprintf(arquivo,
                    "%03hhu %03hhu %03hhu ",
                    (*imagem)->pixels[i][j].r,
                    (*imagem)->pixels[i][j].g,
                    (*imagem)->pixels[i][j].b);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void liberarImagem(Imagem **imagem) {
    if (imagem != NULL) {
        if ((*imagem)->pixels != NULL) {
            for (int i = 0; i < (*imagem)->largura; i++) {
                free((*imagem)->pixels[i]);
            }

            free((*imagem)->pixels);
        }

        free(*imagem);
    }
}
