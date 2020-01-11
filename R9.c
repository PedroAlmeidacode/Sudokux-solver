//
// Created by pedro on 26/12/19.
//

#include "library.h"


void init_linked_tabuleiro(int size, TABULEIRO *tab){

    int n = return_box_size(size);
    CEL *current = malloc(sizeof(CEL)), *prevLine, *prevCol;
    tab->pfirst = current;
    prevCol = tab->pfirst;
    prevLine = tab->pfirst;
    tab->size = size;



    //percorre o tabuleiro que se encontra no array auxiliar para criara  lista ligada
    for (int line = 0; line < tab->size; ++line) {
        for (int col = 0; col < tab->size; ++col) {


            if (line == 0 && col == 0) { // se estiver na celula head
                current->principal_diagonal = 1;
                current->secondary_diagonal = 0;
                current->num = 0;
                current->numero_possiblidades=0;
                current->li_box = line -(line % n);
                current->ci_box = col - (col % n);
                current->lf_box = current->li_box + (n-1);
                current->cf_box = current->ci_box + (n-1);

                current->linha= line;
                current->coluna = col;
                current->n = NULL;
                current->ne = NULL;
                current->e = malloc(sizeof(CEL));
                current->se = malloc(sizeof(CEL));
                current->s = malloc(sizeof(CEL));
                current->so = NULL;
                current->o = NULL;
                current->no = NULL;
            }
            if (line == 0 && col != 0 && col != tab->size - 1) { // se estiver na primeira linha e nao na primeira nem ultima coluna
                current->principal_diagonal = 0;
                current->secondary_diagonal = 0;
                current->num = 0;
                current->numero_possiblidades=0;
                current->li_box = line -(line % n);
                current->ci_box = col - (col % n);
                current->lf_box = current->li_box + (n-1);
                current->cf_box = current->ci_box + (n-1);
                current->linha= line;
                current->coluna = col;
                current->n = NULL;
                current->ne = NULL;
                current->e = malloc(sizeof(CEL));
                current->se = malloc(sizeof(CEL));
                current->s = prevCol->se;
                current->so = prevCol->s;
                current->o = prevCol;
                current->no = NULL;
            }
            if (line == 0 && col == tab->size - 1) { // se estiver na ultima coluna da primeira linha
                current->principal_diagonal = 0;
                current->secondary_diagonal = 1;
                current->num = 0;
                current->numero_possiblidades=0;
                current->li_box = line -(line % n);
                current->ci_box = col - (col % n);
                current->lf_box = current->li_box + (n-1);
                current->cf_box = current->ci_box + (n-1);
                current->linha= line;
                current->coluna = col;
                current->n = NULL;
                current->ne = NULL;
                current->e = NULL;
                current->se = NULL;
                current->s = prevCol->se;
                current->so = prevCol->s;
                current->o = prevCol;
                current->no = NULL;
            }
            if (line != 0 && col == 0 && line != tab->size - 1) { // se estiver na primeira coluna e nao na primeira nem ultima linha
                current->principal_diagonal = 0;
                current->secondary_diagonal = 0;
                current->num = 0;
                current->numero_possiblidades=0;
                current->li_box = line -(line % n);
                current->ci_box = col - (col % n);
                current->lf_box = current->li_box + (n-1);
                current->cf_box = current->ci_box + (n-1);
                current->linha= line;
                current->coluna = col;
                current->n = prevLine;
                current->ne = prevLine->e;
                current->e = prevLine->se;
                current->se = malloc(sizeof(CEL));
                current->s = malloc(sizeof(CEL));
                current->so = NULL;
                current->o = NULL;
                current->no = NULL;
            }
            if (line != 0 && col != 0 && col != tab->size - 1) { // se nao estiver na primeira linha nem primeira coluna nem ultima coluna
                if(line == col) {
                    current->principal_diagonal = 1;
                }else { current->principal_diagonal = 0;}

                if(line == tab->size -1 - col) {
                    current->secondary_diagonal = 1;
                }else{ current->secondary_diagonal = 0;}

                current->num = 0;
                current->numero_possiblidades=0;
                current->li_box = line -(line % n);
                current->ci_box = col - (col % n);
                current->lf_box = current->li_box + (n-1);
                current->cf_box = current->ci_box + (n-1);
                current->linha= line;
                current->coluna = col;
                current->n = prevCol->ne;
                current->ne = prevCol->ne->e;
                current->e = prevCol->ne->se;
                current->se = malloc(sizeof(CEL));
                current->s = prevCol->se;
                current->so = prevCol->s;
                current->o = prevCol;
                current->no = prevCol->n;
            }
            if (line != 0 && col != 0 && col == tab->size - 1 ) { // se estiver na ultima coluna e nao na primeira linha
                current->principal_diagonal = 0;
                current->secondary_diagonal = 0;
                current->num = 0;
                current->numero_possiblidades=0;
                current->li_box = line -(line % n);
                current->ci_box = col - (col % n);
                current->lf_box = current->li_box + (n-1);
                current->cf_box = current->ci_box + (n-1);
                current->linha= line;
                current->coluna = col;
                current->n = prevCol->ne;
                current->ne = NULL;
                current->e = NULL;
                current->se = NULL;
                current->s = prevCol->se;
                current->so = prevCol->s;
                current->o = prevCol;
                current->no = prevCol->n;
            }
            if (line == tab->size - 1 && col == 0) { // se estiver na ultima linha e na primeira coluna
                current->principal_diagonal = 0;
                current->secondary_diagonal = 1;
                current->num = 0;
                current->numero_possiblidades=0;
                current->li_box = line -(line % n);
                current->ci_box = col - (col % n);
                current->lf_box = current->li_box + (n-1);
                current->cf_box = current->ci_box + (n-1);
                current->linha= line;
                current->coluna = col;
                current->n = prevLine;
                current->ne = prevLine->e;
                current->e = prevLine->se;
                current->se = NULL;
                current->s = NULL;
                current->so = NULL;
                current->o = NULL;
                current->no = NULL;
            }
            if (line == tab->size - 1 && col != 0 && col != tab->size - 1) { // se estiver na ultima linha mas nao na primeira nem ultima coluna
                current->principal_diagonal = 0;
                current->secondary_diagonal = 0;
                current->num = 0;
                current->numero_possiblidades=0;
                current->li_box = line -(line % n);
                current->ci_box = col - (col % n);
                current->lf_box = current->li_box + (n-1);
                current->cf_box = current->ci_box + (n-1);
                current->linha= line;
                current->coluna = col;
                current->n = prevCol->ne;
                current->ne = prevCol->ne->e;
                current->e = prevCol->ne->se;
                current->se = NULL;
                current->s = NULL;
                current->so = NULL;
                current->o = prevCol;
                current->no = prevCol->n;
            }
            if (line == tab->size - 1 && col != 0 && col == tab->size - 1) { // se estiver na ultima linha na ultima coluna
                current->principal_diagonal = 1;
                current->secondary_diagonal = 0;
                current->num = 0;
                current->numero_possiblidades=0;
                current->li_box = line -(line % n);
                current->ci_box = col - (col % n);
                current->lf_box = current->li_box + (n-1);
                current->cf_box = current->ci_box + (n-1);
                current->linha= line;
                current->coluna = col;
                current->n = prevCol->ne;
                current->ne = NULL;
                current->e = NULL;
                current->se = NULL;
                current->s = NULL;
                current->so = NULL;
                current->o = prevCol;
                current->no = prevCol->n;
            }
            prevCol = current; //atualiza a coluna anterior
            current = current->e; // atualiza o current
        }
        if (line >= 1) {   // se estiver em qualquer linha que nao a primeira
            prevLine = prevLine->s;   // atualiza o apontador da linha anterior
        }

        current = prevLine->s;  // atualiza o current
    }

}


void read_tabuleiro_from_txt(TABULEIRO *tab,FILE *fp, int size) {

    if (fp != NULL) {
        int **tabuleiro = read_tabuleiro(fp,size);
        fill_tabuleiro(&tab,tabuleiro);
    }
}


void fill_tabuleiro(TABULEIRO **tab, int **tabuleiro){

    CEL *current, *pline;
    pline = (*tab)->pfirst;
    current = (*tab)->pfirst;
    for (int line = 0; line < (*tab)->size; ++line) {
        for (int col = 0; col < (*tab)->size; ++col) {
            current->num = *(*(tabuleiro+line)+col);
            current = current->e;
        }
        printf("\n");
        pline = pline->s;
        current = pline;
    }

}


void put_current_cel_in_place(CEL **current, int linha, int coluna){

    CEL *cel = *current;

    while(cel->linha != linha){
        if(linha > cel->linha){
            cel = cel->s;
        } else{
            cel = cel->n;
        }
    }
    while(cel->coluna != coluna){
        if(coluna > cel->coluna){
            cel = cel->e;
        }else {
            cel = cel->o;
        }
    }

    *current = cel;

}




void init_linked_tabuleiro_random(int clues, TABULEIRO *tab){

    CEL *current = tab->pfirst;

    //array de size*size posicoes random a colocar no tabuleiro
    int *posicao = generate_positions_in_board(tab->size*tab->size);

    int smallest = 5000;
    int plinha=0, pcoluna =0, valor =0;
    printf("dihbdie");

    for (int i = 0; i < clues ; i++) {
        for (int n = 0; n < tab->size * tab->size; n++) {


            int coluna = get_coluna_from_posicao(posicao[n], tab->size);
            int linha = get_linha_from_posicao(posicao[n], tab->size, coluna);

            put_current_cel_in_place(&current,linha,coluna);
            int number;

            //testa se a box onde esta a tentar colocar o numero nao se encontra com apenas um elemento por preencher, evitando boxs completas
            if (box_if_almost_full_2(tab,current,clues)==0 && line_is_almost_full_2(tab,current)==0 && column_is_almost_full_2(tab,current)==0) {
                int n_candidates = n_candidates_in_cel(tab, current, &number);

                if (n_candidates > 0 && n_candidates < smallest) {
                    smallest = n_candidates;
                    plinha = linha;
                    pcoluna = coluna;
                    valor = number;
                }
            }

        }
        put_current_cel_in_place(&current,plinha,pcoluna);
        printf ("coloca o numero %d em [%d,%d]\n",valor,current->linha,current->coluna);
        current->num = valor;
        smallest = 5000,  plinha=0, pcoluna =0, valor =0;
    }
}


//retorna o numero de camdidatos para a respetiva celula
int n_candidates_in_cel(TABULEIRO *tab,CEL *current,int * valor)
{
    int *numbers_possible = generate_positions_in_board(tab->size);

    int allowed =0;

    for (int i = 0; i < tab->size ; i++)
    {

        if (check_if_num_possible(current,tab, *(numbers_possible+i)) == 1)
        {
            if(allowed == 0) *valor = *(numbers_possible+i);
            allowed++;
        }
    }
    return  allowed;

}




int box_if_almost_full_2(TABULEIRO *tab, CEL *cel ,int clues) {
    int size = tab->size;
    int number_of_values = 0;
    int almost_full = 0;
    CEL *current, *pline;
    current = cel;


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


    put_current_cel_in_place(&current,current->li_box,current->ci_box);
    pline = current;

    for (int i = current->li_box; i <= current->lf_box; i++) {
        for (int j = current->ci_box; j <= current->cf_box; j++) {

            if (current->num == 0) {
                number_of_values++;
            }
            current = current->e;
        }
        pline = pline->s;
        current = pline;
    }
    if (number_of_values == almost_full) return 1;
    else return 0;

}


int line_is_almost_full_2(TABULEIRO *tab, CEL *cel){
    CEL * current = cel;
    int almost_full=1;
    int number_of_values=0;
    put_current_cel_in_place(&current,current->linha,0);
    for (int i = 0; i < tab->size ; i++) {
        if(current->num == 0){
            number_of_values++;
        }
        current = current->e;
    }
    if(number_of_values == 1) return 1;
    else return 0;

}

int column_is_almost_full_2(TABULEIRO *tab, CEL *cel){
    CEL * current = cel;
    int almost_full=1;
    int number_of_values=0;
    put_current_cel_in_place(&current,0,current->coluna);
    for (int i = 0; i < tab->size ; i++) {
        if(current->num == 0){
            number_of_values++;
        }
        current = current->s;
    }
    if(number_of_values == almost_full) return 1;
    else return 0;
}



void print_tab(TABULEIRO *tab){

    if(tab != NULL) {
        printf("TABULEIRO:\n");
        CEL *current, *pline;
        pline = tab->pfirst;
        current = tab->pfirst;
        for (int line = 0; line < tab->size; ++line) {
            for (int col = 0; col < tab->size; ++col) {
                printf("%d  ", current->num);
                current = current->e;
                if(col==2 || col== 5 || col == 8)printf(" ");
            }
            if(line==2 || line== 5 || line == 8)printf("\n");
            printf("\n");
            pline = pline->s;
            current = pline;
        }
    }else {
        printf("TABULEIRO VAZIO !\n");
    }
}


