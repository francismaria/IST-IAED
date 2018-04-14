#include "ITEM.h"

typedef struct node{						/*Definição da estrutura node que possui um Item e um ponteiro para a estrutura seguinte*/
	Item item;
	struct node* next;
}*link;

void mostra_hash_ordena();					/*Definição de todas as funções utilizadas no ADT (hashtable e listas)*/
void mostra_tags();
void incrementa_contador(Item);
void hash_popular();

void init_hashtable();
void insert_hashtable(char*);
link insert_begin(link, Item);
Item search_lista(link, char *);
Item search_hashtable(char*);
void verifica_max(Item);



