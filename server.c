#include <stdio.h>
#include<stdlib.h>
#include<time.h>

int naleatorio();
int nvalores(int x);
int existe(int x[],int y, int z);

int main(){
    int x,y,z,cont,cont1,temp,tam;
    x = 12;
    y = 12;
    z = nvalores(x);
    tam = nvalores(x);
    int matriz[x][y];
    int valores[z],posicion[z];
    cont = 0;
    while(z > 0){
        temp = naleatorio(50,1);
        if(cont > 0){
            if(existe(valores,cont,temp) == 1){
                z++;
                cont--;
            }
        }
        valores[cont] = temp;
        z--;
        cont++;
    }
    z = nvalores(x);
    cont = 0;
    while(z > 0){
        temp = naleatorio((x*y),0);
        if(cont > 0){
            if(existe(posicion,cont,temp) == 1){
                z++;
                cont--;
            }
        }
        posicion[cont] = temp;
        z--;
        cont++;
    }

    for(int a = 0 ; a < nvalores(x) ; a++){
        printf("%d ",valores[a]);
    }
    printf("\n");

    for(int a = 0 ; a < nvalores(x) ; a++){
        printf("%d ",posicion[a]);
    }
    printf("\n");


    cont = 1;
    cont1 = 0;
    for(int a = 0 ; a < x ; a++){
        for(int b = 0 ; b < y ; b++){
            if(existe(posicion,tam,cont)==1){
                matriz[a][b] = valores[cont1];
                cont1++;
                printf("%d %d\n",matriz[a][b],cont);
            }else{
                matriz[a][b] = 0;
            }
            cont++;
        }
    }

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