#include "library.h"

#include "library.h"


int main() {
    //teste_R9("/home/pedro/Desktop/ProjetoFinalAEDLP/tabuleiros.txt");
    FILE *fp = fopen("/home/pedro/Desktop/ProjetoFinalAEDLP/tabuleiros.txt", "r");
    //retira do ficheiro o numero de tabuleiros que existem no ficheiro
    int numero_tabuleiros;
    fscanf(fp,"%d",&numero_tabuleiros);

    int size_tabuleiro;
    fscanf(fp, "%d", &size_tabuleiro);


    TABULEIRO tab ={size_tabuleiro, NULL, NULL};
    init_linked_tabuleiro(&tab);
    //init_linked_tabuleiro_random(100,&tab);
    read_tabuleiro_from_txt(&tab,fp,size_tabuleiro);

    print_tab(&tab);
    find_mask_2(&tab);
    print_mask_2(&tab);
    if(single_candidate_in_cel(&tab)== true){
        print_tab(&tab);
        find_mask_2(&tab);
        print_mask_2(&tab);

    }
    //if(Solve_brute_force(&tab,tab.pfirst)== 1)print_tab(&tab);
    //else printf("tabuleiro nao tem solução !");
    //find_mask_2(&tab);
    //print_mask_2(&tab);
    fclose(fp);
    return 0;
}




void teste_R9(char string[]){
    FILE *fp = fopen(string, "r");
    //retira do ficheiro o numero de tabuleiros que existem no ficheiro
    int numero_tabuleiros;
    fscanf(fp,"%d",&numero_tabuleiros);

    int size_tabuleiro;
    fscanf(fp, "%d", &size_tabuleiro);

    TABULEIRO tab ={size_tabuleiro, NULL, NULL};
    init_linked_tabuleiro(&tab);
    print_tab(&tab);

    read_tabuleiro_from_txt(&tab,fp,size_tabuleiro);
    print_tab(&tab);
    fclose(fp);
}


void teste_R1_a(int size){
    int **tabuleiro = init_tabuleiro_random(40,size);
    print_tabuleiro(tabuleiro,size);

}

void teste_R1_b_R2(char string[]){
    int i=0;
    int *tamanho=malloc(MAX_ARRAYS * sizeof(int));
    int ***memoria = read_tabuleiros_from_txt_and_load_memory(tamanho,string);
    while(*(tamanho+i)!= '\0'){
        print_tabuleiro(*(memoria+i),*(tamanho+i));
        i++;
    }


}


void teste_R3(int ** tabuleiro, int size){
    if(checkgrid(tabuleiro,size)) printf ("tabuleiro compleatemnete preenchido");
    else printf("tabuleiro nao completamente preenchido ");

}

void teste_R4_a(int ** tabuleiro,int size){
    if(SolveSudoku(tabuleiro,size)== 1)print_tabuleiro(tabuleiro,size);
    else printf("tabuleiro nao tem solução !");

}

void teste_R4_b(int ** tabuleiro,int size){
    if(my_solver(tabuleiro,size)== 1)print_tabuleiro(tabuleiro,size);
    else printf("tabuleiro nao tem solução !");

}


void printGrid(int grid[N][N]){
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            printf("%2d", grid[row][col]);
        printf("\n");
    }
}



