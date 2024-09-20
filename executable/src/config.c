#include "config.h"

#include <stdio.h>

int parse_config(const char *filename){
    FILE *file = fopen(filename, "r");
    if(!file){
        printf("Can't open '%s'\n", filename);
        return 0;
    }


}