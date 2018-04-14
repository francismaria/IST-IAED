#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>											/*Inclusão das bibliotecas que todas as funções no programa necessita*/
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define key_conta_maior(a,b)(a->conta > b->conta)			/*Definição de macro-funções de modo a respeitar a abstração do tipo Item*/		
#define key_conta_igual(a,b)(a->conta == b->conta)
#define key_conta_menor(a,b)(a->conta < b->conta)
#define comp_nome_item(a,b)(strcmp(a->nome, b->nome))
#define incrementa_item(a)(a->conta++);

typedef struct hash{										/*Definição da estrutura hash que possui o nome da hashtag e a quantidade*/
	char *nome;												/*de vezes que essa hashtag aparece repetida*/
	long int conta;
} *Item;

Item novo_item(char *);
void show_item(Item);

#endif
