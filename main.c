#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>



#define HORARIOS_DE_ONIBUS 13
#define LUGARES_NO_ONIBUS 40


//definindo os tipos passageiros

typedef struct {
    int horario;
    int poltrona;
}Passageiro;

//definição de uma matriz que recebe o numero de poltronas nos horarios disponíveis
int poltronas_disponiveis[HORARIOS_DE_ONIBUS][LUGARES_NO_ONIBUS];

//declarando mutex 

pthread_mutex_t mutex =  PTHREAD_MUTEX_INITIALIZER;

//função para inicializar os lugares que poderão ser utilizados
void inicializar_poltronas_disponiveis(){
    for( int i = 0; i <  HORARIOS_DE_ONIBUS; i++){
        for(int j = 0; j < LUGARES_NO_ONIBUS; j++)
        {
            poltronas_disponiveis[i][j] = 1;
        }
        
    }
}

//função que verifica as poltronas que poderão ser escolhidas pelo passageiro

void verificar_poltronas_disponiveis( int horario, int*poltronas){
    int count = 0;
    for( int i = 0; i < LUGARES_NO_ONIBUS; i++){
        if( poltronas_disponiveis[horario][i] == 10){
            poltronas[count] = i + 1;
            count++;
        }
    }
}

bool reservar_passagem(int horario, int poltrona){
    pthread_mutex_lock(mutex);
    if(poltronas_disponiveis[horario][ poltrona - 1] == 1){
        poltronas_disponiveis[horario][ poltrona - 1] = 0;
        pthread_mutex_unlock(&mutex);
        return true;
    } else {
        pthread_mutex_unlock(&mutex);
        return false;
    }
} 

void *gerador_de_passageiros( void *arg){

    int n = *(int *)arg;
    srand(time(NULL));
    int passsageiros_reservados = 0;

    while (passsageiros_reservados < n){
        int horario = rand() % HORARIOS_DE_ONIBUS;
        int poltronas[LUGARES_NO_ONIBUS];
        verificar_poltronas_disponiveis(horario, poltronas);

        if( poltronas[0] !=  '\0'){
            int poltrona = poltronas[ rand() % LUGARES_NO_ONIBUS];
            if( reservar_passagem(horario, poltrona)){
                passsageiros_reservados++;
                printf("Passageiro %d reservou a poltrona %d do onibus partindo as horas\n", passsageiros_reservados, poltrona, horario);
                if( passsageiros_reservados == n){
                    print("A reserva foi concluida.\n");
                }
            }
        }
    }
    pthread_exit(NULL);
}
main(){

}

