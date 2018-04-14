								/*Francisco Maria*/
								/*António Alves */
#include "HASH.h"														

#define MAX_LINHA 140
#define NUM_SEPARA 11

char linha[MAX_LINHA + 1];
static const char separators[NUM_SEPARA] = {' ', '.', ',',';',':','\t','\n','?','!','"','\0'};

char* le_linha();																							/*Definição das funções no main*/
void split(char*);

int main(){
	char command;

	command = getchar();
	init_hashtable();
	while(1){
		switch(command){
			case 'a':{
				split(le_linha());
				break;
				}
			case 's':{
				mostra_tags();
				break;
				}
			case 'm':{
				hash_popular();
				break;
				}
			case 'l':{
				mostra_hash_ordena();
				break;
				}
			case 'x':
				return 0;
			}
		command = getchar();
		}
	return 0;
}

void hash_inserida(char* token){					/*Função que dada uma hashtag introduzida pelo utilizador executa o seu devido processo*/
	int i;
	Item item_novo;

	for(i = 0; token[i] != '\0';i++)
		token[i] = tolower(token[i]);

	item_novo = search_hashtable(token);

	if(item_novo == NULL){
		insert_hashtable(token);		
	}
	else{
		incrementa_contador(item_novo);
		verifica_max(item_novo);
	}
}

void split(char* linha){
	char *token = strtok(linha, separators);

	while(token != NULL){
		if(*token == '#')
			hash_inserida(token + 1);	
		token = strtok(NULL, separators);
	}
}

char* le_linha(){
	fgets(linha, MAX_LINHA, stdin);
	return linha;
}