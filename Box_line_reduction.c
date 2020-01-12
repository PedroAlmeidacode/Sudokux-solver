//
// Created by pedro on 12/01/20.
//

#include "library.h"



void box_line_reduction(TABULEIRO *tab){
    int number = 0;
    CEL *current = tab->pfirst;
    CEL *pline = current;
    CEL *line = NULL;
    CEL *col = NULL;
    for (int i = current->linha; i < tab->size; i++) { //percorre tabuleiro
        for (int j = current->coluna; j < tab->size; j++) {

            if (current->numero_possiblidades != 0){ // se o current nao tem numero assigned

                for (int k = 0; k < current->numero_possiblidades; k++) { //perorre possiblidades
                    number = *(current->possibilidades + k);

                    put_current_cel_in_place(&line, current->linha, 0);
                    put_current_cel_in_place(&col, 0, current->coluna);

                    for (int l = 0; l < tab->size - 1; l++) {//percorre a linha
                        if (line != current) { //nao passa pela mesma celula
                            if(line->numero_possiblidades != 0) { //se a cel de line nao tem numero assigned
                                for (int n = 0; k < line->numero_possiblidades; n++) {
                                    if (number == *(line->possibilidades + n)) {
                                        if (current->li_box == line->li_box && current->ci_box == line->ci_box) {
                                            delete_number_from_other_cels_of_box(&tab, line, current, number);
                                        }
                                    }
                                }
                            }
                        }
                        line = line->e;
                    }for (int m = 0; m < tab->size - 1; m++) {
                            if (col != current) {
                                if (col->numero_possiblidades != 0) {
                                    for (int n = 0; k < col->numero_possiblidades; n++) {
                                        if (number == *(col->possibilidades + n)) {
                                            if (current->li_box == col->li_box && current->ci_box == col->ci_box) {
                                                delete_number_from_other_cels_of_box(&tab, col, current, number);
                                            }
                                        }
                                    }
                                }

                            }
                        col = col->s;
                        }
                }
            }
            current = current->e;
        }
        pline = pline->s;
        current = pline;
    }
}


