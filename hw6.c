#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Initalize necessary global variables
char final_string[1000];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Structure for the arguments passed to each thread
typedef struct { int id; int length_of_string; } myarg_t;

// Adds a random letter to the final string
void addto_final_string(int id, int string_length) {

    for (int i = 0; i < string_length; i++) {

        char random_letter = 'A' + (random() % 26);
     
        strncat(final_string, &random_letter, 1);
        printf("Thread #%d: Added character %c to the final string \n", id, random_letter);

    }

}

// Function used to perform thread operations
void *thread_call(void *arg) {

    // Convert the void pointer to a myarg_t pointer 
    myarg_t *param = (myarg_t *)arg;

    // Initalize variables for thread ID and amount of letters to add to the final string (each thread on their own stack)
    int id = param->id;
    int string_length = param->length_of_string;

    // Locked critical section, space where each thread adds a random character to the final string
    pthread_mutex_lock(&mutex);
    addto_final_string(id, string_length);
    pthread_mutex_unlock(&mutex);


    return NULL;
}

int main(int argc, char const *argv[]) {

    // Initialize variables for # of threads and length of the final string, specified by the user
    int num_of_threads = atoi(argv[1]);
    int string_length = atoi(argv[2]);

    // Initialize pointers to allocated memory space on heap for each thread and their aguments
    pthread_t *thread = (pthread_t *)malloc(num_of_threads * sizeof(pthread_t));
    myarg_t *args = (myarg_t *)malloc(num_of_threads * sizeof(myarg_t));

    // Initialize variables for amount of times the threads should execute in order to get specified string length
    int length_per_thread = string_length / num_of_threads; 
    int remainder = string_length - (num_of_threads - 1) * length_per_thread; 

    // Create first thread and set its ID and amount of characters to add to final string
    args[0].id = 1;
    args[0].length_of_string = remainder;
    pthread_create(&thread[0], NULL, thread_call, &args[0]);

    // Create rest of the threads and set their ID and amount of characters to add to final string arguments
    for (int i = 1; i < num_of_threads; i++) {
        args[i].id = i + 1;
        args[i].length_of_string = length_per_thread;
        pthread_create(&thread[i], NULL, thread_call, &args[i]);
    }
    
    // Wait for all threads to stop running
    for (int i = 0; i < num_of_threads; i++) {
        pthread_join(thread[i], NULL);
    }

    // Print final string
    printf("Final string: %s\n", final_string);

    // Free pointers 
    free(args);
    free(thread);

    return 0;

}
