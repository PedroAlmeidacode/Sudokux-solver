//
// Created by pedro on 12/01/20.
//

#include "library.h"


bool naked_pairs(TABULEIRO **t) {
    TABULEIRO *tab = *t;
    CEL *current = tab->pfirst;
    CEL *pline = current;

    CEL *first_pair = NULL;
    CEL *second_pair = NULL;

    int alterou = 0;


    //itera a mask , todas as celulas
    for (int i = 0; i < tab->size; i++) {
        for (int j = 0; j < tab->size; j++) {

            if (current->numero_possiblidades ==
                2) { // se a celula tiver dois candidatos e nao for uma celula que ja tem um numero assigned
                first_pair = current;

                second_pair = find_second_pair(tab, first_pair);

                if (second_pair != NULL) {
                    // se realmente encontrou um segundo par

                    //se cumpre alguma das regras assigned deve ser maior do que 0
                    int assigned = 0;
                    //se os dois pares estao na mesma caixa
                    if (first_pair->li_box == second_pair->li_box && first_pair->ci_box == second_pair->ci_box) {
                        assigned++;
                        //apaga o par de  candidatos de outras celulas que nao as do primeiro par e do segundo par na caixa
                        delete_same_in_other_cels_of_box(&tab, first_pair, second_pair);
                    }
                    //verifica se estao os dois na diagonal principal
                    if (first_pair->principal_diagonal == true && second_pair->principal_diagonal == true) {
                        assigned++;
                        delete_same_in_other_cels_of_principal_diagonal(&tab, first_pair, second_pair);
                    }
                    //verifica se  esta0o os dois na diagonal secundaria
                    if (first_pair->secondary_diagonal == true && second_pair->secondary_diagonal == true) {
                        assigned++;
                        delete_same_in_other_cels_of_secondary_diagonal(&tab, first_pair, second_pair);
                    }
                    //verifica se encontram na mesma linha
                    if (first_pair->linha == second_pair->linha) {
                        assigned++;
                        //apaga o par de  candidatos de outras celulas que nao as do primeiro par e do segundo par na linha
                        delete_same_in_other_cels_of_line(&tab, first_pair, second_pair);
                    }
                    //verifica se encontram na mesma coluna
                    if (first_pair->coluna == second_pair->coluna) {
                        assigned++;
                        //apaga o par de  candidatos de outras celulas que nao as do primeiro par e do segundo par na coluna
                        delete_same_in_other_cels_of_col(&tab, first_pair, second_pair);
                    }

                    //apenas coloca se estas duas celulas se encontrarem na mesma linha/coluna/box ou ate as 3 ou 2 delas
                    if (assigned > 0) {
                        //coloca se o primeiro candidato na primeira celula e o segundo candidato na segunda celula
                        first_pair->num = *(first_pair->possibilidades);
                        second_pair->num = *(second_pair->possibilidades + 1);

                        //iguala as duas celulas com os candidatos a 0 depois de colocar la o numero, visto que ja nao precisa de candidatos
                        first_pair->numero_possiblidades = 0;
                        first_pair->possibilidades = NULL;
                        second_pair->numero_possiblidades = 0;
                        second_pair->possibilidades = NULL;
                        alterou ++;

                    }
                }
            }
            current = current->e;
        }
        pline = pline->s;
        current = pline;

    }
    *t = tab;
    if(alterou != 0) return true;
    else return false;

}


//apaga das celulas, da caixa que tiverem estes dois candidato,
void delete_same_in_other_cels_of_box(TABULEIRO **t, CEL *first_pair, CEL *second_pair) {

    TABULEIRO *tab = *t;
    CEL *current = first_pair;
    CEL *pline = current;

    //ponho current na primeira celula da caixa
    put_current_cel_in_place(&current, current->li_box, current->ci_box);
    for (int i = current->li_box; i <= current->lf_box; i++) { //itero toda as posicoes da caixa
        for (int j = current->ci_box; j <= current->cf_box; j++) {
            //se for uma caixa sem nuemro assigned
            if (current->numero_possiblidades != 0) {


                //se current nao for a celula do primeiro ou segundo par
                if (current->linha != first_pair->linha && current->coluna != first_pair->coluna) {
                    if (current->linha != second_pair->linha && current->coluna != second_pair->coluna) {

                        //itera as possiblidades de current
                        for (int k = 0; k < current->numero_possiblidades; k++) {

                            // se o nuemro atual do pointer possiblidades for igual ou ao primeiro ou ao segundo nuemro do par
                            if (*(current->possibilidades + k) == *(first_pair->possibilidades) ||
                                *(current->possibilidades + k) == *(first_pair->possibilidades + 1)) {
                                // apago a possiblidade , deaoloco memoria e junto a proxima posicao a esta
                                delete_num_from_possiblidades(&current, k);

                            }
                        }
                    }
                }
            }
            current = current->e;
        }
        pline = pline->s;
        current = pline;
    }

    *t = tab;
}


//apaga das celulas, da caixa que tiverem estes dois candidato,
void delete_same_in_other_cels_of_principal_diagonal(TABULEIRO **t, CEL *first_pair, CEL *second_pair) {

    TABULEIRO *tab = *t;
    CEL *current = first_pair;

    //ponho current na primeira celula da caixa
    put_current_cel_in_place(&current, 0, 0);
    for (int i = 0; i <= tab->size; i++) { //itero toda as posicoes da caixa

        //se for uma caixa sem nuemro assigned
        if (current->numero_possiblidades != 0) {


            //se current nao for a celula do primeiro ou segundo par
            if (current->linha != first_pair->linha && current->coluna != first_pair->coluna) {
                if (current->linha != second_pair->linha && current->coluna != second_pair->coluna) {

                    //itera as possiblidades de current
                    for (int k = 0; k < current->numero_possiblidades; k++) {

                        // se o nuemro atual do pointer possiblidades for igual ou ao primeiro ou ao segundo nuemro do par
                        if (*(current->possibilidades + k) == *(first_pair->possibilidades) ||
                            *(current->possibilidades + k) == *(first_pair->possibilidades + 1)) {
                            // apago a possiblidade , deaoloco memoria e junto a proxima posicao a esta
                            delete_num_from_possiblidades(&current, k);

                        }
                    }
                }
            }
        }
        current = current->se;
    }
    *t = tab;
}


//apaga das celulas, da caixa que tiverem estes dois candidato,
void delete_same_in_other_cels_of_secondary_diagonal(TABULEIRO **t, CEL *first_pair, CEL *second_pair) {

    TABULEIRO *tab = *t;
    CEL *current = first_pair;

    //ponho current na primeira celula da caixa
    put_current_cel_in_place(&current, 0, tab->size - 1);
    for (int i = 0; i <= tab->size; i++) { //itero toda as posicoes da caixa

        //se for uma caixa sem nuemro assigned
        if (current->numero_possiblidades != 0) {


            //se current nao for a celula do primeiro ou segundo par
            if (current->linha != first_pair->linha && current->coluna != first_pair->coluna) {
                if (current->linha != second_pair->linha && current->coluna != second_pair->coluna) {

                    //itera as possiblidades de current
                    for (int k = 0; k < current->numero_possiblidades; k++) {

                        // se o nuemro atual do pointer possiblidades for igual ou ao primeiro ou ao segundo nuemro do par
                        if (*(current->possibilidades + k) == *(first_pair->possibilidades) ||
                            *(current->possibilidades + k) == *(first_pair->possibilidades + 1)) {
                            // apago a possiblidade , deaoloco memoria e junto a proxima posicao a esta
                            delete_num_from_possiblidades(&current, k);

                        }
                    }
                }
            }
        }
        current = current->so;
    }
    *t = tab;
}



//apaga das celulas, da caixa que tiverem estes dois candidato,
void delete_same_in_other_cels_of_line(TABULEIRO **t, CEL *first_pair, CEL *second_pair) {

    TABULEIRO *tab = *t;
    CEL *current = first_pair;

    //ponho current na primeira celula da caixa
    put_current_cel_in_place(&current, current->linha, 0);
    for (int i = 0; i <= tab->size; i++) { //itero toda as posicoes da caixa

        //se for uma caixa sem nuemro assigned
        if (current->numero_possiblidades != 0) {


            //se current nao for a celula do primeiro ou segundo par
            if (current->linha != first_pair->linha && current->coluna != first_pair->coluna) {
                if (current->linha != second_pair->linha && current->coluna != second_pair->coluna) {

                    //itera as possiblidades de current
                    for (int k = 0; k < current->numero_possiblidades; k++) {

                        // se o nuemro atual do pointer possiblidades for igual ou ao primeiro ou ao segundo nuemro do par
                        if (*(current->possibilidades + k) == *(first_pair->possibilidades) ||
                            *(current->possibilidades + k) == *(first_pair->possibilidades + 1)) {
                            // apago a possiblidade , deaoloco memoria e junto a proxima posicao a esta
                            delete_num_from_possiblidades(&current, k);

                        }
                    }
                }
            }
        }
        current = current->e;
    }
    *t = tab;
}

//apaga das celulas, da caixa que tiverem estes dois candidato,
void delete_same_in_other_cels_of_col(TABULEIRO **t, CEL *first_pair, CEL *second_pair) {

    TABULEIRO *tab = *t;
    CEL *current = first_pair;

    //ponho current na primeira celula da caixa
    put_current_cel_in_place(&current, 0, current->coluna);
    for (int i = 0; i <= tab->size; i++) { //itero toda as posicoes da caixa

        //se for uma caixa sem nuemro assigned
        if (current->numero_possiblidades != 0) {


            //se current nao for a celula do primeiro ou segundo par
            if (current->linha != first_pair->linha && current->coluna != first_pair->coluna) {
                if (current->linha != second_pair->linha && current->coluna != second_pair->coluna) {

                    //itera as possiblidades de current
                    for (int k = 0; k < current->numero_possiblidades; k++) {

                        // se o nuemro atual do pointer possiblidades for igual ou ao primeiro ou ao segundo nuemro do par
                        if (*(current->possibilidades + k) == *(first_pair->possibilidades) ||
                            *(current->possibilidades + k) == *(first_pair->possibilidades + 1)) {
                            // apago a possiblidade , deaoloco memoria e junto a proxima posicao a esta
                            delete_num_from_possiblidades(&current, k);

                        }
                    }
                }
            }
        }
        current = current->s;
    }
    *t = tab;
}



int *delete_num_from_possiblidades(CEL **pCel, int posicao) {

    CEL *current = *pCel;
    current->numero_possiblidades = current->numero_possiblidades - 1;
    int *ppossiblidades = malloc(sizeof(int) * (current->numero_possiblidades));

    int i = 0;

    for (int k = 0; k < current->numero_possiblidades; k++) {
        if (k == posicao) i++;
        *(ppossiblidades + k) = *(current->possibilidades + k + i);
    }

    current->possibilidades = ppossiblidades;

    *pCel = current;

}



//enontra a segunda celula que tem os mesmos candidatos que a primeira celula
CEL *find_second_pair(TABULEIRO *tab, CEL *first_pair) {

    CEL *current = first_pair->e; //comeca a comparar na celula imediatamente a direita da que encontrou o primeiro par
    CEL *pline = current;


    //percorre celula a celula
    for (int i = current->linha; i < tab->size; i++) {
        for (int j = current->coluna; j < tab->size; j++) {

            if (current->numero_possiblidades == 2 && *(current->possibilidades) == *(first_pair->possibilidades) &&
                *(current->possibilidades + 1) == *(first_pair->possibilidades +
                                                    1)) { // se a celula tiver dois candidatos e nao for uma celula que ja tem um numero assigned
                return current;
            }
            current = current->e;
        }
        pline = pline->s;
        current = pline;
    }
    return NULL;
}
