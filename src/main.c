#include <stdio.h>
#include <time.h>

int main()
{
    clock_t start_time_print, end_time_print, start_time_floats, end_time_floats;
    double time_spent;

    long long int num_floats = 1000000000;
    long long int num_prints = 10000;
    double x = 1.5;

    start_time_print = clock();

    int counting = 0;
    while (counting < num_prints){
        counting++;
        printf("%i\n", counting);
    }

    end_time_print = clock();

    time_spent = (double)(end_time_print - start_time_print) / CLOCKS_PER_SEC;
    printf("PRINTS TIME: %f\n", time_spent);

    start_time_floats = clock();

    // Calculate the floating point operations
    for(long long int i = 0; i < num_floats; i++){
        x = x * 1.000001;
        x = x / 1.000001;
    }

    end_time_floats = clock();

    time_spent = (double)(end_time_floats - start_time_floats) / CLOCKS_PER_SEC;
    printf("FLOATS TIME: %f\n", time_spent);

    return 0;
}