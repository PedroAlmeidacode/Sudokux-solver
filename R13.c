//
// Created by pedro on 27/12/19.
//

#include "library.h"
#include <stdbool.h>





// se houver numeros apenas com um candidato na celula coloca se esse numero nessa celula
bool single_candidate_in_cel(TABULEIRO **t) {

    TABULEIRO *tab = *t;//cria instancia da struct tabuleiro

    CEL *current = tab->pfirst; // cria instancia de celula que aponta para a primeira celula da instancia de tabuleiro
    CEL *pline = current;

    for (int i = 0; i < tab->size; i++) {
        for (int j = 0; j < tab->size; j++) {

            if (current->numero_possiblidades == 1) {
                current->num = *(current->possibilidades);
                *t = tab; // iguala a instancia ao tabuleiro enviado como argumento
                return true;
            }
            current = current->e;
        }
        pline = pline->s;
        current = pline;

    }
    return false;
}


bool single_candidate_in_box_for_cel(TABULEIRO **t) {
    TABULEIRO *tab = *t;

    CEL *current = tab->pfirst;
    CEL *pline = current;
    //itera size * size celulas
    for (int i = 0; i < tab->size; i++) {
        for (int j = 0; j < tab->size; j++) {

            if (current->numero_possiblidades != 0) {

                for (int k = 0; k < current->numero_possiblidades; k++) {

                    //verifica se nao ha possiblidades de number nas outras celulas da caixa
                    if (repeated_candidate_in_box(current, *(current->possibilidades + k) == false)) {
                        current->num = *(current->possibilidades + k);
                        *t = tab;
                        return true;
                    }


                }

            }
            current = current->e;
        }
        pline = pline->s;
        current = pline;
    }
    return false;
}



//se esse numero nao for candidato de nunhuma das celulas da box

bool repeated_candidate_in_box(CEL *cel, int number) {
    CEL *current = cel;
    CEL *pline = current;
    put_current_cel_in_place(&current, current->li_box, current->ci_box);

    for (int i = current->li_box; i <= current->lf_box; i++) {
        for (int j = current->ci_box; j <= current->cf_box; j++) {

            if (current->numero_possiblidades != 0)
                for (int k = 0; k < current->numero_possiblidades; k++) {
                    if (*(current->possibilidades + k) == number) return true;
                }
            current = current->e;
        }
        pline = pline->s;
        current = pline;
    }

    return false;
}


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


void find_mask_2(TABULEIRO *tab) {

    if (tab != NULL) {
        CEL *current, *pline;
        pline = tab->pfirst;
        current = tab->pfirst;

        //itera todas as celulas do tabuleiro
        for (int line = 0; line < tab->size; ++line) {
            for (int col = 0; col < tab->size; ++col) {
                //se a current celula nao tiver um numero colocado
                if (current->num == 0) {
                    //itera os numeros possiveis naquela celula
                    for (int k = 1; k <= tab->size; k++) {

                        //testa se o numero k é possivel por nesta posicao
                        if (check_if_num_possible(current, tab, k) == 1) {
                            //se ainda nao tiver numeros possiveis , ou seja primeiro numero assigned para esta celula
                            if (current->numero_possiblidades == 0) {
                                current->possibilidades = (int *) malloc(
                                        sizeof(int));//aloca memoria para o numero (k) possivel
                                *(current->possibilidades) = k;//coloca o numero em possiblidades para a current celula
                                current->numero_possiblidades++;
                            } else {
                                //se ja tiver la um numero possivel realoca memoria para o novo numero
                                current->possibilidades = realloc((current->possibilidades),
                                                                  sizeof(int) * (current->numero_possiblidades + 1));
                                *(current->possibilidades +
                                  current->numero_possiblidades) = k;//coloca o numero em possiblidades para a current celula
                                current->numero_possiblidades++;
                            }

                        }
                    }
                }
                current = current->e;
            }
            pline = pline->s;
            current = pline;
        }
    }
}


void print_mask_2(TABULEIRO *tab) {
    CEL *current = tab->pfirst;
    CEL *pline = tab->pfirst;
    for (int i = 0; i < tab->size; i++) {
        for (int j = 0; j < tab->size; j++) {
            printf("[%d,%d]-> ", current->linha, current->coluna);
            if (current->num != 0) {
                printf("Numero %d atrbuido", current->num);
            } else {


                for (int k = 0; k < current->numero_possiblidades; k++) {
                    printf("%d ", *(current->possibilidades + k));

                }
            }
            printf("\n");
            current = current->e;
        }
        pline = pline->s;
        current = pline;
        printf("\n");
    }
}