#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ListaGenTeste.h"

struct linha{
	int nro;
	struct linha *Top, *Bottom;
	struct letra *InicioL;
};
typedef struct linha Linha;

struct letra{
	char letra;
	struct letra *prox, *ant;
};
typedef struct letra Letra;

Letra *criaLetra(char letra){
	Letra *novo = (Letra*)malloc(sizeof(Letra));
	novo->prox = NULL;
	novo->ant = NULL;
	novo->letra = letra;
	return novo;
}

Linha *criaLinha(Letra **cursor){
	Linha *novo = (Linha*)malloc(sizeof(Linha));
	
	novo->nro = 0;
	novo->Top = NULL;
	novo->Bottom = NULL;
	novo->InicioL =(*cursor) = criaLetra(' ');
	
	return novo;
}

void insereLetra(Linha **linhaA, Letra **cursor, char letra){
	Letra *novo = criaLetra(letra);
	Letra *aux = *cursor;
	if(aux->ant == NULL){
		novo->prox = aux;
		aux->ant = novo;
		(*linhaA)->InicioL = novo;
	}
	else{
		if(aux->prox == NULL){
			novo->prox = aux;
			aux->ant->prox = novo;
			novo->ant = aux->ant;
			aux->ant = novo;
		}
		else{
			aux->prox->ant = novo;
			novo->prox = aux->prox;
			novo->ant = aux;
			aux->prox = novo;
			(*cursor) = novo;
		}
	}
	if(letra != 21)
		(*linhaA)->nro++;
}

void insereLetraInsert(Linha **linhaA, Letra **cursor, char letra){
	if((*cursor)->prox != NULL){
		(*cursor)->letra = letra;
		(*cursor) = (*cursor)->prox;
	}
	else{
		insereLetra(&(*linhaA), &(*cursor), letra);
	}

}

void apagarLetra(Linha **linhaA, Letra **cursor){
	Letra *aux = *cursor;
	if((*linhaA)->nro >0){
		*cursor = aux->prox;
		if(aux->prox != NULL){
			if(aux->ant == NULL){
				(*linhaA)->InicioL = aux->prox;
				aux->prox->ant = NULL;
			}
			else{
				aux->ant->prox = aux->prox;
				aux->prox->ant = aux->ant;
			}
		}
		free(aux);
		(*linhaA)->nro--;
	}
}

void inicializa(Linha **inicio, Linha **linhaA, Linha **iniTela, Letra **cursor){
	*inicio = *linhaA = *iniTela = criaLinha(&(*cursor));
	(*inicio)->nro = 0;
}

void exibe(Linha *inicio, int insert, int contLinha){
	clrscr();
	Letra *aux;
	Linha *auxLinha;
	int cont = 1;
	printf("\tF2-Abrir   F3-Salvar   F4-Sair   F5-Exibir");
	printf("\n");
	printf("---------------------------------------------------\n");
	
	while(inicio != NULL){
		aux = inicio->InicioL;
		while(aux != NULL){
			printf("%c", aux->letra);
			aux = aux->prox;
		}
		printf("\n");
		if(inicio->Bottom == NULL)
			auxLinha = inicio;
		inicio = inicio->Bottom;
		cont ++;
	}
	
	printf("\n");
	printf("---------------------------------------------------\n");
	printf("Col=%d ,  Lin=%d,  Insert = %d", auxLinha->nro,contLinha, insert);
	
}

void exibe2(Linha *inicio){
	clrscr();
	Letra *aux;
	int cont, primLetra = 20, recuoDir = 10, recuoEsq = 10, p = 0, a = 0;
	
	/*printf("Primeira letra:");
	scanf("%d", primLetra);
	printf("Recuo direito:");
	scanf("%d", recuoDir);
	printf("Recuo esquerdo:");
	scanf("%d", recuoEsq);
	clrscr()*/
	
	printf("\n");
	while(inicio != NULL){
		aux = inicio->InicioL;
		if(inicio->Top == NULL || p == 0){
			for(cont = 0; cont<primLetra; cont++){
				a++;
				printf(" ");
			}
			p = 1;
		}
		else{
			for(cont = 0; cont<recuoEsq; cont++)
				printf(" ");
		}
		while(aux != NULL){
			if(aux->letra == '.' || aux->letra == '?' || aux->letra == '!')
				p = 0;
			
			if(a < 65)
				printf("%c", aux->letra);
			else
				a = 0;
			aux = aux->prox;
			a++;
		}
		printf("\n");
		inicio = inicio->Bottom;
	}
}

void exibePgUpDown(Linha *iniTela, int insert, int contLinha, int col){
	clrscr();
	Letra *aux;
	Linha *auxLinha;
	int cont = 1, negrito = 0;
	printf("\tF2-Abrir   F3-Salvar   F4-Sair   F5-Exibir");
	printf("\n");
	printf("---------------------------------------------------\n");
		
	while(cont < 22 && iniTela != NULL){
		aux = iniTela->InicioL;
		while(aux != NULL){
			
			if(aux->letra == 21){
				if(aux->prox != NULL)
					aux = aux->prox;
				if(negrito == 0){
					textcolor(10);
					while(aux != NULL &&  aux->letra != 21){
						printf("%c", aux->letra);
						aux = aux->prox;
					}
					negrito = 1;
					textcolor(15);
				}
				else
					negrito = 0;
			}
			
			else{
				printf("%c", aux->letra);
				aux = aux->prox;
			}

		}
		printf("\n");
		iniTela = iniTela->Bottom;
		cont ++;
	}
	printf("\n");
	printf("---------------------------------------------------\n");
	printf("Col=%d ,  Lin=%d,  Insert = %d", col,contLinha, insert);
}

void exibePgUpDown2(Linha *iniTela, int insert, int contLinha, int col, char sugestao[]){
	clrscr();
	Letra *aux;
	Linha *auxLinha;
	int cont = 1;
	printf("\tF2-Abrir   F3-Salvar   F4-Sair   F5-Exibir");
	printf("\n");
	printf("---------------------------------------------------\n");
		
	while(cont < 22 && iniTela != NULL){
		aux = iniTela->InicioL;
		while(aux != NULL){
			printf("%c", aux->letra);
			aux = aux->prox;
		}
		printf("\n");
		iniTela = iniTela->Bottom;
		cont ++;
	}
	printf("\n");
	printf("---------------------------------------------------\n");
	printf("Col=%d ,  Lin=%d,  Insert = %d", col,contLinha, insert);
	gotoxy(1, 25);
	printf("\nSugestao: '%s' --- 'Enter' para inserir", sugestao);
}

int verificaLetra(char letra){
	if(letra >= 97 && letra <= 122)
		return 1;
	if(letra == 32 || letra == ',')
		return 1;
	if(letra == '.' || letra == '?' || letra == '!')
		return 1;
	else
		return 0;
}

void enter(Linha **linhaA, Letra **cursor, int *x){
	Linha *nova = criaLinha(&(*cursor)), *auxLinha;
	
	if((*linhaA)->Bottom == NULL){
		(*linhaA)->Bottom = nova;
		nova->Top = *linhaA;
	}
	else{
		auxLinha = (*linhaA)->Bottom;
		auxLinha->Top = nova;
		nova->Top = *linhaA;
		nova->Bottom = auxLinha;
		(*linhaA)->Bottom = nova;
	}				
	*linhaA = nova;
	*x=1;
}

void gravarArquivoTexto(Linha *inicio){
	Letra *aux;
	FILE *pont_arq = fopen("Texto.txt","w+");
	while(inicio !=NULL){
		if(inicio->nro>0){
			aux=inicio->InicioL;
			while(aux->prox != NULL){
				fputc(aux->letra, pont_arq);
				aux=aux->prox;
			}
		}
		inicio = inicio->Bottom;	
		fputc('\n', pont_arq);
	}
	fclose(pont_arq);
	gotoxy(1,27);
	printf("Arquivo gravado com sucesso");
}

void lerArquivoTexto(Linha **inicio, Letra **cursor, Linha **linhaA, int *contLinha, Linha **iniTela){
	char letra;
	Linha *aux;
	Letra *letraaux;
	*linhaA = *iniTela = *inicio;
	FILE *pont_arq = fopen("Texto.txt", "r+");
	while(!feof(pont_arq)){
		letra = fgetc(pont_arq);
		if(letra == '\n' || (*linhaA)->nro == 79){
			aux = criaLinha(&(*cursor));
			(*linhaA)->Bottom = aux;
			aux->Top = *linhaA;
			*linhaA = aux;
			if((*contLinha) >= 21)
				*iniTela = (*iniTela)->Bottom;
			(*contLinha)++;
		}
		else{
			if(!feof(pont_arq))
				insereLetra(&(*linhaA), &(*cursor), letra);
		}
	}
}

void realocaCursor(Linha **linhaA, Letra **cursor, int *x){
	Letra *aux;
	aux = (*linhaA)->InicioL;
	
	(*x) = 0;
	while(aux->prox != NULL){
		(*x)++;
		aux = aux->prox;
	}	
	*cursor = aux;
}

void destruirLinha(Linha **linhaA){
	Letra *auxLetra;
	Linha *auxLinha = *linhaA;

	while(auxLinha->InicioL != NULL){
		auxLetra = auxLinha->InicioL;
		if(auxLetra->prox == NULL)
			auxLinha->InicioL = NULL;
		else{
			auxLinha->InicioL = auxLetra->prox;
			auxLetra->ant = NULL;
			free(auxLetra);
		}
	}
}

void destruirTudo(Linha **inicio){
	Linha *aux;
	while((*inicio)->Bottom != NULL){
		aux = (*inicio)->Bottom;
		(*inicio)->Bottom = (*inicio)->Bottom->Bottom;
		if(aux->Bottom != NULL)
			aux->Bottom->Top = *inicio;
		
		destruirLinha(&aux);
		free(aux);
	}
	aux = *inicio;
	destruirLinha(&aux);
	free(&aux);
	*inicio = NULL;
}


int main(){
	ListaGen *lista;
	char palavra[100], *p4 = NULL, teste[100], entertecla;
	
	for(int i = 0; i<100;  i++){
		palavra[i] = '\0';
		teste[i] = '\0';
	}
	
	Linha *inicio, *linhaA, *iniTela, *nova;
	Linha *auxLinha;
	Letra *cursor, *aux;
	int insert = 0, ler = 0;
	int x,y, contLinha=1, contLG = 0, cont = 0, auxi = 0;
	x = 1;
	y = 3;
	inicializa(&inicio, &linhaA, &iniTela, &cursor);
	inicializar(&lista);	
	char letra;
	
	exibe(inicio, insert, contLinha);
	do{
		letra = getch();
		if(verificaLetra(letra)){
			if(linhaA->nro == 79){
				contLinha++;
				if(contLinha > 21 && insert == 0){
					iniTela = iniTela->Bottom;
					y--;
				}	
				if(insert == 0){
					enter(&linhaA, &cursor, &x);
					gotoxy(x, y++);	
				}
				if(insert == 1){
					if(cursor->prox == NULL){
						enter(&linhaA, &cursor, &x);
						gotoxy(x, y++);	
					}
				}
				contLG = 0;
				for(int i = 0; i< 100;  i++)
					palavra[i] = '\0';
				p4 = NULL;	
			}
			
			if(insert == 0){
				insereLetra(&linhaA, &cursor, letra);
				if(letra == ' '){  //é necessario dar o espaço para inserir na ListaGen
					 if(strlen(palavra)>=3){
						insere(&lista, palavra);
					 }
					contLG = 0;
					for(int i = 0; i< 100;  i++)
						palavra[i] = '\0';
					p4 = NULL;	
				}
				else{	
					palavra[contLG] = letra;
					contLG++;
					if(lista!=NULL ){
						if(strlen(palavra) >= 2)
							p4 = procurar(lista, palavra);
						if(p4!= NULL){
							exibePgUpDown2(iniTela, insert, contLinha, linhaA->nro, p4);
							entertecla = getch();
							if(entertecla == 13){
								for(int i=contLG; i<strlen(p4); i++){
									insereLetra(&linhaA, &cursor, p4[i]);
									x++;
								}
								exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
	
								for(int i = 0; i<strlen(palavra);  i++)
									palavra[i] = '\0';	
								contLG = 0;
								p4 = NULL;	
							}
							else{
								insereLetra(&linhaA, &cursor, entertecla);	
								exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);	
								x++;
								palavra[contLG] = entertecla;
								contLG++;	
							}
						}

					}
				}
			}
			else
				insereLetraInsert(&linhaA, &cursor, letra);
			
			exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);	
			x++;
			gotoxy(x,y);
		}
		else{
			switch(letra){
				case 13: enter(&linhaA, &cursor, &x);	//enter
						 contLinha++;
						 if(contLinha > 21){
							iniTela = iniTela->Bottom;
							y--;
						 }
						 exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
						 gotoxy(x,++y);
						 
						 if(strlen(palavra)>=3 && strlen(palavra)<=30)
						 	insere(&lista, palavra);
						 
						 contLG = 0;
						 for(int i = 0; i< 100;  i++)
						 	palavra[i] = '\0';
						 p4 = NULL;	 
						 break;
						 
				case 72: if(linhaA->Top != NULL && linhaA != iniTela){   //seta para cima
							linhaA = linhaA->Top;
							aux = linhaA->InicioL;
							while(aux->prox != NULL)
								aux = aux->prox;
							cursor = aux;
							x = linhaA->nro+1;
							gotoxy(x, --y);
						 }
						 break;
				
				case 75: if(cursor->ant != NULL){	//seta para a esquerda
						 	gotoxy(--x,y);
						 	cursor = cursor->ant;  							
						 }
					  	 break;
					  	 
				case 77: if(cursor->prox != NULL){  //seta para a direita
							cursor = cursor->prox;
							gotoxy(++x,y);
						 }	
						 break;
						 
				case 80:  if(linhaA->Bottom != NULL && y<23){ //seta para baixo
							linhaA = linhaA->Bottom;
						  	aux = linhaA->InicioL;
						  	while(aux->prox != NULL)
						 	 	 aux = aux->prox;
						  	cursor = aux;
						  	x = linhaA->nro+1;
						  	gotoxy(x, ++y);
						  }
						  break;
						  					  
				case 82:  if(insert == 0)   //Insert
							insert = 1;
						  else
						  	insert = 0;		
							  
						  exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);		
						  break;
						  
				case 83: if(cursor->prox != NULL){		//Delete 
				         	apagarLetra(&linhaA,&cursor);
				         	exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
				         	gotoxy(x,y);
				     	 }
						 break;
					 
	          	case 8:  aux = linhaA->InicioL;		 //BackSpace
				         if(aux->prox == NULL && contLinha != 1){  //verifica se não há nenhuma letra na linha
				         	if(linhaA->Top != NULL && linhaA->Bottom != NULL){  // verifica se estou apagando uma linha que possui Top e Bottom
				         		auxLinha = linhaA->Top;
				         		auxLinha->Bottom = linhaA->Bottom;
				         		linhaA->Bottom->Top = auxLinha;
				         		destruirLinha(&linhaA);
				         		free(linhaA);
				         		if(contLinha > 21)
				         			iniTela = iniTela->Top;
				         		else
				         			y--;
				         		linhaA = auxLinha;
				         	}
				         	else{
				         		if(linhaA->Top == NULL && linhaA->Bottom != NULL){  //Verfica se a linha que eu estou apagando é a primeira e possui um Bottom para se torna a primeira
				         			iniTela = iniTela->Bottom;
									auxLinha = inicio;
				         			inicio = auxLinha->Bottom;
				         			inicio->Top = NULL;
				         			
				         			destruirLinha(&auxLinha);
				         			free(auxLinha);
				         			linhaA = inicio;
				         		}
				         		else{  //verifica se a linha que estou apagando é a ultima e possui um Top para se tornar a ultima
				         			auxLinha = linhaA;
				         			linhaA = linhaA->Top;
				         			linhaA->Bottom = NULL;
				         			destruirLinha(&auxLinha);
				         			free(auxLinha);
				         			if(contLinha > 21)
				         				iniTela = iniTela->Top;
				         			else
				         				y--;
				         		}
				         	}
				         	contLinha--;
				        	realocaCursor(&linhaA, &cursor, &x); //realoca o cursor e o x
				        	exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
				         	gotoxy(++x, y);
				         }
				         else{
				         	if(cursor->ant != NULL){        // apaga a letra
				            	apagarLetra(&linhaA,&cursor->ant);
				            	exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
				            	gotoxy(--x,y);
				            	if(contLG > 0){
				            		palavra[contLG] = '\0';
				            		contLG--;
				            	}

				         	}
				         }
						 break;

				case 71: cursor = linhaA->InicioL; //Home
				         x = 1;
						 gotoxy(x,y);
						 break;
						 
				case 79: aux = linhaA->InicioL;   //End
				         x = 0;
						 while(aux->prox!=NULL) {
						 	 aux=aux->prox;
						 	 x++;
						 }
						 cursor = aux;
						 gotoxy(++x,y);
						 break;	
						
				/*case 81:  if(linhaA->Bottom != NULL){   //PgDown
							linhaA = iniTela;
							iniTela = iniTela->Bottom;
							y = 0;
							while(y < 21){
								linhaA = linhaA->Bottom;
								y++;
							}
							
							realocaCursor(&linhaA, &cursor, &x);
							exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
							y = 23;
							gotoxy(++x, y);
							
						  }
						  break;*/
						 
			    /*case 73: if(iniTela->Top != NULL){		 //PgUp
							iniTela = iniTela->Top;               
							linhaA = iniTela;
							realocaCursor(&linhaA, &cursor, &x);
			    		 	exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
			    		 	y = 3;
			    		 	gotoxy(++x, y);
			    		 }
						 break;	*/
						 
						 
				case 73: //PgUp
					      if(contLinha > 21 && linhaA->Top != NULL)
						  {  													
								linhaA = iniTela;
								y = 0;
								while(y < 21 && linhaA->Top != NULL){
									iniTela = iniTela->Top;
									linhaA = linhaA->Top;
									y++;
								}
								realocaCursor(&linhaA, &cursor, &x);
								exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
								y = 3;
						  		gotoxy(++x, y);	
						  }
						  for(int i=0; i<100; i++)
						 	palavra[i] = '\0';
						 	contLG = 0;	 	
						 break;
				
				case 81: //PgDown
						if(contLinha > 21 && linhaA->Bottom != NULL){ 
							 	linhaA = iniTela;
							 	y=0;
							 	while(y < 20){
							 		linhaA = linhaA->Bottom;
							 		y++;
							 	}
								
								y = 0;
								while(y<21 && linhaA->Bottom != NULL){
									iniTela = iniTela->Bottom;
								 	linhaA = linhaA->Bottom;
								 	y++;
								}
								
								realocaCursor(&linhaA, &cursor, &x);
								exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
								y = 23;
								gotoxy(++x, y);		
						}
						 for(int i=0; i<100; i++)
						 	palavra[i] = '\0';
						 	contLG=0;
						 break;
				
				case 61: gravarArquivoTexto(inicio); break;   //F3
				
				case 60: if(ler == 0){   					  //F2
							destruirTudo(&inicio);
							inicializa(&inicio, &linhaA, &iniTela, &cursor);
							ler = 1;
						 	lerArquivoTexto(&linhaA, &cursor, &linhaA, &contLinha, &iniTela); 
					     	exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
					     	auxLinha = inicio;
					     	y = contLinha;
						 	x = 1;
						 	realocaCursor(&linhaA, &cursor, &x);
						 	gotoxy(++x,y);
						 }
						 break;
				
				case 68: insereLetra(&linhaA, &cursor, 21); 	//F10
						 exibePgUpDown(iniTela, insert, contLinha, linhaA->nro);
						 break;
						 
				//case 63: exibe2(inicio); break;    //F5  //o F5 printa um '?' na tela
				
			}
		}
	}while(letra != 62);
	exibe2(inicio);
	
	//exibe(inicio, insert, contLinha);
	//clrscr();
	//exibir(lista, teste, &cont);
	return 0;
}
