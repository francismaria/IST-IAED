#include <stdio.h>								/*Francisco Maria     83464*/
#include <string.h>

#define MAXAERO 1001																						

typedef struct {																					/*Definição da estrutura aeroporto que permite*/
	char id[4];																						/*ter acesso ao nome do aeroporto, à sua capacidade*/
	int max_capac;																					/*máxima e ao seu estado de operação*/
	int estado;
} aeroporto;

typedef struct {																					/*Definição da estrutura voo que é composta*/
	aeroporto a1;																					/*por 2 aeroportos e pelo número de voos que*/
	aeroporto a2;																					/*existe entre esses dois aeroportos*/			
	int n_voos;
} voo;

void executa_A(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_I(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_F(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_G(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_R(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_S(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_N(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);							/*Declaração de todas as funçoes no programa*/
void executa_P(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_Q(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_V(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_C(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_O(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_L(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);
void executa_X(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero);

int main(){
	static voo matriz[MAXAERO][MAXAERO];															/*Declaração da matriz (quadrada) que contém todos os aeroportos e os vooes entre os mesmos*/
	aeroporto v_aero[MAXAERO];																		/*Declaração do vetor aeroporto que vai servir para, através do índice da matriz, descobrir todas as informações sobre esse aeroporto*/
	int num_aero = 0;																				/*Declaração do inteiro que vai atualizar o tamanho do vetor de suporte (v_aero)*/
	char command;

	command = getchar();
	while (1){
		switch (command){
			case 'A':{
				executa_A(v_aero, matriz, num_aero);
				num_aero += 1;
				break;
			}
			case 'I':{
				executa_I(v_aero, matriz, num_aero);
				break;
			}
			case 'F':{
				executa_F(v_aero, matriz, num_aero);
				break;
			}
			case 'G':{
				executa_G(v_aero, matriz, num_aero);
				break;
			}
			case 'R':{
				executa_R(v_aero, matriz, num_aero);
				break;
			}
			case 'S':{
				executa_S(v_aero, matriz, num_aero);
				break;
			}
			case 'N':{
				executa_N(v_aero, matriz, num_aero);
				break;
			}
			case 'P':{
				executa_P(v_aero, matriz, num_aero);
				break;
			}
			case 'Q':{
				executa_Q(v_aero, matriz, num_aero);
				break;
			}
			case 'V':{
				executa_V(v_aero, matriz, num_aero);
				break;
			}
			case 'C':{
				executa_C(v_aero, matriz, num_aero);
				break;
			}
			case 'O':{
				executa_O(v_aero, matriz, num_aero);
				break;
			}
			case 'L':{
				executa_L(v_aero, matriz, num_aero);
				break;
			}
			case 'X':{
				executa_X(v_aero, matriz, num_aero);
				return 0;
			}
		}
		command = getchar();
	}
	return 0;
}

void executa_A(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que permite adicionar novos aeroportos*/

	scanf("%s %d", v_aero[num_aero].id, &v_aero[num_aero].max_capac);										/*Cópia do id e da capacidade máxima do aeroporto para o vetor auxiliar da matriz*/
	v_aero[num_aero].estado = 1;																			/*Uma vez que esta função "junta" um aeroporto à rede, o seu estado de opoeração fica a 1*/
																													
	matriz[num_aero][num_aero].n_voos = 0;																	/*Inicializa o aeroporto com 0 voos*/
	matriz[num_aero][num_aero].a1.max_capac = v_aero[num_aero].max_capac;
	matriz[num_aero][num_aero].a2.max_capac = v_aero[num_aero].max_capac;

	strcpy(matriz[num_aero][num_aero].a1.id,v_aero[num_aero].id);
	strcpy(matriz[num_aero][num_aero].a2.id,v_aero[num_aero].id);
}

void executa_I(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que atera a capacidade máxima de operação do aeroporto*/
	int num_voos = 0, nova_cap = 0, i, j, tamanho;
	char nome_aero[4];

	tamanho = num_aero + 1;																					/*Recebe do utilizador o id do aeroporto e nova capacidade para que quer alterar*/
	scanf("%s %d", nome_aero, &nova_cap);

	for(i = 0; i < tamanho; i++){																			/*Caso ao percorrer o vetor auxiliar com todos os id's dos aeroportos encontrar o id pretendido sai do ciclo*/
		if(strcmp(nome_aero, v_aero[i].id) == 0)			
			break;
	}

	for(j = 0; j < tamanho; j++){																			/*Calcula o número de voos (ida e volta) do aeroporto*/
		num_voos += matriz[i][j].n_voos;
		num_voos += matriz[j][i].n_voos;					
	}

	if (nova_cap < 0){
		if(v_aero[i].max_capac +  nova_cap >= num_voos && v_aero[i].estado == 1){							/*Nesta verificação tornei a nova capacidade em positivo*/
			v_aero[i].max_capac += nova_cap;				
			matriz[i][i].a1.max_capac += nova_cap; 				
			matriz[i][i].a2.max_capac += nova_cap;
			}
		else
			printf("*Capacidade de %s inalterada\n", v_aero[i].id);
	}
	else{																							
		if((v_aero[i].max_capac + nova_cap) >= num_voos && v_aero[i].estado == 1){                           
			v_aero[i].max_capac += nova_cap;
			matriz[i][i].a1.max_capac += nova_cap;
			matriz[i][i].a2.max_capac += nova_cap;
		}
		else
			printf("*Capacidade de %s inalterada\n", v_aero[i].id);
	}
}

void executa_F(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que adiciona um voo de ida e volta*/
	int i, j, k, tamanho, num_voos_1 = 0, num_voos_2 = 0;
	char aero_1[4], aero_2[4];

	scanf("%s %s", aero_1, aero_2);																			/*Recebe do utilizador duas strings que correspondem a 2 id's de aeroportos*/

	tamanho = num_aero + 1;
	for(i = 0; i < tamanho; i++){
		if(strcmp(v_aero[i].id, aero_1) == 0)
			break;
	}

	for(j = 0;j < tamanho; j++){
		if(strcmp(v_aero[j].id, aero_2) == 0)			
			break;																
	}

	for(k = 0; k < tamanho; k++){																			/*Cálculo de todos os voos (ida e volta) para o primeiro e para o segundo aeroporto introduzido*/
		num_voos_1 += matriz[i][k].n_voos;
		num_voos_1 += matriz[k][i].n_voos;
		num_voos_2 += matriz[j][k].n_voos;
		num_voos_2 += matriz[k][j].n_voos;
	}

	if(i == tamanho || j == tamanho || v_aero[i].max_capac < (num_voos_1 + 2)||								/*Caso os dois aeroportos tenham espaço para mais 2 ligações  e estejam abertos, adiciona o voo de ida e volta entre esses mesmo aeroportos*/
		v_aero[j].max_capac < (num_voos_2 + 2) || v_aero[i].estado == 0 || v_aero[j].estado == 0)		
		printf("*Impossivel adicionar voo RT %s %s\n", aero_1, aero_2);
	else{
		matriz[i][j].n_voos += 1;
		matriz[j][i].n_voos += 1;
	}
}

void executa_G(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que adiciona um voo de ida*/
	int i, j, k, tamanho, num_voos_1 = 0, num_voos_2 = 0;
	char aero_1[4], aero_2[4];

	scanf("%s %s", aero_1, aero_2);

	tamanho = num_aero + 1;
	for(i = 0; i < tamanho; i++){
		if(strcmp(v_aero[i].id, aero_1) == 0)
			break;
	}

	for(j = 0;j < tamanho; j++){
		if(strcmp(v_aero[j].id, aero_2) == 0)				
			break;
	}
	for(k = 0; k < tamanho; k++){
		num_voos_1 += matriz[i][k].n_voos;
		num_voos_1 += matriz[k][i].n_voos;
		num_voos_2 += matriz[j][k].n_voos;
		num_voos_2 += matriz[k][j].n_voos;
	}
	
	if(i == tamanho || j == tamanho || num_voos_1 == v_aero[i].max_capac || num_voos_2 == v_aero[j].max_capac
		|| v_aero[i].estado == 0 || v_aero[j].estado == 0)
		printf("*Impossivel adicionar voo %s %s\n", aero_1, aero_2);
	else
		matriz[i][j].n_voos += 1;				
}

void executa_R(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){										/*Função que remove um voo com partida no primeiro aeroporto introduzido e com chegada no segundo*/
	int i, j, k,tamanho, num_voos_1 = 0;
	char aero_1[4], aero_2[4];

	scanf("%s %s", aero_1, aero_2);

	tamanho = num_aero + 1;
	for(i = 0; i < tamanho; i++){
		if(strcmp(v_aero[i].id, aero_1) == 0)
			break;
	}

	for(j = 0;j < tamanho; j++){
		if(strcmp(v_aero[j].id, aero_2) == 0)				
			break;
	}
	for(k = 0; k < tamanho; k++){
		num_voos_1 += matriz[i][k].n_voos;
		num_voos_1 += matriz[k][i].n_voos;
	}
	if(i == tamanho || j == tamanho || matriz[i][j].n_voos == 0 || v_aero[i].estado == 0 || v_aero[j].estado == 0 || num_voos_1 == 0)
		printf("*Impossivel remover voo %s %s\n", aero_1, aero_2);
	else{
		matriz[i][j].n_voos += -1;										
	}
}

void executa_S(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){										/*Função que remove voo de ida e volta entre o primeiro aeroporto introduzido e o segundo*/
	int i, j, k, tamanho, num_voos_1 = 0, num_voos_2 = 0;
	char aero_1[4], aero_2[4];

	scanf("%s %s", aero_1, aero_2);

	tamanho = num_aero + 1;
	for(i = 0; i < tamanho; i++){
		if(strcmp(v_aero[i].id, aero_1) == 0)
			break;
	}

	for(j = 0;j < tamanho; j++){
		if(strcmp(v_aero[j].id, aero_2) == 0)				
			break;
	}
	
	for(k = 0; k < tamanho; k++){
		num_voos_1 += matriz[i][k].n_voos;
		num_voos_1 += matriz[k][i].n_voos;
		num_voos_2 += matriz[j][k].n_voos;
		num_voos_2 += matriz[k][j].n_voos;
	}

	if(i == tamanho || j == tamanho || num_voos_1 < 1 || num_voos_2 < 1 ||										/*Caso o número de voos seja igual a 0 é impossível removê-los*/
		matriz[i][j].n_voos == 0 || matriz[j][i].n_voos == 0 || v_aero[i].estado == 0 || v_aero[j].estado == 0)
		printf("*Impossivel remover voo RT %s %s\n", aero_1, aero_2);
	else{
		matriz[i][j].n_voos += -1;
		matriz[j][i].n_voos += -1;
	}
}

void executa_N(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){										/*Função que retorna o núero de voos (ida e volta) entre dois aeroportos*/
	int i, j, tamanho;
	char aero_1[4], aero_2[4];

	scanf("%s %s", aero_1, aero_2);

	tamanho = num_aero + 1;
	for(i = 0; i < tamanho; i++){
		if(strcmp(v_aero[i].id, aero_1) == 0)
			break;
	}

	for(j = 0;j < tamanho; j++){
		if(strcmp(v_aero[j].id, aero_2) == 0)				
			break;
	}

	if (i + 1 == tamanho + 1 && j + 1 == tamanho + 1)
		printf("*Aeroporto %s inexistente\n*Aeroporto %s inexistente\n", aero_1, aero_2);
	else if(i + 1 == tamanho + 1)								
		printf("*Aeroporto %s inexistente\n", aero_1);
	else if(j + 1 == tamanho + 1)
		printf("*Aeroporto %s inexistente\n", aero_2);
	else
		printf("Voos entre cidades %s:%s:%d:%d\n",aero_1, aero_2, matriz[i][j].n_voos, matriz[j][i].n_voos);/*Caso todas as condições anteriores não se verifiquem o número de voos de ida vai buscar à matriz na linha do primeiro aeroporto e na coluna do segundo aeroporto, e nos voos de volta vice-versa*/
}

void executa_P(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que retorna o aeroporto com mais rotas (maior número de voos)*/
	int i, j, tamanho, soma = 0, max = 0, soma_out = 0, soma_in = 0, n_out = 0, n_in = 0, indice = 0;

	tamanho = num_aero + 1;
	for(i = 0;i < tamanho; i++){																			/*Este ciclo percorre a matriz, somando todos os voos dos aeroportos*/
		soma = 0;																							/*caso a soma desse aeroporto i seja maior que o máximo cuja variável*/	
		soma_in = 0;																						/*max foi inicializada a 0, max fica igual à soma total dos voos desse*/
		soma_out = 0;																						/*aeroporto o indice do aeroporto na matriz fica tambe guardado e criei*/
		for(j = 0; j < tamanho; j++){																		/*as duas variáveis(n_in e n_out) que recebem os respetivos números de*/
			soma_out += matriz[i][j].n_voos;																/*voos a entrar e a sair, respetivamente, sendo que as linhas da matriz*/
			soma_in += matriz[j][i].n_voos;																	/*são os aeroportos de partida e as colunas da matriz são os aeroportos de chegada*/
		}
		soma = soma_out + soma_in;
		if(max < soma){
			max = soma;
			indice = i;
			n_out = soma_out;
			n_in = soma_in;
		}																									/*Ao ter obtido o índice do aeroporto cuja soma dos voos é a máxima*/
	}																										/*todos os aeroportos o programa vai ao vetor auxiliar da matriz cujo*/
	printf("Aeroporto com mais rotas %s:%d:%d\n", v_aero[indice].id, n_out, n_in);							/*indíce é o do aeroporto com mais voos*/
}

void executa_Q(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que retorna o aeroporto com maior número de aeroportos conectados*/
	int i, k, indice = 0, tamanho, max = 0, soma, aero_indice = 0;
	aeroporto vetor_repete[MAXAERO];																		/*Criei um vetor, do tipo aeroporto, auxiliar para guardar os id's dos aeroportos*/

	tamanho = num_aero + 1;
	for(i = 0; i < tamanho; i++){																			/*Este ciclo percorre a matriz verificando se os voos entre o aeroporto i(fixado)*/
		soma = 0;																							/*e o aeroporto j é maior ou igual a 1, caso essa condição se verifique a variável*/
		indice = 0;																							/*soma incrementa, caso não haja voos na linha i e coluna k vai verificar se os há*/
		for(k = 0; k < tamanho; k++){																		/*na linha k e coluna i*/
			if(matriz[i][k].n_voos >= 1){
				soma += 1;
				strcpy(vetor_repete[indice].id,v_aero[k].id);
				indice += 1;
			}
			else{
				if(matriz[k][i].n_voos >= 1)
					soma += 1;
			}
		}
		if (soma > max){																					/*Caso a soma dos aeroportos conectados seja maior que o max (variável que é atualizada*/
			max = soma;																						/*cada vez que o número de aeroportos conectados é maior que o próprio max) guarda o número*/
			aero_indice = i;																				/*de aeroportos e o índice do aeroporto*/
			}
	}
	printf("Aeroporto com mais ligacoes %s:%d\n", v_aero[aero_indice].id, max);
}

void executa_V(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que retorna o par de aeroportos aero_1 e aero_2 com o maior número a sair de aero_1 a aero_2*/
	int i, k, max = 0, tamanho, aero1_indice = 0, aero2_indice = 0;

	tamanho = num_aero + 1;																				
	for(i = 0; i < tamanho; i++){																			/*Este ciclo percorre a matriz e verifica o número de voos que sai de i para k, caso o número de voos*/
		for (k = 0; k < tamanho; k++){																		/*seja maior que o máximo guarda-se o maior número de voos na variável max e o aeroporto de ida i e o*/
			if(matriz[i][k].n_voos > max){																	/*aeroporto de volta k*/
				max = matriz[i][k].n_voos;
				aero1_indice = i;
				aero2_indice = k;
			}
		}
	}
	printf("Voo mais popular %s:%s:%d\n", v_aero[aero1_indice].id, v_aero[aero2_indice].id, max);
}

void executa_C(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que encerra um aeroporto*/
	int i, j, k, tamanho;
	char aero_1[4];

	scanf("%s", aero_1);																			

	tamanho = num_aero + 1;
	for(i = 0; i < tamanho; i++){
		if(strcmp(v_aero[i].id, aero_1) == 0)
			break;
	}
	if(i == tamanho)
		printf("*Aeroporto %s inexistente\n", aero_1);
	else{
		v_aero[i].estado = 0;																				/*Põe o estado de um aeroporto a 0 e vai percorrer na matriz todos*/
		for(k = 0; k < tamanho; k++){																		/*os voos correspondentes a esse aeroporto e metê-los a 0*/
			for(j = 0; j < tamanho; j++){
				if(k == i)
					matriz[k][j].n_voos = 0;								
				else
					matriz[k][i].n_voos = 0;
			}
		}
	}
}

void executa_O(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que reabre um aeroporto*/
	int i, j, tamanho;
	char aero_1[4];

	scanf("%s", aero_1);

	tamanho = num_aero + 1;
	for(i = 0; i < tamanho; i++){
		if (strcmp(v_aero[i].id, aero_1) == 0)
			break;
	}
	if(i == tamanho)																						/*Caso o id não se encontre no vetor auxiliar é porque não existe*/
		printf("*Aeroporto %s inexistente", aero_1);
	else{
		v_aero[i].estado = 1;
		matriz[i][i].a1.estado = 1;
		matriz[i][i].a2.estado = 1;
		for(j = 0; j < tamanho; j++){
			matriz[i][j].n_voos = 0;
			matriz[j][i].n_voos = 0;																		/*Percorre a matriz e mete todos os voos a 0*/
		}
	}
}

void executa_L(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){									/*Função que imprime os aeroportos e seus voos em diferentes formas*/
	int i, j, l, n_in = 0, n_out = 0, command = 0, tamanho = 0, soma_voos = 0;
	aeroporto novo_vetor[MAXAERO];
	char aux[4];
	int h[MAXAERO] = {0};

	scanf("%d", &command);
	if (command == 0){																						/*L 0*/
		for(i = 0; i < num_aero; i++){																	
			n_out = 0;																						
			n_in = 0;																						
			for(j = 0; j < num_aero; j++){																	/*Este ciclo percorre a matriz calculando o número de voos ida e volta e*/
				n_out += matriz[i][j].n_voos;																/*após cada iteração do ciclo imprime o respetivo id, a capacidade máxima*/
				n_in += matriz[j][i].n_voos;																/*e número de voos do aeroporto i*/
			}
			printf("%s:%d:%d:%d\n", v_aero[i].id, v_aero[i].max_capac, n_out, n_in);
		}
	}
	else if(command == 1){																					/*L 1*/
		tamanho = num_aero + 1;
		for(i = 0; i < tamanho; i++){																		/*Criei um vetor auxiliar(novo_vetor) do vetor auxiliar da matriz e copiei os id dos*/
			strcpy(novo_vetor[i].id, v_aero[i].id);															/*aeroportos do vetor auxiliar da matriz para esse vetor novo_vetor e aí*/	
		}																									/*poder ordenar os id's dos aeroportos por ordem alfabética*/
		for(i = 0; i < tamanho; i++){
			for(j = i+1; j < tamanho; j++){
				if(strcmp(novo_vetor[i].id, novo_vetor[j].id) > 0){
					strcpy(aux, novo_vetor[i].id);
					strcpy(novo_vetor[i].id, novo_vetor[j].id);
					strcpy(novo_vetor[j].id, aux);
				}
			}
		}
		for(i = 1; i < tamanho; i++){																		/*Este ciclo vai percorrer esse novo_vetor e o vetor auxiliar da matriz e quando*/
			for(l = 0; l < tamanho; l++){																	/*for igual o id do aeroporto do novo_vetor com o do vetor auxiliar da matriz calcula*/
				if(strcmp(novo_vetor[i].id, v_aero[l].id) == 0){											/*o número de voos de ida e volta, sendo que este vetor auxiliar permite imprimir os*/
					n_in = 0;																				/*aeroportos de ordem alfabética mas todas as outras informações relativas aos aeroportos*/
					n_out = 0;																				/*encontram-se na matriz e no vetor auxiliar permitindo manter a mesma estrutura da matriz*/
					for(j = 0; j < tamanho; j++){															/*e do seu vetor auxiliar*/
						n_in += matriz[j][l].n_voos;
						n_out += matriz[l][j].n_voos;
						}
					printf("%s:%d:%d:%d\n", novo_vetor[i].id, v_aero[l].max_capac, n_out, n_in);
					}
				}		
			}
		}
	else{																									/*L 2*/
		for(i = 0; i < num_aero; i++){																		
			soma_voos = 0;																					/*Criei um vetor auxiliar h[] que contivesse MAXAERO posições e inicializei-o com todas*/
			for(j = 0; j < num_aero; j++){																	/*as posições a 0*/
				soma_voos += matriz[i][j].n_voos;
				soma_voos += matriz[j][i].n_voos;
			}																								/*Este ciclo percorre a matriz e calcula o número de voos de ida e volta de cada aeroporto*/
			h[soma_voos]++;																					/*atribuindo como índice do vetor a soma dos voos e incrementando ao valor do vetor nesse índice*/
		}																									
		for(i = 0; i < MAXAERO; i++){																		/*Este ciclo percorre o vetor auxiliar h[] e imprime o número de voos i e o número de aeroportos*/
			if(h[i] > 0)																					/*que contêm esse número de voos i*/
				printf("%d:%d\n", i, h[i]);
		}
	}
}

void executa_X(aeroporto v_aero[], voo matriz[][MAXAERO], int num_aero){
	int i, j, numero_voos = 0, tamanho;

	tamanho = num_aero + 1;																					/*Este ciclo percorre a matriz e soma o número de voos de todos os aeroportos*/
	for(i = 0; i < tamanho; i++){
		for(j = 0; j < tamanho; j++)
			numero_voos += matriz[i][j].n_voos;
	}
	printf("%d:%d\n",numero_voos, num_aero);
}

