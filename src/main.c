#include <stdio.h>
#include <time.h>

int main()
{
    clock_t start_time, end_time;
    double time_spent;

    long long int num_iterations = 10000;
    double x = 1.5;

    int counting = 0;
    while (counting <= 100){
        counting++;
        printf("FINDME\n");
    }

    start_time = clock();

    // Calculate the floating point operations
    for(long long int i = 0; i < num_iterations; i++){
        x = x * 1.000001;
        x = x / 1.000001;
    }

    end_time = clock();

    time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("TIME: %f\n", time_spent);

    return 0;
}