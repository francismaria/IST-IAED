#include "ITEM.h"

Item novo_item(char* nome_hash){							/*Função que cria e guarda um novo hashtag introduzido*/
	Item x = (Item)malloc(sizeof(struct hash));

	x->nome = strdup(nome_hash);
	x->conta = 1;

	return x;
}

void show_item(Item x){
	printf("#%s %ld\n", x->nome, x->conta);
}