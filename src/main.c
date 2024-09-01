#include <stdbool.h>
#include <stdio.h>

bool running = false;

int main()
{
    running = true;

    // Main Loop
    int cycle = 0;
    while(running){
        cycle++;
        printf("Cycle: %i\n", cycle);
        if(cycle == 100000){
            running = false;
        }
    }

    // Exit
    return 0;
}