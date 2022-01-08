#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 4444
int naleatorio();
int nvalores(int x);
int existe(int x[],int y, int z);
int jugadores(int x);

int main(){

	int sockfd, ret, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_in newAddr;
	socklen_t addr_size;
	
	int fd1[2],fd2[2];
	int x,y,z,cont,cont1,temp,tam,jug,primer;
	int tube1 = pipe(fd1);
	int tube2 = pipe(fd2);
	char buffer[1024];
	pid_t childpid;
	
    //Ingresar cantidad jugadores
    jug = 4;

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
    /*for(int a = 0 ; a < nvalores(x) ; a++){
        printf("%d ",valores[a]);
    }
    printf("\n");*/

    //Imprimir las posiciones
    /*for(int a = 0 ; a < nvalores(x) ; a++){
        printf("%d ",posicion[a]);
    }
    printf("\n");*/

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
    /*for(int a = 0 ; a < x ; a++){
        for(int b = 0 ; b < y ; b++){
            if(matriz[a][b] < 10){
                printf("[0%d]",matriz[a][b]);
            }else{
                printf("[%d]",matriz[a][b]);
            }
            
        }
        printf("\n");
    }*/

	if(tube1 < 0) {
        printf("Error al crear pipe 1\n");
        exit(1);
    }
	if(tube2 < 0) {
        printf("Error al crear pipe 2\n");
        exit(1);
    }

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error en la conexion.\n");
		exit(1);
	}
	printf("[+]Server Socket esta creado.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error al vincular.\n");
		exit(1);
	}
	printf("[+]Vincular al puerto%d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Escuchando....\n");
	}else{
		printf("[-]Error al vincular.\n");
	}
    primer=0;
	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}
		//Imprime que se conecto un cliente
        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
        //aqui agregar un contador de los clientes conectados
		//if(conectados=cantidadjugadores) hacer las cosas
		if((childpid = fork()) == 0){
			close(sockfd);
			while(1){
				//Recibe datos del cliente
				recv(newSocket, buffer, 1024, 0);
				if(strcmp(buffer, ":exit") == 0){
					//Imprime la desconexion del cliente
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}else{
					//Imprime lo que el cliente mando
                    if(primer!=0){
                        printf("Client: %s\n", buffer);
                        close(fd1[0]);
                        close(fd2[1]);

                        //Hijo manda al Padre
                        write(fd1[1],buffer,sizeof(buffer));

                        //Hijo lee del padre
                        if(read(fd2[0],buffer,sizeof(buffer)) > 0) {
                            printf("El padre dijo: %s\n",buffer);
                        }
                    }else{
                        primer++;
					    bzero(buffer, sizeof(buffer));
                    }
					
					

					//Devuelve lo que se recibio al cliente
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
			}
        }else{
            while(1) {
                close(fd1[1]);
                close(fd2[0]);
                
                //Padre lee del hijo
                if(read(fd1[0],buffer,sizeof(buffer)) > 0) {
                    printf("El hijo escribe: %s\n",buffer);
                }
                //Padre manda al hijo
                write(fd2[1],buffer,sizeof(buffer));
            }
		}
	}
	close(newSocket);
	return 0;
}

int naleatorio(int y , int z){
    int x;
    //srand (time(NULL));
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