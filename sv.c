#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define DIM 1000
#define FIFONAME "myfifo"

sem_t semaforo;


int naleatorio();
int nvalores(int x);
int existe(int x[],int y, int z);
int jugadores(int x);

void th1_function(){
    for(int i=0;i<DIM;i++){
        sem_wait(&semaforo);
        // printf("Turno J1: ");
        sem_post(&semaforo);
    }
}

 void th2_function(){
    for(int i=0;i<DIM;i++){
        sem_wait(&semaforo);
        // printf("Turno J2: ");
        sem_post(&semaforo);
    }
}

void th3_function(){
    for(int i=0;i<DIM;i++){
        sem_wait(&semaforo);
        // printf("Turno J3: ");
        sem_post(&semaforo);
    }
}

void th4_function(){
    for(int i=0;i<DIM;i++){
        sem_wait(&semaforo);
        // printf("Turno J4: ");
        sem_post(&semaforo);
    }
}

int main(void){
	int x,y,z,cont,cont1,temp,tam,jug;
    int fd1[2],fd2[2];
	int tube1 = pipe(fd1);
	int tube2 = pipe(fd2);
	pid_t childpid;
	//Ingresar cantidad jugadores
    jug = 2;

    //Iniciar la matriz
    x = jugadores(jug);
    y = jugadores(jug);
    int matriz[x][y];

    //Generar los numeros aleatorios
    z = nvalores(x); 
    int valores[z];
    cont = 0;
    while(z > 0){
        temp = naleatorio(50,1);
        if(cont > 0){
            if(existe(valores,cont,temp) == 0){
                valores[cont] = temp;
                z--;
                cont++;
            }
        }else{
            valores[cont] = temp;
            z--;
            cont++;
        }
    }
    
    //Generar posiciones aleatorias para los numeros
    z = nvalores(x);
    int posicion[z];
    cont = 0;
    while(z > 0){
        temp = naleatorio((x*y),1);
        if(cont > 0){
            if(existe(posicion,cont,temp) == 0){
                posicion[cont] = temp;
                z--;
                cont++;
            }
        }else{
            posicion[cont] = temp;
            z--;
            cont++;
        }
        
    }

    //Imprimir los numeros
    // for(int a = 0 ; a < nvalores(x) ; a++){
    //     printf("%d ",valores[a]);
    // }
    // printf("\n");

    // //Imprimir las posiciones
    // for(int a = 0 ; a < nvalores(x) ; a++){
    //     printf("%d ",posicion[a]);
    // }
    // printf("\n");

    //Llenar la matriz con los numeros en sus respectivas posiciones
    cont = 1;
    cont1 = 0;
    for(int a = 0 ; a < x ; a++){
        for(int b = 0 ; b < y ; b++){
            if(existe(posicion,nvalores(x),cont)==1){
                matriz[a][b] = valores[cont1];
                cont1++;
                //printf("%d %d\n",matriz[a][b],cont);
            }else{
                matriz[a][b] = 0;
            }
            cont++;
        }
    }

    //Imprimir la matriz
    for(int a = 0 ; a < x ; a++){
        for(int b = 0 ; b < y ; b++){
            if(matriz[a][b] < 10){
                printf("[0%d]",matriz[a][b]);
            }else{
                printf("[%d]",matriz[a][b]);
            }
            
        }
        printf("\n");
    }

    int n,fd;
	char buf[1024];

	// unlink(FIFONAME);
	// if(mkfifo(FIFONAME, 666)<0){
	// 	perror("mkfifo");
	// 	exit(1);
	// }
	if((fd=open(FIFONAME,O_RDWR))<0){
		perror("open");
		exit(1);
	}
    
	

    pthread_t th1, th2;
    sem_init(&semaforo, 0, 1);
    pthread_create(&th1, NULL, (void *) th1_function, (void *) NULL);
	pthread_create(&th2, NULL, (void *) th2_function, (void *) NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    if(jug>=3){
        pthread_t th3;
        pthread_create(&th3, NULL, (void *) th3_function, (void *) NULL);
        pthread_join(th3,NULL);
    }
    if(jug==4){
        pthread_t th4;
        pthread_create(&th4, NULL, (void *) th4_function, (void *) NULL);
        pthread_join(th4,NULL);
    }

    
    while((n=read(fd,buf,sizeof(buf)))>0){
        write(1,buf,n);
	}

    // while(1){
    //     if((childpid = fork()) == 0){
    //         while(1){
    //             n=read(fd,buf,sizeof(buf));
    //             if(strlen(buf)>1){
    //                 printf("Client: %s\n", buf);
    //                 printf("Tamano: %ld\n", strlen(buf));
    //                 close(fd1[0]);
    //                 close(fd2[1]);

    //                 //Hijo manda al Padre
    //                 write(fd1[1],buf,sizeof(buf));

    //                 //Hijo lee del padre
    //                 if(read(fd2[0],buf,sizeof(buf)) > 0) {
    //                     printf("El padre dijo: %s\n",buf);
    //                 }
    //                 //strcpy(buf,"");
    //                 bzero(buf,sizeof(buf));
    //             }
    //         }
    //     }else{
    //         while(1) {
    //             n=read(fd,buf,sizeof(buf));
    //             if(strlen(buf)>1){
    //                 close(fd1[1]);
    //                 close(fd2[0]);
                    
    //                 //Padre lee del hijo
    //                 if(read(fd1[0],buf,sizeof(buf)) > 0) {
    //                     printf("El hijo escribe: %s\n",buf);
    //                 }
    //                 //Padre manda al hijo
    //                 write(fd2[1],buf,sizeof(buf));
    //                 //strcpy(buf,"");
    //                 bzero(buf,sizeof(buf));
    //             }
    //         }
    //     }
    // }
    //close(fd);
	exit(0);
}

int naleatorio(int y , int z){
    int x;
    srand (time(NULL));
    x = rand()%y+z;
    return x;
}

int nvalores(int x){
    if(x = 8){
        return 16;
    }
    if(x = 10){
        return 25;
    }
    if(x = 12){
        return 36;
    }
}

int existe(int x[] , int y , int z){
    for(int a = 0 ; a < y ; a++){
        if(z == x[a]){
            return 1;
        }
    }
    return 0;
}

int jugadores(int x){
    if(x == 2){
        return 8;
    }
    if(x == 3){
        return 10;
    }
    if(x == 4){
        return 12;
    }
}