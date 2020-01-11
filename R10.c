//
// Created by pedro on 26/12/19.
//

#include "library.h"

//permitir guardar os tabuleiros previamente guardados

int add_node_to_fila(FILA *fila, TABULEIRO *tab) {
    //nao existe tabuleiro no apontador tabuleiro ( item = NULL)
    if ((fila == NULL) || (tab == NULL)) {
        return 0;
    }

    //a queue esta vazia
    tab->prev = NULL;
    if (fila->size == 0) {
        fila->head = tab;
        fila->tail = tab;

    } else {
        // adicionar tabuleiro ao fim da queue
        fila->tail->prev = tab;
        fila->tail = tab;
    }
    fila->size++;
    return 1;
}

FILA *construir_fila() {
    FILA *queue = (FILA*) malloc(sizeof (FILA));
    if (queue == NULL) {
        return NULL;
    }

    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}



