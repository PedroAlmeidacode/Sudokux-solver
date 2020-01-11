#include "library.h"



// A Backtracking program  in C to solve Sudoku problem
#include <stdio.h>
#include <stdbool.h>

/* Takes a partially filled-in grid and attempts to assign values to
  all unassigned locations in such a way to meet the requirements
  for Sudoku solution (non-duplication across rows, columns, and boxes) */
bool SolveSudoku(int **grid, int size) {
    int row;
    int col;

    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(grid, &row, &col, size))
        return true; // success!

    // consider digits 1 to size
    for (int num = 1; num <= size; num++) {

        // if looks promising
        if (checkconsistency(grid, size, row, col, num) == 1) {
            // make tentative assignment
            grid[row][col] = num;

            // return, if success, yay!
            if (SolveSudoku(grid, size))
                return true;

            // failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // this triggers backtracking
}

/* Searches the grid to find an entry that is still unassigned. If
   found, the reference parameters row, col will be set the location
   that is unassigned, and true is returned. If no unassigned entries
   remain, false is returned. */
bool FindUnassignedLocation(int **grid, int *row, int *col, int size) {
    int i, j;


    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            *row = i;
            *col = j;
            if (grid[i][j] == UNASSIGNED) return true;
        }
    }
    return false;
}


int my_solver(int **tabuleiro, int size) {
    int alterou = 0;
    int mask[size][size][size];
    find_mask(mask, tabuleiro, size);

    while (checkgrid(tabuleiro, size) == 0) {

        exaustion_of_number_alone_rule(tabuleiro,mask,size);
        alterou = 0;
        exaustion_of_number_oculto_rule(tabuleiro,mask,size,&alterou);
        exaustion_pairs(tabuleiro,mask,size,&alterou);
        print_tabuleiro(tabuleiro,size);
        if(checkgrid(tabuleiro, size) == 1) return 1;
        if(alterou == 0) {
            if (SolveSudoku(tabuleiro,size)== 1) return 1;
            else return 0;
        }

    }
    return 1;
}

//leva a exaustao esta regra, ou seja depois de usar a regra vai atualizar a macara e continuamente ate nao dar
void exaustion_of_number_alone_rule(int **tabuleiro,int mask[N][N][N],int size){
    int n =0;

    while(n ==0) {
        if (puts_number_alone_in_tabuleiro(tabuleiro, mask, size) == 1) {
            find_mask(mask, tabuleiro, size);
            //printf("achou numeros sozimhos\\n");
            print_tabuleiro(tabuleiro,size);
        }
        else n++;
    }

}


//leva a exaustao esta regra, ou seja depois de usar a regra vai atualizar a macara e continuamente ate nao dar
void exaustion_of_number_oculto_rule(int **tabuleiro,int mask[N][N][N],int size, int *alterou){
    int n =0;

    while(n ==0){
        if(puts_number_oculto_alone_in_box(tabuleiro, mask, size)==1) {
            *alterou = 1;
            find_mask(mask, tabuleiro, size);
            //printf("achou numeros ocultos\n");
            print_tabuleiro(tabuleiro,size);
        }else n++;
    }


}
//leva a exaustao esta regra, ou seja depois de usar a regra vai atualizar a macara e continuamente ate nao dar
void exaustion_pairs(int **tabuleiro, int mask[N][N][N], int size, int *alterou) {
    int i = 0;
    while (i == 0) {

        if (naked_pairs_solver(tabuleiro, mask, size) == 1) {
            *alterou = 1;
            find_mask(mask, tabuleiro, size);
            //printf("achou pares\n");
            print_tabuleiro(tabuleiro,size);
        }else i++;
    }

}


void find_mask(int mask[N][N][N], int **tabuleiro, int size) {
    put_mask_to_zero(mask, size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            if (tabuleiro[i][j] == 0) {

                for (int k = 1; k <= size; k++) {

                    //testa se o numero k é possivel por nesta posicao
                    if (checkconsistency(tabuleiro, size, i, j, k) == 1) {

                        mask[i][j][k - 1] = k;

                    }

                }

            }

        }

    }

}

//colca todas as possiblidades de cada celula a 0
void put_mask_to_zero(int mask[N][N][N], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                mask[i][j][k] = 0;

            }
        }
    }
}
// se houver numeros apenas com um candidato na celula coloca se esse numero nessa celula
int puts_number_alone_in_tabuleiro(int **tabuleiro, int mask[N][N][N], int size) {
    int n = 0;
    int number = 0;
    int alterou = 0;
    //itera as linhas da mask
    for (int i = 0; i < size; i++) {
        //itera as colunas da mask
        for (int j = 0; j < size; j++) {
            number = 0;
            n = 0;
            //itera as possiblidades dentro de cada celula
            for (int k = 0; k < size; k++) {



                //se o numero a testar nao for 0 ou seja celulas com numero ja atribuido nao contam
                if (mask[i][j][k] != 0) {
                    n++;
                    number = mask[i][j][k];

                }
            }
            // se n = 1 apenas existe um numero dentro desta celula que esta guardado dentro de
            // number que sera colocado na respetiva celula do tabuleiro
            if (n == 1) {
                tabuleiro[i][j] = number;
                alterou++;
            }
        }
    }
    if (alterou > 0) return 1;
    else return 0;
}

int puts_number_oculto_alone_in_box(int **tabuleiro, int mask[N][N][N], int size) {
    int alterou = 0;

    //itera size * size celulas
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            int n = return_box_size(size);
            //calcula o tamanho da box
            int li = 0, lf = 0, ci = 0, cf = 0;
            li = i - (i % n);
            lf = li + (n - 1);
            ci = j - (j % n);
            cf = ci + (n - 1);

            //itera as possiblidades da celula [i,j]
            for (int k = 0; k < size; k++) {
                //se é uma possiblidade
                if (mask[i][j][k] != 0) {
                    int number = mask[i][j][k];

                    //verifica se nao ha possiblidades de number nas outras celulas da caixa
                    if (not_repeated_in_box_of_mask(mask, li, lf, ci, cf, number, size) == 1) {
                        //coloca essa possiblidade assumida na celula
                        tabuleiro[i][j] = number;
                        alterou++;
                    }

                }

            }

        }
    }
    if (alterou > 0) return 1;
    else return 0;
}

//se esse numero nao for candidato de nunhuma das celulas da box
int not_repeated_in_box_of_mask(int mask[N][N][N], int li, int lf, int ci, int cf, int number, int size) {
    int n = 0;
    for (int i = li; i <= lf; i++) {
        for (int j = ci; j <= cf; j++) {

            for (int k = 0; k < size; k++) {
                if (number == mask[i][j][k]) n++;
            }
        }
    }

    if (n == 1) {
        return 1;
    } else return 0;

}


int naked_pairs_solver(int **tabuleiro, int mask[N][N][N], int size) {
    int alterou = 0;
    //itera a mask , todas as celulas
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int two = 0;
            int pair[2];
            //itera os candidatos de cada celula
            for (int k = 0; k < size; k++) {
                //se o candidato é um numero
                if (mask[i][j][k] != 0) {
                    two++;
                    if (two == 1) pair[0] = mask[i][j][k];//coloca o primeiro numero do par na primeira posicao de pair
                    if (two == 2) pair[1] = mask[i][j][k];//coloca o segundo numero do par na segunda posicao de pair
                }
            }
            //se existe uma celula que apenas tem dois candidatos , vai procurar outra celula com apenas esses dois candidatos
            if (two == 2) {
                int linha_second_pair = 0;
                int col_second_pair = 0;
                int found = 0;
                int linha = i;
                int coluna = j;
                while (found == 0) {
                    //encontra a celula do segundo par se houver um segundo par retorna 1,
                    // guarda em linha_second_pair a linha do segundo par e em col_second_pair a coluna do segundo par
                    if (find_second_naked_pair(pair, linha, coluna, &linha_second_pair, &col_second_pair, mask, size) == 1) {
                        //printf(" encontrou uma celula com os mesmos numeros em [%d,%d]\n",linha_second_pair,col_second_pair);
                        int assigned = 0;
                        //verifica se as duas celulas com os pares encontram se na mesma caixa
                        if (two_pairs_in_the_same_box(i, j, linha_second_pair, col_second_pair, size) == 1) {
                            assigned++;
                            //apaga o par de  candidatos de outras celulas que nao as do primeiro par e do segundo par na caixa
                            delete_candidates_pair_numbers_from_box_of_mask(mask, i, j, linha_second_pair,
                                                                            col_second_pair,
                                                                            size, pair);
                        }
                        //verifica se estao os dois na diagonal principal
                        if (i == j && linha_second_pair == col_second_pair) {
                            assigned++;
                            delete_mask_pair_numbers_from_principal_diagonal(mask, i, j, linha_second_pair,
                                                                             col_second_pair,
                                                                             size, pair);
                        }
                        //verifica se  esta0o os dois na diagonal secundaria
                        if (i == size - 1 - j && linha_second_pair == size - 1 - col_second_pair) {
                            assigned++;
                            delete_mask_pair_numbers_from_secondary_diagonal(mask, i, j, linha_second_pair,
                                                                             col_second_pair,
                                                                             size, pair);
                        }
                        //verifica se encontram na mesma linha
                        if (i == linha_second_pair) {
                            assigned++;
                            //apaga o par de  candidatos de outras celulas que nao as do primeiro par e do segundo par na linha
                            delete_mask_pair_numbers_from_line(mask, i, size, j, col_second_pair, pair);
                        }
                        //verifica se encontram na mesma coluna
                        if (j == col_second_pair) {
                            assigned++;
                            //apaga o par de  candidatos de outras celulas que nao as do primeiro par e do segundo par na coluna
                            delete_mask_pair_numbers_from_col(mask, j, size, i, linha_second_pair, pair);
                        }

                        //apenas coloca se estas duas celulas se encontrarem na mesma linha/coluna/box ou ate as 3 ou 2 delas
                        if (assigned > 0) {
                            found++;
                            //coloca o primeiro numero do par de numeros na primeira celula encontrada
                            tabuleiro[i][j] = pair[0];
                            //coloca o segundo numero do par de numeros na celula encontrada igual a primeira
                            tabuleiro[linha_second_pair][col_second_pair] = pair[1];
                            //iguala as duas celulas com os candidatos a 0 depois de colocar la o numero, visto que ja nao precisa de candidatos
                            for (int k = 0; k < size; k++) {
                                mask[i][j][k] = 0;
                                mask[linha_second_pair][col_second_pair][k] = 0;
                                alterou++;
                            }
                            //se a csegundaelula nao for admitida ou seja nao se encontra de acordo com as regras vai se ter que tentar encontrar outra segunda
                            // celula igual  apartir do ponto onde se parou
                        }else{
                            if(col_second_pair == size -1) {
                                linha = linha_second_pair + 1;
                                coluna = 0;
                            }else {
                                linha = linha_second_pair;
                                coluna = col_second_pair + 1;
                            }

                        }
                    }else found++; // nao foi encontrada segunda celula com os numeros procurados ou as que existem nao cumprem os parametros
                }

            }


        }
    }
    if (alterou > 0) return 1;
    else return 0;


}
//apaga das celulas, da diagonal principal que tiverem estes dois candidato, colocando os a 0
void delete_mask_pair_numbers_from_principal_diagonal(int mask[N][N][N], int linha_first_pair, int coluna_first_pair,
                                                      int linha_second_pair, int coluna_second_pair, int size,
                                                      const int pair[2]) {
    int j = 0;
    for (int i = 0; i < size; i++) {

        // para nao testar dentro das celulas do primeiro e segundo par
        if (i != linha_first_pair && j != coluna_first_pair && i != linha_second_pair && j != coluna_second_pair) {

            for (int k = 0; k < size; k++) {
                if (mask[i][j][k] != 0) {
                    if (pair[0] == mask[i][j][k]) mask[i][j][k] = 0;
                    if (pair[1] == mask[i][j][k]) mask[i][j][k] = 0;
                }
            }
        }
        j++;
    }

}
//apaga das celulas, da diagonal secundaria que tiverem estes dois candidato, colocando os a 0
void delete_mask_pair_numbers_from_secondary_diagonal(int mask[N][N][N], int linha_first_pair, int coluna_first_pair,
                                                      int linha_second_pair, int coluna_second_pair, int size,
                                                      const int pair[2]) {
    int j = size - 1;

    for (int i = 0; i < size; i++) {
// para nao testar dentro das celulas do primeiro e segundo par
        if (i != linha_first_pair && j != coluna_first_pair && i != linha_second_pair && j != coluna_second_pair) {

            for (int k = 0; k < size; k++) {
                if (mask[i][j][k] != 0) {
                    if (pair[0] == mask[i][j][k]) mask[i][j][k] = 0;
                    if (pair[1] == mask[i][j][k]) mask[i][j][k] = 0;
                }
            }
        }


        j--;
    }


}
//apaga das celulas, da caixa que tiverem estes dois candidato, colocando os a 0
void delete_candidates_pair_numbers_from_box_of_mask(int mask[N][N][N], int linha_first_pair, int coluna_first_pair,
                                                     int linha_second_pair, int coluna_second_pair, int size,
                                                     const int pair[2]) {
    int n = return_box_size(size);
    //calcula o tamanho da box do primeiro para
    int li = 0, lf = 0, ci = 0, cf = 0;
    li = linha_first_pair - (linha_first_pair % n);
    lf = li + (n - 1);
    ci = coluna_first_pair - (coluna_first_pair % n);
    cf = ci + (n - 1);

    for (int i = li; i <= lf; i++) {
        for (int j = ci; j <= cf; j++) {

            // para nao testar dentro das celulas do primeiro e segundo par
            if (i != linha_first_pair && j != coluna_first_pair && i != linha_second_pair && j != coluna_second_pair) {

                for (int k = 0; k < size; k++) {
                    if (mask[i][j][k] != 0) {
                        if (pair[0] == mask[i][j][k]) mask[i][j][k] = 0;
                        if (pair[1] == mask[i][j][k]) mask[i][j][k] = 0;
                    }
                }
            }
        }
    }
}

//apaga das celulas, da coluna, que tiverem estes dois candidato, colocando os a 0
void delete_mask_pair_numbers_from_col(int mask[N][N][N], int coluna, int size, int linha_first_pair, int linha_second_pair,
                                       const int pair[2]) {
    //itera a coluna em que os dois pares se encontram
    for (int i = 0; i < size; i++) {
        //se nao sao as duas celulas dos pares ou seja encontram se na mesma linha que o mesmo
        if (i != linha_first_pair && i != linha_second_pair) {
            //ietra os candidatos
            for (int k = 0; k < size; k++) {
                //se o valor do candidato da celula for igual ao do par
                if (pair[0] == mask[i][coluna][k]) mask[i][coluna][k] = 0; // retira esse candidato da celula
                if (pair[1] == mask[i][coluna][k]) mask[i][coluna][k] = 0; // retira esse candidato da celula
            }
        }

    }


}
//apaga das celulas, da linha,  que tiverem estes dois candidato, colocando os a 0
void delete_mask_pair_numbers_from_line(int mask[N][N][N], int linha, int size, int coluna_first_pair,
                                        int coluna_second_pair, const int pair[2]) {
    //itera a linha em que os dois pares se encontram
    for (int j = 0; j < size; j++) {
        //se nao sao as duas celulas dos pares ous eja encontram se na mesma coluna que o mesmo
        if (j != coluna_first_pair && j != coluna_second_pair) {
            //ietra os candidatos
            for (int k = 0; k < size; k++) {
                //se o valor do candidato da celula for igual ao do par
                if (pair[0] == mask[linha][j][k]) mask[linha][j][k] = 0; // retira esse candidato da celula
                if (pair[1] == mask[linha][j][k]) mask[linha][j][k] = 0; // retira esse candidato da celula
            }
        }

    }


}

int two_pairs_in_the_same_box(int i, int j, int linha_second_pair, int col_second_pair, int size) {
    int n = return_box_size(size);

    //calcula o tamanho da box do primeiro para
    int li = 0, lf = 0, ci = 0, cf = 0;
    li = i - (i % n);
    lf = li + (n - 1);
    ci = j - (j % n);
    cf = ci + (n - 1);

    //verifica se o segundo par esta dentro da box do primeiro par
    if (linha_second_pair >= li && linha_second_pair <= lf && col_second_pair >= cf && col_second_pair <= cf) return 1;
    else return 0;


}

//enontra a segunda celula que tem o primeiro par de numeros
int find_second_naked_pair(const int first_pair[2], int linha, int col, int *linha_second_pair, int *col_second_pair,
                           int mask[N][N][N], int size) {


    //two equal- variavel que testara se existem dois numeros iguais aos do first pair
    //two_numbers_in_possibilities- variavel que testara se existem apenas dois numeros nas possiblidades da celula
    int two_equal, two_numbers_in_possibilities;

    //percorre celula a celula
    for (int i = linha; i < size; i++) {
        for (int j = col + 1; j < size; j++) {

            two_equal = 0;
            two_numbers_in_possibilities = 0;




            //percorre as possiblidades da celula
            for (int k = 0; k < size; k++) {
                //se for uma possiblidade
                if (mask[i][j][k] != 0) {
                    //se for uma das possiblidades do primeiro par
                    if (first_pair[0] == mask[i][j][k] || first_pair[1] == mask[i][j][k]) {
                        two_equal++;

                    }
                    two_numbers_in_possibilities++;

                }

            }
            // se tiver dois numeros igauis e apenas duas possiblidades nessa celula
            if (two_equal == 2 && two_numbers_in_possibilities == 2) {
                //guarda a linha e a coluna do segundo par
                *linha_second_pair = i;
                *col_second_pair = j;
                //retorna 1 porque existe um par pelo menos
                return 1;

            }

        }
    }
    //se nao existir um par gual retorna 0
    return 0;
}


void print_mask(int size, int mask[N][N][N]) {
    int n_zeros = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("\ntabuleiro: [%d,%d] ->  ", i, j);
            for (int k = 0; k < size; k++) {
                if (mask[i][j][k] == 0) {
                    n_zeros++;
                }
                if (mask[i][j][k] != 0) printf("%d ", mask[i][j][k]);

            }
            if (n_zeros == size) printf("numero atribuido");
            n_zeros = 0;
        }
        printf("\n");
    }
}