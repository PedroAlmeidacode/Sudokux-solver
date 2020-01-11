//
// Created by pedro on 28/11/19.
//

#include <bits/types/clock_t.h>
#include <time.h>
#include "library.h"

void compare_two_functions_time(){

    clock_t time;
    time = clock();
    //chamada a funcao
    time = clock() - time;
    double time_taken_func1 = ((double)time)/CLOCKS_PER_SEC; // in seconds

    clock_t t;
    t = clock();
    //chmada a funcao
    t = clock() - t;
    double time_taken_func2 = ((double)t)/CLOCKS_PER_SEC; // in seconds


    if(time_taken_func1 < time_taken_func2) printf("A funcao 1 (%f segundos) foi mais rapida que a funcao 2 (%f segundos) \n",time_taken_func1,time_taken_func2);
    else  printf("A funcao 2 (%f segundos) foi mais rapida que a funcao 1 (%f segundos) \n",time_taken_func2,time_taken_func1);

}
