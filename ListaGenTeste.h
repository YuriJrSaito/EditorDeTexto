#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>

struct listagen{
	char letra, final;
	struct listagen *prox, *prim;
};
typedef struct listagen ListaGen;

ListaGen *Cria(char info){
	ListaGen *novo = (ListaGen*)malloc(sizeof(ListaGen));
	
	novo->letra = info;
	novo->prox = NULL;
	novo->prim = NULL;
	novo->final = 'F';
	
	return novo;
}

void inicializar(ListaGen **lista){
	*lista = NULL;
}

/*void exibir(ListaGen *lista){
	if(lista != NULL){
		printf("%c", lista->letra);
		if(lista->final == 'T')
			printf("\n");
		exibir(lista->prim);
		exibir(lista->prox);
	}
}*/



void exibir(ListaGen *lista, char teste[], int *cont){
	if(lista != NULL){
		teste[*cont] = lista->letra;
		(*cont)++;
		if(lista->final == 'T'){
			printf("%s", teste);
			printf("\n");	
		}
		exibir(lista->prim, teste, &(*cont));
		teste[*cont] = '\0';
		(*cont)--;
		exibir(lista->prox, teste, &(*cont));
	}
}


/*void exibe(ListaGen *lista){
	while(lista != NULL){
		printf("%c", lista->letra);
		if(lista->final == 'T'){
			printf("\n");
		lista = lista->prim;
		}
	}
}*/

ListaGen *procuraHorizontal(ListaGen *aux, char letra, ListaGen **ant){
	if(aux->prox == NULL && aux->letra != letra){
		*ant = aux;
		return NULL;
	}
	while(aux != NULL && aux->letra != letra){
		*ant = aux;
	 	aux = aux->prox;
	}
	return aux;
}

char *procurar(ListaGen *lista, char palavra[]){
	ListaGen *aux;
	int i=0, j=0, flag = 0;
	static char teste[30];
	
	while(i < strlen(palavra) && flag == 0){
		aux = lista;
		if(aux->prox == NULL && aux->letra != palavra[i])
			return NULL;
		else{
			
			while(aux != NULL && aux->letra != palavra[i])
				aux = aux->prox;
			if(aux != NULL && aux->prim != NULL){
				teste[j++] = aux->letra;
				lista = aux->prim;
			}
			else
				flag = 1;
			i++;
		}
	}
	if(flag == 0){
		while(lista->prim != NULL && lista->final != 'T'){
			teste[j++] = lista->letra;
			lista = lista->prim;
		}
		if(lista != NULL){
			teste[j] = lista->letra;
			teste[++j] = '\0';
		}
		return teste;
	}
	else
		return NULL;
}

void insere(ListaGen **lista, char palavra[]){
	ListaGen *aux, *nova, *ant, *aux2;
	int i = 0, flag = 0;
	aux = *lista;
	if(*lista == NULL){
		*lista = Cria(palavra[i++]);
		aux = *lista;
		while(i < strlen(palavra)){
			nova = Cria(palavra[i]);
			aux->prim = nova;
			aux = nova;
			i++;
		}
		aux->final = 'T';
	}
	else{
		while(i < strlen(palavra)){
			aux2 = procuraHorizontal(aux, palavra[i], &ant);
			if(aux2 == NULL){
				flag = 1;
				ant->prox = Cria(palavra[i]);
				ant = ant->prox;
				i++;
				while(i < strlen(palavra)){
					nova = Cria(palavra[i]);
					ant->prim = nova;
					ant = nova;
					i++;
				}
				ant->final = 'T';
			}
			else{
				 if(aux2->prim != NULL)
				 	aux = aux2->prim;
				 else{
				 	if(aux2->letra == palavra[i++] && i<strlen(palavra))
				 	{
				 	 	flag = 1;
					 	aux2->prim = Cria(palavra[i++]);
						aux2 = aux2->prim;
					 	while(i < strlen(palavra)){
					  		aux2->prim = Cria(palavra[i]);
						 	aux2 = aux2->prim;
						 	i++;
					 	}
					 	aux2->final = 'T';
					}
				 }
				 i++;
			}
		}
		if(flag == 0)
			aux2->final = 'T';	
	}
}
