#include "HASH.h"

#define M 1037														/*Definição do tamanho da Hashtable*/

static link* hashtable;
static Item max = NULL;												/*Item que guarda qual o ponteiro para a hash que apareceu mais vezes*/
static int n_tags = 0;												/*Definição de uma variável que guarda o número de hashtags introduzidas*/
static int n_total = 0;												/*Definição de uma variável que guarda o número total de vezes que todas as hashtags são introduzidas*/

void mostra_tags(){
	
	printf("%d %d\n",n_tags, n_total);
}

void incrementa_contador(Item item){								/*Função que incrementa o "conta" da respetiva hash*/
	incrementa_item(item);											/*(o número de vezes que aparece)*/
	n_total++;
}

int compare(const void *a, const void *b){							/*Função compare da função qsort()*/

	Item l = *(Item*)a;
	Item r = *(Item*)b;

	if(key_conta_maior(l,r))
		return -1;
	if (key_conta_menor(l,r))
		return 1;
	if (key_conta_igual(l,r))
		return comp_nome_item(l, r);
	return 0;
}

void mostra_hash_ordena(){											/*Função que ordena e imprime todas as hash introduzidas*/
	Item *tabela=(Item*)malloc(sizeof(Item)*n_tags);				/*e o seu respetivo contador*/
	int index = 0, i;
	link j;															/*Criação de uma tabela auxiliar que contém ponteiros para hash's*/

	for(i = 0; i < M; i++){											/*Ciclo que percorre a hashtable e em cada posição da hashtable*/
		for(j = hashtable[i]; j != NULL; j = j->next){				/*verifica se existe uma lista, caso positivo, irá percorrer*/
			tabela[index++] = j->item;								/*a lista e copiar o ponteiro para a respetiva posição da tabela*/
		}															/*auxiliar*/
	}
	qsort(tabela, n_tags, sizeof(Item), compare);
	for(index = 0; index < n_tags; index++){						/*Após a ordenação da tabela auxiliar(qsort()) vai percorrer a tabela*/
		show_item(tabela[index]);									/*e imprimir os itens aos quais são apontados*/
	}
	free(tabela);				
}

void verifica_max(Item item){										/*Função que é chamada cada vez que se insere uma nova hash ou*/
	if(max == NULL)													/*cada vez que se insere uma hash repetida, de forma a verificar*/
		max = item;													/*se o "conta" do item introduzido ou alterado é maior que o do max*/
	else{
		if(key_conta_maior(item,max))								/*Caso positivo o valor de max passa a ser o do item*/
			max = item;
		else if(key_conta_igual(item,max)){
			if(comp_nome_item(item,max) < 0)
				max = item;
		}
	}
}
void hash_popular(){											
	if (max == NULL)
		return;
	show_item(max);
}

Item search_lista(link h,char *nome_hash){							/*Função que dada a posição na hash procura na lista dessa mesma posição*/
	link current = h;

	if(h == NULL)
		return NULL;
	
	while(strcmp(current->item->nome, nome_hash) != 0){
		if(current->next == NULL)
			return NULL;
		else
			current = current->next;
	}

	return current->item;
}

link insert_begin(link h, Item valores){							/*Função que insere uma nova hash no início da lista da respetiva*/
	link new = (link)malloc(sizeof(struct node));					/*posição retornada pela hash(), (hash function)*/

	new->next = (link)malloc(sizeof(struct node));

	new->item = valores;
	new->next = h;

	n_tags++;
	n_total++;
	verifica_max(new->item);
	return new;
}
int hash(char *v){													/*Hash Function*/
	int h = 0, a = 127;

	for(; *v != '\0'; v++)
		h = (a*h + *v) %M;
	return h;
}

Item search_hashtable(char* v){										/*Função que dado o valor retornado pela função hash*/
	int i = hash(v);												/*procura na respetiva lista a que a posição da hash está a apontar*/
	return search_lista(hashtable[i], v);
}

void insert_hashtable(char *nome_hash){								/*Função que insere um novo hash na hashtable, criando um novo item*/
	Item item = novo_item(nome_hash);								/*e após ser retornado a posição na hashtable, vai-se inserir na*/
	int i = hash(item->nome);										/*respetiva lista*/
	hashtable[i] = insert_begin(hashtable[i], item);
}
void init_hashtable(){												/*Função que iniciliza a hashtable com todos os seus elementos a NULL*/
	int i;
	hashtable = (link*)malloc(sizeof(link)*M);
	for(i = 0; i < M; i++)
		hashtable[i] = NULL;
}
