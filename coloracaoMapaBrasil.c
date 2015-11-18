#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 26 //qtde maxima de vértices


char *estados[26][12]= {{"BA", "SE", "AL","PE","PI","MA","TO","GO","MG","ES", "end"},
{ "MG","GO","MS","SP","RJ","ES","BA", "end"},
{ "PA","AP","RR","AM","MT","TO","MA", "end"},
{ "MT","PA""AM","RO","MS","GO","TO", "end"},
{ "PE","PB","CE","PI","BA","AL", "end"},
{ "GO","BA","TO","MT","MS","MG", "end"},
{ "TO","MA","PA","MT","GO","BA", "end"},
{ "MS","PR","SP","GO","MG","MT", "end"},
{ "AM","RR","AC","MT","RO","PA", "end"},
{ "MA","PA","TO","BA","PI", "end"},
{ "PI","MA","BA","PE","CE", "end"},
{ "CE","PI","PE","PB","RN", "end"},
{ "SP","PR","MS","RJ","MG", "end"},
{ "PR","SC","SP","MS", "end"},
{ "RJ","SP","MG","ES", "end"},
{ "ES","MG","RJ","BA", "end"},
{ "RO","AM","AC","MT", "end"},
{ "PB","RN","CE","PE", "end"},
{ "AL","PE","BA","SE", "end"},
{ "SC","RS","PR", "end"},
{ "AC","RO","AM", "end"},
{ "RR","PA","AM", "end"},
{ "RN","CE","PB", "end"},
{ "SE","AL","BA", "end"},
{ "RS","SC", "end"},
{ "AP","PA", "end"}};

struct vertice {
    char *sigla;

    struct vertice *prox;
};

struct listaadj{
    struct vertice *listav;
};

struct listaadj *Adj;
struct vertice *novo;
int *marcado;

void inserirEstadosNoGrafo(){

    int  linha, coluna;
    struct vertice *v, fim;


       for (linha=0; linha < 26; linha++){
          for (coluna=0; strcmp(estados[linha][coluna], "end") != 0; coluna++){
               novo = (struct vertice*) malloc(sizeof(struct vertice));
               novo->sigla = estados[linha][coluna];
               novo->prox = NULL;
               printf("criou novo\n");
               //encontra o fim da lista de vertices e insere a sigla no fim dela
               v = Adj[linha].listav;
               if (v == NULL){
                  Adj[linha].listav = novo;
                  printf("inseriu no v = null\n");
                }else{
                   while(v->prox != NULL){
                     v = v->prox;
                     //printf("dentro while\n");
                   }
                   v->prox = novo;
                   printf("inseriu novo\n");
                }
               //link p/ lista
          }
          printf("inseriu uma estado e seus vizinhos\n");
       }


}
//aloca memoria para o grafo e para o vetor de itens visitados
void criarGrafo(){
    int i;

    Adj = (struct listaadj*) malloc(sizeof(struct listaadj)*(TAM+1));
    marcado = (int*) malloc(sizeof (int) * (TAM+1));


    for (i=1; i <=TAM; i++){
        Adj[i].listav = NULL;
        marcado[i] = 0;
    }
}

void imprimirGrafo(){
    printf(" \n\nLista adjacencia\n\n");
    struct vertice *v;
    int i;
    for(i=0; i < TAM; i++){
        v = Adj[i].listav;

        while(v != NULL){
            printf("%s  ", v->sigla);
            v = v->prox;
        }
        printf("\n");
    }
    printf("\n\n");
}

void imprimirEstados(){
    int i, linha, coluna;


       for (linha=0; linha < 26; linha++){
          for (coluna=0; strcmp(estados[linha][coluna], "end") != 0; coluna++){
                printf("%s  ", estados[linha][coluna]);
          }
          printf("\n");
       }


}

int main (){
    //imprimirEstados();
    criarGrafo();
    inserirEstadosNoGrafo();
    imprimirGrafo();

}


