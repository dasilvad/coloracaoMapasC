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

char *cor [4];

struct vertice {
    char *sigla;
    int cor;//indice da cor no vetor de cores
    struct vertice *prox;
};

struct listaadj{
    struct vertice *listav;
};

struct listaadj *Adj;
struct vertice *novo;


//encontra um cor para o primeiro vertice da lista de vertice.
//retorna 1 se a cor nao estiver sendo usada no vizinho.
//retorna 0 caso contrario
int encontrarCor (struct vertice *listaVertice, int cor){
    int linha;

    struct vertice *v;
    v = listaVertice->prox;
    while(v != NULL){
        for (linha=0; linha < 26; linha++){//percorre o grafo
            if (strcmp(v->sigla, Adj[linha].listav->sigla ) == 0){//encontra o vizinho no grafo
               if (cor == Adj[linha].listav->cor){//cor selecionada ja esta sendo usada no vizinho do vertice
                    return 0;//false
               }else{
                    break;
               }
            }
        }
        v = v->prox;
    }
    return 1;


}

void  colorirMapaBrasil(char cor1[], char cor2[], char cor3[], char cor4[]){
    cor[0] = cor1;
    cor[1] = cor2;
    cor[2] = cor3;
    cor[3] = cor4;
    int linha, indiceCor;
    //percorre o grafo
    for (linha=0; linha < 26; linha++){
        indiceCor = 0;
        do{//percorre as cores
            if (encontrarCor(Adj[linha].listav, indiceCor) == 1){
                Adj[linha].listav->cor = indiceCor;//colore o vertice
                break;//encontrou cor e coloriu
            }
            indiceCor++;
         }while (indiceCor < 4);
    }
}


void inserirEstadosNoGrafo(){
    int  linha, coluna;
    struct vertice *v, fim;


       for (linha=0; linha < 26; linha++){
          for (coluna=0; strcmp(estados[linha][coluna], "end") != 0; coluna++){
               novo = (struct vertice*) malloc(sizeof(struct vertice));
               novo->sigla = estados[linha][coluna];
               novo->prox = NULL;

               //encontra o fim da lista de vertices e insere a sigla no fim dela
               v = Adj[linha].listav;
               if (v == NULL){
                  Adj[linha].listav = novo;

                }else{
                   while(v->prox != NULL){
                     v = v->prox;
                     //printf("dentro while\n");
                   }
                   v->prox = novo;

                }
          }
       }


}
//aloca memoria para o grafo
void criarGrafo(){
    int i;

    Adj = (struct listaadj*) malloc(sizeof(struct listaadj)*(TAM+1));


    for (i=1; i <=TAM; i++){
        Adj[i].listav = NULL;
    }
}
//imprime o grafo sem a coloracao
void imprimirGrafo(){
    printf("Lista adjacencia\n\n");
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

//imprime a lita de adjacencia com os vertices coloridos
void imprimirGrafoColorido(){
    printf(" \n\nGrafo Colorido\n\n");
    struct vertice *v;
    int i;
    for(i=0; i < TAM; i++){
        printf ("%s -> %s \n", Adj[i].listav->sigla, cor[Adj[i].listav->cor]);
    }
    printf("\n\n");
}

//imprime os estados que serao colocados no grafo
void imprimirEstados(){
    int i, linha, coluna;


       for (linha=0; linha < 26; linha++){
          for (coluna=0; strcmp(estados[linha][coluna], "end") != 0; coluna++){
                printf("%s  ", estados[linha][coluna]);
          }
          printf("\n");
       }
}

//desaloca a lista de adjacencia
void desalocarGrafo(){
    struct vertice *aux;
    int i;
    for(i=0; i < TAM; i++){
        aux = Adj[i].listav;
        Adj[i].listav = Adj[i].listav->prox;
        while (Adj[i].listav !=NULL){
            free(aux);
            aux = Adj[i].listav;
            Adj[i].listav = Adj[i].listav->prox;
        }
    }
    free(Adj);
}

int main (){
    criarGrafo();
    inserirEstadosNoGrafo();
    //imprimirGrafo();
    colorirMapaBrasil("blue", "red", "yellow", "green");
    imprimirGrafoColorido();
    desalocarGrafo();
}
