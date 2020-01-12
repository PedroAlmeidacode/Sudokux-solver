//
// Created by pedro on 12/01/20.
//

#include "library.h"



void pointing_pairs(TABULEIRO *tab) {

    //TABULEIRO *tab = *t;
    CEL *current = tab->pfirst;
    CEL *pline = current;

    int numero = 0;
    int segundo_numero = 0;

    CEL *box = current;
    CEL *pbox = current;



    //percorre celula a celula do tabuleiro
    for (int i = 0; i < tab->size; i++) {
        for (int j = 0; j < tab->size; j++) {
            //se fro uma celula com candidatos
            if (current->num == 0 && current->numero_possiblidades != 0) {



                int ci = current->ci_box;
                int cf = current->cf_box;
                int li = current->li_box;
                int lf = current->lf_box;
                //percorre os candidatos de current
                for (int k = 0; k < current->numero_possiblidades; k++) {
                    numero = *(current->possibilidades + k);


                    put_current_cel_in_place(&box, li, ci);
                    //percorre a caixa onde current se encontra
                    for (int l = ci; l < lf; l++) {
                        for (int m = ci; m< cf; m++) {
                            //se a celula box nao tivr assiged number
                            if (box->num == 0 && box->numero_possiblidades != 0) {
                                //nao comparar a mesma celula
                                if (box != current) {
                                    //percorrer o numero de canidatos da segunda celula
                                    for (int k = 0; k < box->numero_possiblidades; k++) {
                                        segundo_numero = *(box->possibilidades + k);

                                        if (numero == segundo_numero) {

                                            if (box->linha == current->linha) {
                                                delete_number_from_other_cels_of_line(&tab, current, box,numero);
                                            }
                                            if (box->coluna == current->coluna) {

                                                delete_number_from_other_cels_of_col(&tab, current, box,numero);
                                            }

                                        }
                                    }
                                }


                            }
                            box = box->e;

                        }
                        pbox = pbox->s;
                        current = pbox;
                    }
                }
            }



            current = current->e;

            }
            pline = pline->s;
            current = pline;
        }

}

//apaga das celulas, da caixa que tiverem estes dois candidato,
void delete_number_from_other_cels_of_line(TABULEIRO **t, CEL *first_pair, CEL *second_pair, int num) {

    TABULEIRO *tab = *t;
    CEL *current = first_pair;

    //ponho current na primeira celula da caixa
    put_current_cel_in_place(&current, current->linha, 0);
    for (int i = 0; i <= tab->size - 1; i++) { //itero toda as posicoes da linha

        //se for uma caixa sem nuemro assigned
        if (current->numero_possiblidades != 0) {


            //se current nao for a celula do primeiro ou segundo par
            if (current->linha != first_pair->linha && current->coluna != first_pair->coluna) {
                if (current->linha != second_pair->linha && current->coluna != second_pair->coluna) {

                    //itera as possiblidades de current
                    for (int k = 0; k < current->numero_possiblidades; k++) {

                        // se o nuemro atual do pointer possiblidades for igual ou ao primeiro ou ao segundo nuemro do par
                        if (*(current->possibilidades + k) == num) {
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
void delete_number_from_other_cels_of_col(TABULEIRO **t, CEL *first_pair, CEL *second_pair, int num) {

    TABULEIRO *tab = *t;
    CEL *current = first_pair;

    //ponho current na primeira celula da caixa
    put_current_cel_in_place(&current, 0, current->coluna);
    for (int i = 0; i <= tab->size - 1; i++) { //itero toda as posicoes da caixa

        //se for uma caixa sem nuemro assigned
        if (current->numero_possiblidades != 0) {


            //se current nao for a celula do primeiro ou segundo par
            if (current->linha != first_pair->linha && current->coluna != first_pair->coluna) {
                if (current->linha != second_pair->linha && current->coluna != second_pair->coluna) {

                    //itera as possiblidades de current
                    for (int k = 0; k < current->numero_possiblidades; k++) {

                        // se o nuemro atual do pointer possiblidades for igual ou ao primeiro ou ao segundo nuemro do par
                        if (*(current->possibilidades + k) == num) {
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


//apaga das celulas, da caixa que tiverem estes dois candidato,
    void delete_number_from_other_cels_of_box(TABULEIRO **t, CEL *first_pair, CEL *second_pair, int number) {

        TABULEIRO *tab = *t;
        CEL *current = first_pair;
        CEL *pline = current;

        int ci = current->ci_box;
        int cf = current->cf_box;
        int li = current->li_box;
        int lf = current->lf_box;
        //ponho current na primeira celula da caixa
        put_current_cel_in_place(&current, current->li_box, current->ci_box);
        for (int i = li; i <= lf; i++) { //itero toda as posicoes da caixa
            for (int j = ci; j <= cf; j++) {
                //se for uma caixa sem nuemro assigned
                if (current->numero_possiblidades != 0) {


                    //se current nao for a celula do primeiro ou segundo par
                    if (current->linha != first_pair->linha && current->coluna != first_pair->coluna) {
                        if (current->linha != second_pair->linha && current->coluna != second_pair->coluna) {

                            //itera as possiblidades de current
                            for (int k = 0; k < current->numero_possiblidades; k++) {

                                // se o nuemro atual do pointer possiblidades for igual ou ao primeiro ou ao segundo nuemro do par
                                if (*(current->possibilidades + k) == number ){
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
