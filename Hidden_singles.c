//
// Created by pedro on 12/01/20.
//
#include "library.h"


// se houver numeros apenas com um candidato na celula coloca se esse numero nessa celula
bool single_candidate_in_cel(TABULEIRO *tab) {

    //TABULEIRO *tab = *t;//cria instancia da struct tabuleiro

    CEL *current = tab->pfirst; // cria instancia de celula que aponta para a primeira celula da instancia de tabuleiro
    CEL *pline = current;

    for (int i = 0; i < tab->size; i++) {
        for (int j = 0; j < tab->size; j++) {

            if (current->numero_possiblidades == 1) {
                current->num = *(current->possibilidades);

                //*t = tab; // iguala a instancia ao tabuleiro enviado como argumento
                return true;
            }
            current = current->e;
        }
        pline = pline->s;
        current = pline;

    }
    return false;
}


bool single_candidate_in_box_for_cel(TABULEIRO *tab) {
    //TABULEIRO *tab = *t;

    CEL *current = tab->pfirst;
    CEL *pline = current;
    //itera size * size celulas
    for (int i = 0; i < tab->size; i++) {
        for (int j = 0; j < tab->size; j++) {

            if (current->numero_possiblidades != 0) {

                for (int k = 0; k < current->numero_possiblidades; k++) {

                    //verifica se nao ha possiblidades de number nas outras celulas da caixa
                    if (repeated_candidate_in_box(current, *(current->possibilidades + k)) == false) {
                        current->num = *(current->possibilidades + k);
                        //*t = tab;
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

    int ci = current->ci_box;
    int cf = current->cf_box;
    int li = current->li_box;
    int lf = current->lf_box;

    for (int i =li; i <= lf; i++) {
        for (int j = ci; j <= cf; j++) {

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





