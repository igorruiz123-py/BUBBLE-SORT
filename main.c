#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 700000
#define MIN 0
#define MAX 700000
#define TIME_BUFFER_LEN 64
#define UNSORTED_FILE_NAME "random-numbers.txt"
#define SORTED_FILE_NAME "sorted-numbers.txt"

void loadingbar(int current, int total){

    int percent = (current  * 100) / total;

    int width = 30;

    printf("\r[");

    for (int i = 0; i < width; i++){
        if (i < percent * width / 100){
            printf("#");
        }
        else {
            printf(" ");
        }
    }

    printf("] %d%%", percent);
    fflush(stdout);
}

void printtime(time_t t, char *buffer, size_t size){

    struct tm *tme = localtime(&t);

    strftime(buffer, size, "%d/%m/%Y - %H:%M:%S", tme);
}

int checkfile(FILE *file){

    if (file == NULL){
        perror("fopen");
        exit (EXIT_FAILURE);
    }

    return 1;
}

void mkfile(void){

    FILE *file;

    file = fopen(UNSORTED_FILE_NAME, "w");

    checkfile(file);

    printf("\nInserting random numbers into the file...\n");

    for (int i = 0; i < N; i++){
        fprintf(file, "%d \n", rand() % (MAX - MIN + 1) + MIN);
    }

    printf("\nRandom numbers inserted into the file!\n");

    fclose(file);
}

void sortfile(void){

    FILE *unsortedfile;

    FILE *sortedfile;

    int *buffer = malloc(N * sizeof(int));

    int i = 0;

    unsortedfile = fopen(UNSORTED_FILE_NAME, "r");

    checkfile(unsortedfile);

    while(fscanf(unsortedfile, "%d", &buffer[i]) == 1){
        i++;
    }

    fclose(unsortedfile);

    printf("\nSorting numbers...\n");

    for (int j = 0; j < N; j++){
        for (int k = 0; k < N - 1 - j; k++){
            if (buffer[k] > buffer[k + 1]){
                int temp = buffer[k];
                buffer[k] = buffer[k + 1];
                buffer[k + 1] = temp;
            }
        }

        if (j % (N / 100) == 0){
            loadingbar(j , N);
        }
    }

    printf("\nNumbers sorted!\n");

    sortedfile = fopen(SORTED_FILE_NAME, "w");

    checkfile(sortedfile);

    printf("\nInserting sorted numbers into file...\n");

    for (int l = 0; l < N; l++){
        fprintf(sortedfile, "%d \n", buffer[l]);
    }

    printf("\nSorted numbers inserted into file!\n");

    fclose (sortedfile);

    free(buffer);

}

int main(void){

    srand(time(NULL));

    time_t t1 = time(NULL);
    char buff1[TIME_BUFFER_LEN];    

    printtime(t1, buff1, sizeof(buff1));

    mkfile();

    sortfile();

    time_t t2 = time(NULL);
    char buff2[TIME_BUFFER_LEN];

    printtime(t2, buff2, sizeof(buff2));

    printf("\nStart Time: %s\n", buff1);
    printf("\nEnd Time: %s\n", buff2);
}