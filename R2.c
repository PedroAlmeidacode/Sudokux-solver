#include "library.h"

int ***read_tabuleiros_from_txt_and_load_memory(int * tamanhos, char string[] ) {
    int number_of_tabuleiros;

    int i =0;
    int size_tabuleiro;
    FILE *handler = fopen(string, "r");

        //retira do ficheiro o numero de tabuleiros que existem no ficheiro
        fscanf(handler,"%d",&number_of_tabuleiros);

        //aloca um apontador que guarda em cada posicao o size do tabuleiro que se encontra na posicao correspondente de memoria
        //tamanhos = malloc(number_of_tabuleiros*sizeof(int));

        //aloca memoria para a quantidade de tabuleiros que vamos colocar
        int ***memoria = malloc( number_of_tabuleiros* sizeof(int **));

        //itera os tabuleiros
        while (i != number_of_tabuleiros ) {
            //retira do txt o tamanho de cada tabuleiro
            fscanf(handler, "%d", &size_tabuleiro);

            //guarda no aponatdor tamanhos o tamanho correspondnete para cada matriz
            *(tamanhos+i) = size_tabuleiro;
            //guarda em cada posicao do apontador memoria o tabuleiro retirado
            *(memoria + i) = read_tabuleiro(handler, size_tabuleiro);

            i++;//itera
        }
        *(tamanhos+i) = '\0';

    fclose(handler); //fechar ficheiro
    return memoria ;
}


int **read_tabuleiro(FILE *handler, int size)
{
    int **tabuleiro = create_dyn_tabuleiro(size);

    for (int linha = 0; linha < size ; linha++) {
        for (int coluna = 0; coluna < size ; coluna++) {
            int numb;

            fscanf(handler, "%d", &numb);
            *(*(tabuleiro + linha) + coluna) = numb;
        }
    }
    return tabuleiro;
}




