#include "engine.h"
#include "libapi.h"

#include <stdio.h>

void funcA(){
    printf("Engine says hello!\n");
}

void funcB(){
    printf("Engine says hello!\n");
}

void check_address(){
    printf("Address of funcA: %p\n", (void*)funcA);
}