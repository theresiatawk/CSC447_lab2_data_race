#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MaxThreads 1000

void* count3s_thread(void* id);
pthread_t tid[MaxThreads];

int t; /* number of threads */
int* array;
int length;
int count;

void count3s()
{
    int i;
    count = 0;
    /* Create t threads */
    for (i = 0; i < t; i++)
    {
        pthread_create(&tid[i], NULL, count3s_thread, (void*)i);
    }

    /*** wait for the threads to finish ***/
    for (i = 0; i < t; i++)
    {
        pthread_join(tid[i], NULL);
    }
}

void* count3s_thread(void* id)
{
    int i;
    /* Compute portion of the array that this thread should work on */
    int length_per_thread = length / t;
    int start = (int)id * length_per_thread;

    for (i = start; i < start + length_per_thread; i++)
    {
        if (array[i] == 3)
        {
            count += 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int i;
    length = 1048576; /*  2^20  */
    t = 64; /*** be sure that t divides length!! ***/

    array = calloc(length, sizeof(int));

    /* initialize the array with random integers between 0 and 9 */
    srand(time(NULL));  /* seed the random number generator with current time */
    for (i = 0; i < length; i++)
    {
        array[i] = rand() % 10;
    }

    clock_t time_start = clock(); /* run the threads, wait till they finish */
    count3s();
    clock_t time_end = clock();

    double time_spent = ((double)(time_end - time_start) / CLOCKS_PER_SEC) * 1000.0;
    printf("The execution time of parallel code is: %fms\n", time_spent);
    printf("The number of 3's when executing in parallel is %d\n", count);


    clock_t time_startt = clock();
    count = 0;
    for (i = 0; i < length; i++)
        if (array[i] == 3)
            count++;
    clock_t time_endd = clock();

    double time_spentt = ((double)(time_endd - time_startt) / CLOCKS_PER_SEC) * 1000.0;
    printf("The execution time of serial code is: %fms\n", time_spentt);
    printf("The number of 3's when executing serially is %d\n", count);

    return 0;
}