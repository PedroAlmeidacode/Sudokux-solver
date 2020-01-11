//
// Created by pedro on 28/11/19.
//

#include "library.h"

void save_solution(char string[], int ** solution, int size){

    FILE *handler = fopen(string, "a");// append pois assim coloca sempre na ultima posicao
    if(handler==NULL) {
        perror("Error opening file.");}
    fprintf(handler,"%d\n",size);
    for (int i = 0; i < size ; i++) {
        for (int j = 0; j < size ; j++) {
            fprintf(handler,"%d ",solution[i][j]);

        }
        fprintf(handler,"\n");

    }

    fclose(handler);

}

void save_solution_bin(char string[], int **solution, int size){


    FILE *handler = fopen(string, "ab");// append pois assim coloca sempre na ultima posicao
    if(handler==NULL) {
        perror("Error opening file.");}
    fprintf(handler,"%d\n",size);
    fwrite(solution,sizeof(int),size*size,handler); // write 10 bytes from our buffer


    fclose(handler);


}