
//
// Created by pedro on 27/12/19.
//

#include "library.h"
#include <stdbool.h>


//MY_SOLVER


void find_mask_2(TABULEIRO *tab) {


    if (tab != NULL) {
        CEL *current, *pline;
        pline = tab->pfirst;
        current = tab->pfirst;



        //itera todas as celulas do tabuleiro
        for (int line = 0; line < tab->size; ++line) {
            for (int col = 0; col < tab->size; ++col) {
                //se a current celula nao tiver um numero colocado
                if(current->numero_possiblidades != 0){
                    free(current->possibilidades);
                    current->numero_possiblidades=0;
                }
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
                printf("numero de candidatos: %d \tcandidatos: ",current->numero_possiblidades);

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