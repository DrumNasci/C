/*Project huffmantree
auhtor andrenascimento*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 15

typedef enum{false, true} bool;

typedef struct no{      //estrutura da árvore
	int freq;
	char letra;
	struct no *dir;
	struct no *esq; 
}noArv; 

int alfa[26];          //vetor de ocorrencias
int alfa_conv[26];

noArv *pont_vet[MAX]; //vetor de ponteiros

void pause(){
	getchar();
	getchar();
}

noArv *inicializa_ponto(char letra, int freq){
	noArv *novo = (noArv *)malloc(sizeof(noArv));
	novo->freq = freq;
	novo->letra = letra;
	novo->dir = NULL;
	novo->esq = NULL;
	return novo;
}

bool ordena_vet(int cont){
	int i, j;
	noArv *aux = NULL;
	for(j=1; j<cont; j++){
		i = j;
		while((i > 0) && (pont_vet[i]->freq > pont_vet[i-1]->freq)){
			aux = pont_vet[i-1];
			pont_vet[i-1] = pont_vet[i];
			pont_vet[i] = aux;
			i--;
		}
	}
	return true;
}

void imprime(int comp){
	int i=0;
	while(i < comp){
		printf("[%c: %d] ", pont_vet[i]->letra, pont_vet[i]->freq);
		i++;
	}
}

void inicia_alfa(){  //inicia o vetor de ocorrencias com 0
	for(int i=0; i<26; i++){
		alfa[i] = 0;
		alfa_conv[i] = -1;
	}
}

bool gera_arvore(int cont){
	if(cont < 2){
		return true;
	}
	else{
		noArv *pai = (noArv *)malloc(sizeof(noArv));
		int n = cont-1;
		pai = inicializa_ponto(' ', (pont_vet[n]->freq + pont_vet[n-1]->freq));
		pai->dir = pont_vet[n-1];
		pai->esq = pont_vet[n];
		pont_vet[n-1] = pai;
		//free(pont_vet[n]);
		ordena_vet(n);
		imprime(n);
		printf("\n");
		return gera_arvore(n);
	}
}

void imprime_emo(noArv *n){
	if(n != NULL){
		imprime_emo(n->esq);
		printf("[%c %d] ", n->letra, n->freq);
		imprime_emo(n->dir);	
	}
}


int main(){
	char palavra[MAX];
	int i, j, comp, cont=0, soma=0;
	fgets(palavra, MAX, stdin);
	comp = strlen(palavra);
	for(i=0; i<comp; i++){
		alfa[palavra[i]-97]++;
	}
	for(i=0; i<26; i++){
		if(alfa[i] != 0){
			//printf("[%c: %d]\n", i+97, alfa[i]);
			soma += alfa[i];
			pont_vet[cont] = inicializa_ponto(i+97, alfa[i]);
			cont++;
		}
	}
	imprime(cont);
	printf("\nNumero de letas: %d\n\n", soma);
	ordena_vet(cont);
	imprime(cont);
	printf("\n");
	gera_arvore(cont);
	printf("\n");
	imprime_emo(pont_vet[0]);
	
	
	
	printf("\n");
	return 0;
}
