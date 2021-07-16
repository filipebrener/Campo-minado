#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct sCampo{
	int cont_bandeiras;
	int **oculto;
	char **visivel;
}Campo;

typedef struct sJogador{
	char nome[45];
	clock_t tempo;
	int linha,coluna,bomba;
	int GG;
	int modo;
}Jogador;

typedef struct sRecorde{
	Jogador normal[5];
	Jogador personalizado[5];
	int cont_p;
	int cont_n;
}Recorde;


imprime_tabuleiro_vizivel(Campo c,Jogador x){
	int i,j;
	printf("-----------------------------------------\n");
	printf("             CAMPO MINADO\n");
	printf("-----------------------------------------\n\n");
	printf("       ");
	for(i=1;i<=x.linha;i++){
		printf("%d ",i);
	}
	printf("\n");
	for(i=1;i<=x.linha;i++){
		printf("%d      ",i);
		for(j=1;j<=x.coluna;j++){
			printf("%c ",c.visivel[i][j]);
		}
		printf("\n");
	}
	printf("\nBombas marcadas %d/10\n\n",c.cont_bandeiras);
}

Campo iniciar_tabuleiro_personalizado(Campo c,Jogador x){
	int i,j,a,b;

	c.oculto = (int **) calloc(x.linha+2,sizeof(int*));
	
	for(i=0;i<=x.linha+2;i++){
		c.oculto[i] = (int *) calloc(x.coluna+2,sizeof(int));
	}
	
	c.visivel = (char **) malloc((x.linha+2)*sizeof(char*));

	for(i=0;i<=x.linha+2;i++){
		c.visivel[i] = (char *) malloc((x.coluna+2)*sizeof(char));
	}
	
	for(i=1;i<=x.linha;i++){
		for(j=1;j<=x.coluna;j++){
			c.visivel[i][j] = '#';
		}
	}

	srand(time(NULL));					// função para que os numeros gerados aleatoriamente não sejam o mesmo a cada execução
	for(i=0;i<x.bomba;i++){
		a = (rand() % x.linha );
		if(a == 0){
			a++;
		}
		b = (rand() % x.coluna );
		if(b == 0){ 
			b++;
		}
		if(c.oculto[a][b] == 9){      // estrutura de desisão para que não seja alocado uma mina onde ja tenha uma anteriormente
			i--;                      // se ja houver uma bomba na posição i-- executa o for com o mesmo valor de 'i' novamente
		} else {
			c.oculto[a][b] = 9;
		}
	}	
	return c;
}


void imprime_final(Campo c,Jogador x){											// função mostra as minas ao finalizar o jogo
	int i,j;
	printf("-----------------------------------------\n");
	printf("             CAMPO MINADO\n");
	printf("-----------------------------------------\n\n");
	printf("       ");
	for(i=1;i<x.coluna+1;i++){
		printf("%d ",i);
	}
	printf("\n");
	for(i=1;i<x.linha+1;i++){
		printf("%d      ",i);
		for(j=1;j<x.coluna+1;j++){
			if(c.oculto[i][j] > 8){
				printf("@ ");
			} else {
				printf("%c ",c.visivel[i][j]);
			}
		}
		printf("\n");
	}
}

int Verifica_mina(int c){				             				// função que verifica se a jogada foi em cima de uma mina
	if(c > 8){
		return 1;
	} else {
		return 0;
	}
}

Campo jogada(Campo c, int i, int j){								// função que executa a jogada

	if(c.visivel[i][j] == 'B'){
		return c;
	}
	
	if (c.oculto[i][j] > 0 && c.oculto[i][j] < 9){                // estrutura de desisão para validar as posições escolhidas pelo usuario
		if(c.oculto[i][j] == 1){
			c.visivel[i][j] = '1';                                  // atribui o valor encontrado no campo oculto ao campo visivel 
		}
		if(c.oculto[i][j] == 2){
			c.visivel[i][j] = '2';                                  // atribui o valor encontrado no campo oculto ao campo visivel
		}
		if(c.oculto[i][j] == 3){
			c.visivel[i][j] = '3';                                  // atribui o valor encontrado no campo oculto ao campo visivel
		}
		if(c.oculto[i][j] == 4){
			c.visivel[i][j] = '4';                                  // atribui o valor encontrado no campo oculto ao campo visivel
		}
		if(c.oculto[i][j] == 5){
			c.visivel[i][j] = '5';                                  // atribui o valor encontrado no campo oculto ao campo visivel
		}
		if(c.oculto[i][j] == 6){
			c.visivel[i][j] = '6';                                  // atribui o valor encontrado no campo oculto ao campo visivel
		}
		if(c.oculto[i][j] == 7){
			c.visivel[i][j] = '7';                                  // atribui o valor encontrado no campo oculto ao campo visivel
		}
		if(c.oculto[i][j] == 8){
			c.visivel[i][j] = '8';                                  // atribui o valor encontrado no campo oculto ao campo visivel
		}
		return c;
	} else  if (c.oculto[i][j] == 0){                  // quando a casa selecionada for '0' no tabuleiro oculto o tabuleiro visivel deve abrir todas as casas 
			c.visivel[i][j] = '-';                     // adjacentes até encontrar um numero
			if(c.visivel[i-1][j-1] == '#'){
				c = jogada(c,i-1,j-1);                 // chamada da função na casa vizinha
			}
			if(c.visivel[i-1][j] == '#'){
				c = jogada(c,i-1,j);				   // chamada da função na casa vizinha
			}
			if(c.visivel[i-1][j+1] == '#'){
				c = jogada(c,i-1,j+1);                 // chamada da função na casa vizinha
			}
			if(c.visivel[i][j-1] == '#'){
				c = jogada(c,i,j-1);                 // chamada da função na casa vizinha
			}
			if(c.visivel[i][j+1] == '#'){
				c = jogada(c,i,j+1);                 // chamada da função na casa vizinha
			}
			if(c.visivel[i+1][j-1] == '#'){
				c = jogada(c,i+1,j-1);                 // chamada da função na casa vizinha
			}
			if(c.visivel[i+1][j] == '#'){
				c = jogada(c,i+1,j);                 // chamada da função na casa vizinha
			}
			if(c.visivel[i+1][j+1] == '#'){
				c = jogada(c,i+1,j+1);                 // chamada da função na casa vizinha
			}
		}
		return c;
}

Campo colocar_bandeira(Campo c){                                 // função para colocar as bandeiras no campo
	int i,j;
	printf("Digite a linha que deseja colocar ou remover a bandeira: ");
	scanf("%d",&i);
	printf("Digite a coluna que deseja colocar ou remover a bandeira: ");
	scanf("%d",&j);
	if(c.visivel[i][j] == '#'){
		c.visivel[i][j] = 'B';
		return c;	
	}
	if (c.visivel[i][j] == 'B'){
		c.visivel[i][j] = '#';
		return c;
	}
	return c;
}

Campo cont_bandeiras(Campo c,Jogador x){                                  // função que percorre o campo minado visível e conta quantas bandeiras foram colocadas pelo usuário
	int i,j,cont=0;
	for(i=1;i<=x.linha+1;i++){
		for(j=1;j<=x.coluna+1;j++){
			if(c.visivel[i][j] == 'B'){
				cont++;
			}
		}
	}
	c.cont_bandeiras = cont;
	return c;
}

int ganhou(Campo c,Jogador x){												// função para conferir se o jogador ganhou
	int i,j,cont=0;
	for(i=1;i<=x.linha+1;i++){
		for(j=1;j<=x.coluna+1;j++){
			if(c.visivel[i][j] == '#'){
				cont++;
			}
		}
	}   
	return cont;
}																	


Campo Gerar_numero(Campo c,Jogador x){                                        // função para gerar os numeros adjacentes as bombas
	int i,j;
	for(i=1;i<x.linha;i++){												// estrutura de repetição para percorrer toda a matriz
		for(j=1;j<x.coluna;j++){
			
			if(c.oculto[i][j] > 8){									// estrutura de desisão para que quando encontrado uma bomba seja somado 1 em suas posições adjacentes
				c.oculto[i-1][j-1]++;
				c.oculto[i-1][j]++;
				c.oculto[i-1][j+1]++;
				c.oculto[i][j-1]++;
				c.oculto[i][j+1]++;
				c.oculto[i+1][j-1]++;
				c.oculto[i+1][j]++;
				c.oculto[i+1][j+1]++;
			}
				
		}
	}
	return c;
}

Jogador registrar_jogador(Jogador x, int z){
	fflush(stdin);
	printf("Digite seu nome: ");
	gets(x.nome);
	if (z == 0){
		printf("Digite o numero de Linhas: ");
		scanf("%d",&x.linha);
		printf("Digite o numero de Colunas: ");
		scanf("%d",&x.coluna);
		printf("Digite o numero de bombas: ");
		scanf("%d",&x.bomba);
		x.modo = 2;	
	} else {
		x.bomba = 10;
		x.linha = 9;
		x.coluna = 9;
		x.modo = 1;
	}
	return x;
}

void imprime_menu(){	
	printf("-----------------------------------------\n");
	printf("             CAMPO MINADO\n");
	printf("-----------------------------------------\n\n");
	printf("                 MENU\n");
	printf("1 - Novo Jogo\n");
	printf("2 - Personalizar Tabuleiro\n");
	printf("3 - Sair\n\n");
	printf("Digite ume opcao: ");
}

void desaloca_tabuleiro(Campo c){
	free(c.oculto);
	free(c.visivel);	
}

	Recorde receber(Recorde r){                                 // leitura dos recordes
	FILE *file;
	char padrao[6],personalizado[13];
	int i,aux;
	file = fopen("Recordes.txt","r");
	if(file == NULL){
		file = fopen("Recordes.txt","w");
		fprintf(file,"Padrao 0\n");
		fprintf(file,"Personalizado 0\n");
		for(i=0;i<5;i++){
			r.cont_n = 0; 
			r.cont_p = 0;	
		}
		fclose(file);
		return r;
	} else {
		fscanf(file,"%s %d\n",&padrao,&r.cont_n);

		for(i=0;i<r.cont_n;i++){
			fscanf(file,"%d %s %d\n",&aux,&r.normal[i].nome,&r.normal[i].tempo);
		}
		fscanf(file,"%s %d\n",&personalizado,&r.cont_p);
			for(i=0;i<r.cont_p;i++){
				fscanf(file,"%d %s %d %d %d %d\n",&aux,&r.personalizado[i].nome,&r.personalizado[i].tempo,&r.personalizado[i].linha,&r.personalizado[i].coluna,&r.personalizado[i].bomba);
				}
	}
	fclose(file);
	return r;
}

Recorde ordenar(Recorde r,Jogador x){
	int aux,i,j;
	Jogador aux2;
	if(x.modo == 1){
		aux = r.cont_n;
		if(aux > 4){
			if(x.tempo < r.normal[4].tempo){
				r.normal[4] = x;
			}
		}
		r.normal[aux] = x;
		r.cont_n++;
		for(i=0;i<=aux;i++){
			for(j=i+1;j<=aux;j++){
				if(r.normal[i].tempo > r.normal[j].tempo){
					aux2 = r.normal[i];
					r.normal[i] = r.normal[j];
					r.normal[j] = aux2;
				}
			}
		}
	} else {
		aux = r.cont_p;
		if(aux > 4){
			if(x.tempo < r.personalizado[4].tempo){
				r.personalizado[4] = x;
			}
		}
		r.personalizado[aux] = x;
		r.cont_p++;
		for(i=0;i<=aux;i++){
			for(j=i+1;j<=aux;j++){
				if(r.personalizado[i].tempo > r.personalizado[j].tempo){
					aux2 = r.personalizado[i];
					r.personalizado[i] = r.personalizado[j];
					r.personalizado[j] = aux2;
				}
			}
		}
	}	
	return r;
}

void Registrar_arquivo(Recorde r){
	FILE *file;
	int i,j;
	file = fopen("Recordes.txt","w");
	fprintf(file,"Padrao %d \n",r.cont_n);
	for(i=0;i<r.cont_n;i++){
		fprintf(file,"%d %s %d \n",i+1,r.normal[i].nome,r.normal[i].tempo);
	}
	fprintf(file,"Personalizado %d\n",r.cont_p);
	for(i=0;i<r.cont_p;i++){
		fprintf(file,"%d %s %d %d %d %d\n",i+1,r.personalizado[i].nome,r.personalizado[i].tempo,r.personalizado[i].linha,r.personalizado[i].coluna,r.personalizado[i].bomba);
	}
	fclose(file);
}

int main(){
	Campo c;
	Jogador x;
	Recorde r;
	r = receber(r);
	int i,j,func;
	do{												// estrutura de repetição para que o programa feche apenas quando o usuario quiser
		system("cls");
		if(func != 5){
			imprime_menu();						
			scanf("%d",&func);                     // leitura da função escolhida pelo usuario
		}
		switch (func){							   // estrutura de desição para executar a função escolhida pelo usuario
	 		case 1:{
	 			x = registrar_jogador(x,1);
	 			func = 5;
	 			break;
			}
			case 2:{
				x = registrar_jogador(x,0);
				func = 5;
				break;
			}
			case 4:{
			 	printf("Obrigado por jogar!\n");
				break;
			}
			case 5:{
				c = iniciar_tabuleiro_personalizado(c,x);
				c = Gerar_numero(c,x);
				x.tempo = clock();
	 			do{
	 				fflush(stdin);
	 				system("cls");
	 				c = cont_bandeiras(c,x);
	 				imprime_tabuleiro_vizivel(c,x);
	 				printf("Digite a linha da jogada (ou -1 para colocar ou remover uma Bandeira): ");
	 				scanf("%d",&i);
	 	 			if(i == -1){
	 					c = colocar_bandeira(c);
					} else {
						printf("Digite a coluna da jogada: ");
						scanf("%d",&j);
						c = jogada(c,i,j);
						printf("depois daqui");
						if(c.visivel[i][j] != 'B'){
							if (Verifica_mina(c.oculto[i][j]) == 1){
							x.GG = 0;
							break;				
							}
						}
					}
				} while(ganhou(c,x) > x.bomba);
				x.tempo = clock()- x.tempo;
				x.tempo = x.tempo/CLOCKS_PER_SEC;
				system("cls");
				imprime_final(c,x);
				printf("O seu tempo foi de %d segundos\n",x.tempo/CLOCKS_PER_SEC);
				if(x.GG != 0){
					printf("\nPARABENS!!!! \nVOCE GANHOU :)\n\n");
					r = ordenar(r,x);
					Registrar_arquivo(r);
				} else {
					printf("VOCE PERDEU :C\n\n");
				}
					printf("Deseja jogar novamente ?\n");
					printf("Digite 1 para sim ou 0 para nao: ");
					scanf("%d",&func);
					if (func == 0){
						func == 4;
					}
				break;
			 }
		}
	}while(func != 3);
	desaloca_tabuleiro(c);
	return 0;
}
