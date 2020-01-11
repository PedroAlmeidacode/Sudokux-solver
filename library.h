#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#ifndef PROJETOFINALAEDLP_LIBRARY_H
#define PROJETOFINALAEDLP_LIBRARY_H


// UNASSIGNED is used for empty cells in sudoku grid
#define UNASSIGNED 0

// N is used for the size of Sudoku grid. Size will be NxN
#define N 9

//maximo de arrays possiveis tirar de fichrio para guardar em memoria local (***memoria)
#define MAX_ARRAYS 10


//struct das letras da sopa apontador de norte no sentido dos ponteiros
typedef struct cel {
    int li_box; // linha inicial da caixa em que se encontra
    int ci_box; // coluna inicial da caixa em que se encontra
    int lf_box;// linha final da caixa em que se encontra
    int cf_box;// coluna final da caixa em que se encontra
    int principal_diagonal; // se a celula se encontar na diagonal principal 1 senao 0
    int secondary_diagonal; // se a celula se encontar na diagonal secundaria 1 senao 0
    int num;
    int *possibilidades;//possibilidades de numeros na celula
    int numero_possiblidades;
    int linha,coluna; //linha e coluna em que  a celula se encontra
    struct cel *n;
    struct cel *ne;
    struct cel *e;
    struct cel *se;
    struct cel *s;
    struct cel *so;
    struct cel *o;
    struct cel *no;
} CEL;

//struct do tabuleiro com apontador para a primeira celula, levando apartir dessa a todas as outras
typedef struct tabuleiro {
    int size;
    CEL *pfirst;
    struct tabuleiro *prev;
} TABULEIRO;

typedef struct linkedlist{
    TABULEIRO * head;
    TABULEIRO * tail;
    TABULEIRO * current;
    int size;
}FILA;



/**R13 funcoes*/

int * delete_num_from_possiblidades(CEL ** pCel, int posicao );
bool naked_pairs(TABULEIRO **t);
bool repeated_candidate_in_box(CEL *cel, int number);
bool single_candidate_in_box_for_cel(TABULEIRO **t);
bool single_candidate_in_cel(TABULEIRO **t);
CEL* find_second_pair(TABULEIRO * tab, CEL * first_pair);
void delete_same_in_other_cels_of_box(TABULEIRO **t, CEL *first_pair, CEL *second_pair);
void delete_same_in_other_cels_of_principal_diagonal(TABULEIRO **t, CEL *first_pair, CEL *second_pair);
void delete_same_in_other_cels_of_secondary_diagonal(TABULEIRO **t, CEL *first_pair, CEL *second_pair);
void delete_same_in_other_cels_of_line(TABULEIRO **t, CEL *first_pair, CEL *second_pair);
void delete_same_in_other_cels_of_col(TABULEIRO **t, CEL *first_pair, CEL *second_pair);

/**R12 funcoes*/

bool Solve_brute_force(TABULEIRO *tab, CEL *current);
bool is_complete(TABULEIRO *tab, CEL **pCel);
void find_mask_2(TABULEIRO *tab);
void print_mask_2(TABULEIRO *tab);
int check_if_num_possible(CEL *cel, TABULEIRO *tab, int num);
int no_repeated_num_in_line(CEL *ref, TABULEIRO *tab, int num);
int no_repeated_num_in_column(CEL *ref, TABULEIRO *tab, int num);
int no_repeated_num_in_box(CEL *ref,  int num);
int no_repeated_num_in_principal_diagonal(CEL *ref, TABULEIRO *tab, int num);
int no_repeated_num_in_secondary_diagonal(CEL *ref, TABULEIRO *tab, int num);

/** R10 funoces*/
FILA *construir_fila();//inicializa a estrutura
int add_node_to_fila(FILA *fila, TABULEIRO *tab);//adiciiona um novo tabuleiro a fila

/** R9 funoces*/
int box_if_almost_full_2(TABULEIRO *tab, CEL *cel ,int clues);
int line_is_almost_full_2(TABULEIRO *tab, CEL *cel);
int column_is_almost_full_2(TABULEIRO *tab, CEL *cel);
int n_candidates_in_cel(TABULEIRO *tab,CEL *current,int * valor);
void  put_current_cel_in_place(CEL **current, int linha, int coluna);
void teste_R9(char string[]);
void init_linked_tabuleiro(int size,  TABULEIRO *tab);
void fill_tabuleiro(TABULEIRO **tab, int **tabuleiro);
void read_tabuleiro_from_txt(TABULEIRO *tab,FILE *fp, int size);
void print_tab(TABULEIRO *tab);
void read_all_tabuleiros_from_txt_print_test( char string[]);
void init_linked_tabuleiro_random(int clues, TABULEIRO *tab);

/** R8 funcoes*/
/***
 *
 * @param string path para solutions.txt
 * @param solution tabuleiro a guardar
 * @param size tamanho do tabuleiro
 */
void save_solution(char string[], int ** solution, int size);
/***
 *
 * @param string path para solutions.txt
 * @param solution tabuleiro a guardar
 * @param size tamanho do tabuleiro
 */
void save_solution_bin(char string[], int **solution, int size);

/***
 * retorna o tamanho da caixa de acordo com o tamanho do tabuleiro
 * ou seja se o tabuleiro for de size 9 o tamanho da caixa é de 3
 * @param size tamanho do tabuleiro
 * @return retorna o tamanho da caixa
 */
int return_box_size(int size);

// This function finds an entry in grid that is still unassigned
bool FindUnassignedLocation(int **grid, int *row, int *col,int size);


bool SolveSudoku(int **grid, int size);

/***
 * resolve um tabuleiro usando as 3 regras especificadas
 * @param tabuleiro
 * @param size tamanho do tabuleiro
 * @return retorna 1 se o tabuleiro estiver resolvido ou 0 se nao for possivel resolver
 */
int  my_solver(int **tabuleiro, int size);
/***
 * faz a exaustao da regra, ou seja atualiza e implementa a regra ate nao conseguir mais
 * @param tabuleiro
 * @param mask guarda os candidatos de cada celula usando um array 3d
 * @param size tamanho do tabuleiro
 * @param alterou usado para saber se a regra foi implementada , para a que chamar a funcao saber
 */
void exaustion_pairs(int **tabuleiro, int mask[N][N][N], int size,int * alterou);
/***
 * faz a exaustao da regra, ou seja atualiza e implementa a regra ate nao conseguir mais
 * @param tabuleiro
 * @param mask guarda os candidatos de cada celula usando um array 3d
 * @param size tamanho do tabuleiro
 */
void exaustion_of_number_alone_rule(int **tabuleiro,int mask[N][N][N],int size);
/***
 * faz a exaustao da regra, ou seja atualiza e implementa a regra ate nao conseguir mais
 * @param tabuleiro
 * @param mask guarda os candidatos de cada celula usando um array 3d
 * @param size tamanho do tabuleiro
 * @param alterou usado para saber se a regra foi implementada , para a que chamar a funcao saber
 */
void exaustion_of_number_oculto_rule(int **tabuleiro,int mask[N][N][N],int size, int * alterou);
/***
 * verifica o tabuleiro se encontra preenchido
 * @param matrix tabuleiro
 * @param size tamanho do tabuleiro
 * @return 1 se estiver preenchido , ou seja nao tem nenhum zero
 */
int checkgrid(int **matrix, int size);



/*** funcoes usadas para atualizar a mascara   */
/***
 * atualiza a mascara igualando a zero e pesquisando os candidatos para cada celula a 0
 * @param mask
 * @param tabuleiro
 * @param size tamanho do tabuleiro
 */
void find_mask(int mask[N][N][N], int **tabuleiro, int size);
/***
 * iguala todos os candidatos a 0
 * @param mask
 * @param size
 */
void put_mask_to_zero(int  mask[N][N][N],int size);

/***funcao de imrpimir a mascara */
void print_mask(int size, int mask[N][N][N]);




/*** funcoes usadas para a regra do numero alone  */
/***
 * coloca um numero no tabuleiro se esse numero for o unico candidato dessa celula
 * @param tabuleiro
 * @param mask
 * @param size
 * @return retorna 1 se colocou algum numero no tabuleiro
 */
int puts_number_alone_in_tabuleiro(int **tabuleiro, int mask[N][N][N], int size);


/*** funcoes usadas para a regra do numero oculto alone  */
/***
 * coloca o numero na celula do tabuleiro se esse numero ou for o unico na linha ou na coluna ou
 * na caixa, ou na diagonal principal, ou nao secundaria
 * @param tabuleiro
 * @param mask
 * @param size
 * @return
 */
int puts_number_oculto_alone_in_box(int **tabuleiro , int mask[N][N][N], int size);
/***
 * de acordo com a tecnica de por um numero que estaja sozinho na caixa
 * tem de se verificar se nao existe esse candidato em outras celulas da caixa
 * @param mask mascara
 * @param li linha inicial da caixa
 * @param lf linha final da caixa
 * @param ci coluna inicial da caixa
 * @param cf coluna final da caixa
 * @param number numero que se pretende por e que nao podera existir nos candidatos das outras celulas
 * @param size tamanho do tabuleiro
 * @return retorna 1 se nao estiver esse numero nos candidatos do resto da caixa
 */
int not_repeated_in_box_of_mask(int mask[N][N][N],int li,int lf ,int ci ,int cf ,int number ,int size );







/*** funcoes usadas para a regra dos pares */
/***
 * resolucao da regra dos pares
 * @param tabuleiro
 * @param mask
 * @param size
 * @return
 */
int naked_pairs_solver(int **tabuleiro, int mask[N][N][N], int size);
/***
 * coloca a 0 (apaga) da mask os candidatros de outra celulas iguais ao par da caixa
 * @param mask mascara
 * @param linha_first_pair linha da primeira celula com o par
 * @param coluna_first_pair coluna da primeira celula com o par
 * @param linha_second_pair linha da segunda celula com o par
 * @param coluna_second_pair coluna da segunda celula com o par
 * @param size tamanho do tabuleiro
 * @param pair array com os dois numeros candidatos encontrados no primeiro par
 */
void delete_candidates_pair_numbers_from_box_of_mask(int mask[N][N][N], int linha_first_pair, int coluna_first_pair,
                                                     int linha_second_pair, int coluna_second_pair, int size,
                                                     const int pair[2]);
/***
 * coloca a 0 (apaga) da mask os candidatros de outra celulas iguais ao par da coluna
 * @param mask mascara
 * @param coluna coluna em que as duas celulas se encontam
 * @param size tamanho do tabuleiro
 * @param linha_first_pair coluna da primeira celula com o par
 * @param linha_second_pair linha da segunda celula com o par
 * @param pair array com os dois numeros candidatos encontrados no primeiro par
 */
void delete_mask_pair_numbers_from_col(int mask[N][N][N],int coluna,int size, int linha_first_pair, int linha_second_pair, const int pair[2]);
/****
 * coloca a 0 (apaga) da mask os candidatros de outra celulas iguais ao par da linha
 * @param mask mascara
 * @param linha linha em que as duas celulas se encontam
 * @param size tamanho do tabuleiro
 * @param coluna_first_pair coluna da primeira celula com o par
 * @param coluna_second_pair coluna da segunda celula com o par
 * @param pair array com os dois numeros candidatos encontrados no primeiro par
 */
void delete_mask_pair_numbers_from_line(int mask[N][N][N],int linha,int size, int coluna_first_pair, int coluna_second_pair, const int pair[2]);
/****
 * testa se as duas celulas se ecnontram na mesma caixa
 * @param i limnha da priemira celula
 * @param j coluna da primeira celula
 * @param linha_second_pair linha da segunda celula
 * @param col_second_pair coluna da segunda celula
 * @param size tamanho do tabuleiro
 * @return retorna 1 se estiverem na mesma caixa
 */
int two_pairs_in_the_same_box(int i, int j, int linha_second_pair, int col_second_pair, int size);
/******
 * encontra uma segunda celula com os mesmo par e a apenas com o par de numeros da primeira celula
 * @param first_pair array com os dois numeros camdidatos
 * @param linha linha da primeira celula encontrada
 * @param col coluna da primeira celula encontrada
 * @param linha_second_pair linha a guardar se se encontrar uma segunda celula com o par de numeros
 * @param col_second_pair coluna a guardar se se encontrar uma segunda celula com o par de numeros
 * @param mask mascara
 * @param size tamanho do tabueleiro
 * @return retorna 1 se encontar
 */
int find_second_naked_pair(const int first_pair[2], int linha, int col, int *linha_second_pair, int *col_second_pair,
                           int mask[N][N][N], int size);
/****
 *
 * @param mask mascara
 * @param linha_first_pair linha da primeira celula com o par
 * @param coluna_first_pair coluna da primeira celula com o par
 * @param linha_second_pair linha da segunda celula com o par
 * @param coluna_second_pair linha da segunda celula com o par
 * @param size tamanho do tabuelro
 * @param pair array com o par de numeros
 */
void delete_mask_pair_numbers_from_principal_diagonal(int mask[N][N][N], int linha_first_pair, int coluna_first_pair,int linha_second_pair, int coluna_second_pair, int size,
                                                      const int pair[2]);
/******
 *
 * @param mask mascara
 * @param linha_first_pair linha da primeira celula com o par
 * @param coluna_first_pair coluna da primeira celula com o par
 * @param linha_second_pair linha da segunda celula com o par
 * @param coluna_second_pair coluna da segunda celula com o par
 * @param size tamanho do tabuleiro
 * @param pair array com o par de numeros
 */
void delete_mask_pair_numbers_from_secondary_diagonal(int mask[N][N][N], int linha_first_pair, int coluna_first_pair,int linha_second_pair, int coluna_second_pair, int size,
                                                      const int pair[2]);










void printGrid(int grid[N][N]);

int checkconsistency(int **tabuleiro, int size, int linha, int coluna , int number );
/**Funcoes usadas em recurso da checkconsistency para checkar se o numero a colocar na celula é perimitido de acordo com as regras */
int no_repeated_number_in_line(int **tabuleiro, int size,int linha, int valor);
int no_repeated_number_in_column(int **tabuleiro, int size,int coluna, int valor);
int no_repeated_number_in_box(int **tabuleiro, int size, int linha, int coluna, int valor);
int no_repeated_number_in_principal_diagonal(int **tabuleiro,int size, int linha, int coluna , int valor);
int no_repeated_number_in_secondary_diagonal(int **tabuleiro ,int size, int linha, int coluna , int valor);











void teste_R1_b_R2(char string[]);




void teste_R1_a(int size);
/**
 * o objetivo desta funcao é criar aleatoriamente n posicoes(clues) de acordo com o total
 * de posicoes que tem ao seu dispor
 * estas posicoes vao ser posteriormente convertidas para a respetiva linha e coluna
 * estas posicoes vao originar a criacao de um numero aleatorio nessa celula
 * criando entao um tabuleiro inicial completamente aleatorio
 *
 * @param range - size*size , numero de elementos total dentro de um tabuleiro por exemplo um tabuleiro de size 9*9 tem 81 elementos
 * @return retorna um apontador que contem as posicoes geradas
 */
int *generate_positions_in_board(int range);

/**
 *
 * @param posicao - posicao do tabuleiro por exemplo num tabuleiro 9*9 existem 81 posicoes , a posicao 76 corresponde a linha 8 e coluna 3
 * @param size - (numero de linhas ou numero de colunas comecando no 1)
 * @return retorna linha em que a posicao se encontra de 0 - (size-1)
 */
int get_coluna_from_posicao(int posicao, int size);

/**
 * para averiguar a linha em que a posicao se encontra foi criada uma formula que necessita da posicao size e coluna
 * @param posicao  -  posicao do tabuleiro por exemplo num tabuleiro 9*9 existem 81 posicoes , a posicao 76 corresponde a linha 8 e coluna 3
 * @param size  - (numero de linhas ou numero de colunas comecando no 1)
 * @param coluna - coluna em que esta posicao se encontra
 * @return
 */
int get_linha_from_posicao(int posicao, int size, int coluna);



/**
 *
 * @param clues - numero de elemntos que se deseja inicializar o tabuleiro (vai influenciar a dificuldade de resolucao do tabuleiro)
 * @param size - (numero de linhas ou numero de colunas comecando no 1)
 * @return - retorna um array dinamico de um tabuleiro com x clues criado aleatoriamente
 */
int** init_tabuleiro_random(int clues, int size);
/** Funcoes usadas em recurso de criar um tabuleiro random*/
/**
 * Esta funcao cria um tabuleiro (matriz/ array bidimensional) , aloca espaco para ele de acordo com o size, e inicializa todas as posicoes do tabuleiro a 0
 * @param size - (numero de linhas ou numero de colunas comecando no 1)
 * @return - retorna o tabuleiro com todas as posicoes inicializadas a 0
 */
int** create_dyn_tabuleiro(int size);
int box_if_almost_full(int **tabuleiro, int size, int linha, int coluna, int clues);
int column_is_almost_full(int **tabuleiro, int size,int coluna);
int line_is_almost_full(int **tabuleiro, int size,int coluna);
int number_of_numbers_allowed_in_this_position(int **tabuleiro,int linha, int coluna, int size,int * valor);







void print_tabuleiro(int **tabuleiro, int n);




/** funcoes usadas para ler varios tabuleiros do txt*/
int ***read_tabuleiros_from_txt_and_load_memory(int * tamanho, char string[]);
/**
 * nesta funcao passa se no primeiro parametro o apontador para o ficheiro a ser lido e na segunda passa se o tamanho do ficheiro a ler que devera ser
 * lido do ficheiro prosteriormente visto que se encontra no cabecalho do tabuleiro
 * a funcao basicamente chama a funcao create_dyn_tabuleiro(size) que aloca e cria um tabuleiro tudo a 0
 * de seguida transfere todos os inteiros do ficheiro "/home/pedro/Desktop/ProjetoFinalAEDLP/tabuleiros.txt"
 * para cada respetiva posicao do tabueleiro
 *
 *
 * @param handler apontador para o ficheiro
 * @param size - (numero de linhas ou numero de colunas comecando no 1)
 * @return . retorna um array dinamico que contem o tabueliro vsualizado no ficheiro
 */
int **read_tabuleiro(FILE *handler, int size);




#endif //PROJETOFINALAEDLP_LIBRARY_H
