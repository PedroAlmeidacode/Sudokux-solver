
//
// Created by pedro on 04/01/20.
//

#include "library.h"


/* Takes a partially filled-in grid and attempts to assign values to
  all unassigned locations in such a way to meet the requirements
  for Sudoku solution (non-duplication across rows, columns, and boxes) */
bool Solve_brute_force(TABULEIRO *tab, CEL *current) {



    if (is_complete(tab, &current) == true)
        return true; // success!

    // consider digits 1 to size
    for (int num = 1; num <= tab->size; num++) {


        // if looks promising
        if (check_if_num_possible(current, tab, num) == 1) {
            // make tentative assignment,
            current->num = num;

            print_tab(tab);

            // return, if success, yay!
            if (Solve_brute_force(tab,tab->pfirst))
                return true;

            // failure, unmake & try again
            current->num = 0;
        }
    }
    return false; // this triggers backtracking
}



/*percorre a grelha e retorna true se estiver completa , false se ainda tiver
 * posicoes unassigned*/
bool is_complete(TABULEIRO *tab, CEL **pCel){
    CEL *current = tab->pfirst;
    CEL *pline = current;
    int i,j;
    for (i = 0; i < tab->size; i++) {
        for (j = 0; j < tab->size; j++) {
            if (current->num == 0){
                *pCel = current;
                return false;

            }
            current= current->e;
        }
        pline = pline->s;
        current = pline;
    }
    return true;


}


int check_if_num_possible(CEL *cel, TABULEIRO *tab, int num){
    if(cel->num == 0) {
        if (no_repeated_num_in_line(cel, tab, num) == 1 &&
            no_repeated_num_in_box(cel,num) == 1 &&
            no_repeated_num_in_column(cel, tab, num) == 1 &&
            no_repeated_num_in_principal_diagonal(cel, tab, num) == 1 &&
            no_repeated_num_in_secondary_diagonal(cel, tab, num) == 1)
        {
            return 1;
        } else return 0;
    }else return 0;
}




int no_repeated_num_in_line(CEL *ref, TABULEIRO *tab, int num){

    CEL *current = ref;
    int coluna = current->coluna;
    if(coluna != 0){ //se a celula nao estiver na coluna 0 coloca cuurent na primeira coluna (0)
        put_current_cel_in_place(&current,current->linha,0);
    }

    for (int i = 0; i < tab->size; i++) {
        if (current->num == num) { // se houver esse numero ja na linha retorna falso (exite numero igual na linha )
            return 0;
        }
        current = current->e; //move a current para a celula a este
    }
    return 1;
}




int no_repeated_num_in_column(CEL *ref, TABULEIRO *tab, int num){
    CEL * current = ref;
    int linha = current->linha;
    if(linha != 0){ //se a celula nao estiver na linha 0 coloca cuurent na primeira linha (0)
        put_current_cel_in_place(&current,0,current->coluna);
    }
    for (int i = 0; i < tab->size; i++) {
        if (current->num == num) { //  se houver esse numero ja na coluna retorna falso (exite numero igual na coluna
            return 0;
        }
        current = current->s; //move a current para a celula a este
    }

    return 1;
}



int no_repeated_num_in_box(CEL *ref, int num) {
    CEL *current = ref;

    int ci = current->ci_box;
    int cf = current->cf_box;
    int li = current->li_box;
    int lf = current->lf_box;

    if(current->linha != current->li_box || current->coluna != current->ci_box ){ // escolhe a celula com a linha mais acima da caixa
        put_current_cel_in_place(&current,current->li_box,current->ci_box);
    }
    CEL *pline = current;

    for (int i = li; i <= lf; i++) {
        for (int j = ci; j <= cf; j++) {

            if(current->num == num){
                return 0;
            }
            current = current->e;
        }
        pline = pline->s;
        current = pline;
    }
    return 1;
}




int no_repeated_num_in_principal_diagonal(CEL *ref, TABULEIRO *tab, int num){
    CEL *current = ref;

    if(current->principal_diagonal == 0) { //a posicao a colocar nao faz parte sequer da diagonal principal
        return 1;
    }else{
        current = tab->pfirst;
        for (int i = 0; i < tab->size; i++) {
            if (current->num == num) {
                return 0;
            }
            current= current->se;
        }
        return 1;
    }
}

int no_repeated_num_in_secondary_diagonal(CEL *ref, TABULEIRO *tab, int num){
    CEL *current = ref;

    if(current->secondary_diagonal == 0){ // testa se esta nao esta na diagonal secundaria
        return 1;
    } else{
        current = tab->pfirst;
        put_current_cel_in_place(&current,0,tab->size-1);
        for (int i = 0; i < tab->size; i++) {
            if(current->num == num) {
                return 0;
            }
            current=current->so;
        }
        return 1;
    }
}








