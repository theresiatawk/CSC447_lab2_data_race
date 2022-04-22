#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *array;
int length;

int main()
{
    int i;
    length = 10000;
    int count = 0;
    array = calloc(length, sizeof(int));
    
    /* initialize the array with random integers between 0 and 9 */
    srand(time(NULL));  /* seed the random number generator with current time */
    
    /* start the time of execution */ 
    clock_t time_start = clock();
    for (i = 0; i < length; i++)
    {
        array[i] = rand() % 10;
    }
    for (i = 0; i < length; i++)
    {
        if (array[i] == 3)
        {
            count++;
        }
    }
    clock_t time_end = clock();
    
    /*Caculating the time it takes for execution*/
    
    double time_spent = ((double)(time_end - time_start) / CLOCKS_PER_SEC) * 1000.0;
    printf("There are %d 3s in the array and the running time is:  %fms", count, time_spent);
    return 0;
}