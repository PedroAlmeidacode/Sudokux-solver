#include "library.h"


int** create_dyn_tabuleiro(int size) {
    int i;
    int **matrix = malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        *(matrix + i) = (malloc(size * sizeof(int)));
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0; // colocar posicao a 0
        }
    }
    return matrix;
}



int *generate_positions_in_board(int range) {
    time_t t;
    srand((unsigned)time(&t));
    int *final= malloc(sizeof(int) * range);

    for (int i = 1; i <= range; i++) {     // fill array
        final[i-1]= i;
    }


        for (int i = 0; i < range; i++) {    // shuffle array
            int temp = final[i];
            int randomIndex = rand() % range;
            final[i] = final[randomIndex];
            final[randomIndex] = temp;
        }

    return final;
}






int get_coluna_from_posicao(int posicao, int size){
    int coluna = posicao % size ;
    if (coluna == 0){ return size -1;}
    else return coluna -1;
}







int get_linha_from_posicao(int posicao, int size, int coluna){
    return ((posicao + size - coluna ) / size) -1;
}






int** init_tabuleiro_random(int clues,  int size){

    int **tabuleiro = create_dyn_tabuleiro(size);  // cria a tabela dinamicamente de acordo com o size tudo a 0


    //array de size*size posicoes random a colocar no tabuleiro

    int *posicao = generate_positions_in_board(size*size);

    int smallest = 5000;
    int plinha=0, pcoluna =0, valor =0;

    for (int i = 0; i < clues ; i++) {
        for (int n = 0; n < size * size; n++) {


            int coluna = get_coluna_from_posicao(posicao[n], size);
            int linha = get_linha_from_posicao(posicao[n], size, coluna);

            int number;

            //testa se a box onde esta a tentar colocar o numero nao se encontra com apenas um elemento por preencher, evitando boxs completas
            if (box_if_almost_full(tabuleiro,size,linha,coluna, clues)==0 && line_is_almost_full(tabuleiro,size,coluna)==0 && column_is_almost_full(tabuleiro,size,coluna)==0) {
                int n_numbers_allowed = number_of_numbers_allowed_in_this_position(tabuleiro, linha, coluna, size,&number);

                if (n_numbers_allowed > 0 && n_numbers_allowed < smallest) {
                    smallest = n_numbers_allowed;
                    plinha = linha;
                    pcoluna = coluna;
                    valor = number;
                }
            }

        }
        tabuleiro[plinha][pcoluna] = valor;
        smallest = 5000,  plinha=0, pcoluna =0, valor =0;
    }
    return tabuleiro; // quando for solucionaval retorna o tabuleiro
}



int box_if_almost_full(int **tabuleiro, int size, int linha, int coluna, int clues) {
    int n = return_box_size(size);
    int number_of_values = 0;
    int almost_full = 0;


    if (clues < (size * size) - (9 * size)) almost_full = 9;
    else if (clues < (size * size) - (8 * size)) almost_full = 8;
    else if (clues < (size * size) - (7 * size)) almost_full = 7;
    else if (clues < (size * size) - (6 * size)) almost_full = 6;
    else if (clues < (size * size) - (5 * size)) almost_full = 5;
    else if (clues < (size * size) - (4 * size)) almost_full = 4;
    else if (clues < (size * size) - (3 * size)) almost_full = 3;
    else if (clues < (size * size) - (2 * size)) almost_full = 2;
    else if (clues < (size * size) - (1 * size)) almost_full = 1;
    else return 0;

    int li = 0, lf = 0, ci = 0, cf = 0;
    li = linha - (linha % n);
    lf = li + (n - 1);
    ci = coluna - (coluna % n);
    cf = ci + (n - 1);

    for (int i = li; i <= lf; i++) {
        for (int j = ci; j <= cf; j++) {

            if (tabuleiro[i][j] == 0) {
                number_of_values++;

            }
        }
    }
    if (number_of_values == almost_full) return 1;
    else return 0;

}

int line_is_almost_full(int **tabuleiro, int size,int linha){
    int almost_full=1;
    int number_of_values=0;
    for (int i = 0; i < size ; i++) {
        if(tabuleiro[linha][i] == 0){
            number_of_values++;
        }
    }
    if(number_of_values == 1) return 1;
    else return 0;

}

int column_is_almost_full(int **tabuleiro, int size,int coluna){
    int almost_full=1;
    int number_of_values=0;
    for (int i = 0; i < size ; i++) {
        if(tabuleiro[i][coluna] == 0){
            number_of_values++;
        }
    }
    if(number_of_values == almost_full) return 1;
    else return 0;
}







int number_of_numbers_allowed_in_this_position(int **tabuleiro,int linha, int coluna, int size,int * valor)
{
    int *numbers_possible = generate_positions_in_board(size);

    int allowed =0;

    for (int i = 0; i < size ; i++)
    {
        if (checkconsistency(tabuleiro, size, linha, coluna, *(numbers_possible+i)) == 1)
        {
            if(allowed == 0) *valor = *(numbers_possible+i);
            allowed++;
        }
    }
    return  allowed;

}




void print_tabuleiro(int **tabuleiro, int n) {
    int box_size= return_box_size(n);
    printf("\n---------------------------------\n      TABULEIRO SUDOKUX\n");
    for (int i = 0; i < n; ++i) {

        if(i % box_size ==0)printf("\n");
        printf("|");
        for (int j = 0; j < n; ++j) {
            if(j % box_size ==0)printf(" ");
            if((tabuleiro[i][j] / 10) < 1 ){ // testa se é um inteiro de dois ou um digito para a impressao ficar centrada
                printf("%d  ", tabuleiro[i][j]);
            }else{
            printf("%d ", tabuleiro[i][j]);}
        }
        printf("|\n");
    }
}


// criei esta funcao porque por alguma razao no consigo por a funcionar o sqrt no meu computador
int return_box_size(int size){
    int box_size = 0;
    if(size == 9)box_size = 3;
    else if(size == 16)box_size = 4;
    else if(size == 25)box_size = 5;
    else if(size == 36)box_size = 6;

    return  box_size;


}
