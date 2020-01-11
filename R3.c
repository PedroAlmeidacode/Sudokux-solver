#include "library.h"

int check_consistency_of_board(int **tabuleiro, int size){
    if (size < 9 || size > 36) return 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size ; j++) {
            if(checkconsistency(tabuleiro,size,i,j,tabuleiro[i][j])== 0) return 0;

        }

    }
    return 1;
}


int checkconsistency(int **tabuleiro, int size, int linha, int coluna , int number ){
    if(tabuleiro[linha][coluna] == 0) {
        if (no_repeated_number_in_line(tabuleiro, size, linha, number) == 1 &&
            no_repeated_number_in_box(tabuleiro, size, linha, coluna, number) == 1 &&
            no_repeated_number_in_column(tabuleiro, size, coluna, number) == 1 &&
            no_repeated_number_in_principal_diagonal(tabuleiro, size, linha, coluna, number) == 1 &&
            no_repeated_number_in_secondary_diagonal(tabuleiro, size, linha, coluna, number) == 1)
        {
            return 1;
        } else return 0;
    }else return 0;
}




int no_repeated_number_in_line(int **tabuleiro, int size,int linha, int valor){

    for (int i = 0; i < size ; i++) {
        if(tabuleiro[linha][i] == valor){
            return 0;
        }
    }
    return 1;
}




int no_repeated_number_in_column(int **tabuleiro, int size,int coluna, int valor){

    for (int i = 0; i < size ; i++) {
        if(tabuleiro[i][coluna] == valor){
            return 0;
        }
    }
    return 1;
}



int no_repeated_number_in_box(int **tabuleiro, int size, int linha, int coluna, int valor){
    int n =return_box_size(size);

    int li = 0, lf = 0, ci = 0, cf = 0;
    li = linha - (linha % n);
    lf = li + (n - 1);
    ci = coluna - (coluna % n);
    cf = ci + (n - 1);

    for (int i = li; i <= lf ; i++) {
        for (int j = ci; j <= cf ; j++) {

            if(tabuleiro[i][j] == valor){
                return 0;
            }
        }
    }

    return 1;

}




int no_repeated_number_in_principal_diagonal(int **tabuleiro,int size, int linha, int coluna , int valor){
    int j=0;
    if(linha != coluna){ //a posicao a colocar nao faz parte sequer da diagonal principal
        return 1;
    }else {
        for (int i = 0; i < size; i++) {

            if (tabuleiro[i][j] == valor) {
                return 0;
            }
            j++;
        }
        return 1;
    }
}

int no_repeated_number_in_secondary_diagonal(int **tabuleiro ,int size, int linha, int coluna , int valor){
    int j= size -1;
    if(linha != size-1-coluna || coluna != size-1-linha){ // testa se esta nao esta na diagonal secundaria
        return 1;
    } else{

        for (int i = 0; i < size; i++) {


                if(tabuleiro[i][j] == valor) {
                    return 0;
                }
            j--;
        }
        return 1;
    }
}



/**
 * testa se  a grelha esta completamente preenchida
 * @param matrix grelha de sudoku
 * @return retorna 1 se a grelha estiver preenchida
 */
int checkgrid(int **matrix, int size) {
    for (int linha = 0; linha < size; linha++) {
        for (int coluna = 0; coluna < size; coluna++) {
            if (matrix[linha][coluna] == 0) {
                return 0;
            }
        }
    }
    return 1;

}
