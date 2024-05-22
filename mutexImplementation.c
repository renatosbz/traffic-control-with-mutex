#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <time.h>

pthread_mutex_t mutex;
int streetArrayA[4]={32,32,32,32};
int streetArrayB[4]={32,32,32,32};
int junction = 32;
bool lights;

void* interface() {
            printf("\n\n");
            printf("               rua 1\n");
            printf("             +      +\n");
            printf("             |  %c   |\n", streetArrayA[0]);
            printf("             +------+\n");
            printf("             |  %c   |\n", streetArrayA[1]);
            if (lights) {
                printf("      +--+---+\033[32m------\033[39m+---+--+\n");
                printf("rua 4  %c | %c \033[31m|\033[39m  %c   | %c | %c  rua 2\n", streetArrayB[0], streetArrayB[1], junction, streetArrayB[2], streetArrayB[3]);
            } else {
                printf("      +--+---+\033[31m------\033[39m+---+--+\n");
                printf("rua 4  %c | %c \033[32m|\033[39m  %c   | %c | %c  rua 2\n", streetArrayB[0], streetArrayB[1], junction, streetArrayB[2], streetArrayB[3]);
            }
            printf("      +--+---+------+---+--+\n");
            printf("             |  %c   |\n", streetArrayA[2]);
            printf("             +------+\n");
            printf("             |  %c   |\n", streetArrayA[3]);
            printf("             +      +\n");
            printf("               rua 3\n\n\n");
            usleep(119000);
            system("clear");
}

void* threadFunctionA() {
    int i = -1;
    int junctionPass = false;
    int carA = rand() % (77 - 65) + 65;
     while (i < 3) {
    
        if(i+1 == 2 && junctionPass == false){
            
            
            pthread_mutex_lock(&mutex);
            lights = true;
            junctionPass=true;
            streetArrayA[i] = 32;
            junction = carA;

            
            
            interface();          
            

            junction = 32;
            pthread_mutex_unlock(&mutex);
            

            
        }
        else{
  
            streetArrayA[i] = 32;
            i++;
            streetArrayA[i] = carA;


            pthread_mutex_lock(&mutex); 
            interface();

            
            pthread_mutex_unlock(&mutex);
            usleep(9000);
            
        }
        
         
    }
    streetArrayA[i] = 32;
    pthread_exit(NULL);
}

void* threadFunctionB() {
    int i = -1;
    int junctionPass = false;
    int carB = rand() % (90 - 78) + 78;
     while (i < 3) {
    
        if(i+1 == 2 && junctionPass == false){

            pthread_mutex_lock(&mutex);

            lights = false;
            junctionPass=true;
            streetArrayB[i] = 32;
            junction = carB;

            interface();
            
            junction = 32;
            pthread_mutex_unlock(&mutex);
            
        }
        else{

            streetArrayB[i] = 32;
            i++;
            streetArrayB[i] = carB;

            pthread_mutex_lock(&mutex); 
            interface();

            pthread_mutex_unlock(&mutex);
            
            usleep(9000);
            
            
        }
        
         
    }
            
    streetArrayB[i] = 32;
    
    pthread_exit(NULL);
}



int main() {
    int aux = 0;
    int iterations;

    srand(time(NULL));
    iterations = (rand() % 5) + 1;

    pthread_mutex_init(&mutex, NULL);

    while (aux < iterations) {
        pthread_t thread1, thread2;

        

        pthread_create(&thread1, NULL, threadFunctionA, NULL);

        pthread_create(&thread2, NULL, threadFunctionB, NULL);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        
        aux++;
    }  
        pthread_mutex_destroy(&mutex);
        return 0;
    }