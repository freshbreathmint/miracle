#include <stdio.h>
#include "library.h"

int main()
{
    while(1){
        int flops = measure_flops();
        printf("FLOPS: %i\n", flops);
    }

    return 0;
}