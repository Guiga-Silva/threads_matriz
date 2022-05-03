#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *sum(void *matriz);

int count = 0;
int global_index = 0;
int qtd_threads;

int main(void) {
        
        scanf(" %d", &qtd_threads);

        pthread_t threads[qtd_threads];
        int matriz[qtd_threads][qtd_threads];

        for (int i = 0; i < qtd_threads; i++) {
                for (int j = 0; j < qtd_threads; j++) {
                        scanf(" %d", &matriz[i][j]);
                }
        }

        for (int i = 0; i < qtd_threads; i++) {
                if (pthread_create(&(threads[i]), NULL, (void *) sum, matriz)) {
                        printf("Erro na criacao da thread\n");
                }
        }

        for (int i = 0; i < qtd_threads; i++) {
                pthread_join(threads[i], NULL);
        }

        printf("Soma de todos os valores: %d\n", count);

        return 0;
}

int line_index = 0;
void *sum(void *matriz) {

        pthread_mutex_lock(&mutex);

        int *matriz_local = (int *) matriz;
        int *linha = matriz_local + global_index;
        int soma_linha = 0;

        for (int i = 0; i < qtd_threads; i++) {
                count += linha[i];
                soma_linha += linha[i];
                global_index++;
        }
        line_index++;
        printf("Soma da linha %d da matriz: %d\n", line_index, soma_linha);


        pthread_mutex_unlock(&mutex);
}