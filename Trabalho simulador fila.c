#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAM 10
#define MAX 100

typedef struct clientes{ //quem compoe a fila
	int id;
	int valor;
	int op;//operacao 1-saque; 2-deposito; 3-pagamento; 
	char *reacao;
}cliente;


typedef struct filas10{ //cabeça da lista que indica inicio e fim
	struct elemento *ini;
	struct elemento *fim;
}filas;


typedef struct elemento{ // lista que abriga cliente e proximos
	cliente persona;
	struct elemento *prox;
}elem;


void inicia_cliente(cliente pessoa){
	pessoa.id = 0;
	pessoa.valor = 0;
	pessoa.op = 0;
	pessoa.reacao = "(^_^)";
//	pessoa.prox = NULL;
}

filas* inicia_filas(filas *f){ //inicia cabeça da lista
	int i;
	
	if(f != NULL){
		for(i = 0; i < TAM; i++){
			f[i].ini = NULL;
			f[i].fim = NULL;
		}
	}
	
	return f;
}

cliente randA(cliente pessoa){//gera adultos

	int i, random, randval, randop, randreac;
	
	srand(time(NULL));
	for(i = 0; i <6;i++)
    random = 16 + (rand() % 43) ;//faixa entre 16 e 59 anos
    pessoa.id = random;
    printf("\n\nGERA ADULTO %d", random);
     
    randval = 50 + (rand() % 5000); 
    pessoa.valor = randval;
	 
    randop = 1 + (rand() % 3);      
	pessoa.op = randop;	 
	
	pessoa.reacao = "(^_^)";
	
	return pessoa;
}

cliente randP(cliente pessoa){//gera 60+

	int i, random, randval, randop, randreac;
	
	srand(time(NULL));
	
    random = 60 + (rand() % 30);  // x = valor_minimo + rand() % ( valor_maximo - valor_minimo ) ;
    pessoa.id = random;
    printf("\n\nGERA IDOSO %d", random);
     
    randval = 50 + (rand() % 5000); 
    pessoa.valor = randval;
	
    randop = 1 + (rand() % 3); 
	pessoa.op = randop;	 
	
	pessoa.reacao = "(^_^)";
	
	return pessoa;
}



int inserirfim (cliente pessoa, filas *fn){ //insere na fila
	int aux;
	
	printf("\nENTRADA %d", pessoa.id);
	
	elem  *no = (elem * ) malloc(sizeof(elem));
	if(!no) return 0;
	
	no->persona = pessoa;
	no->prox = NULL;
	
	srand(time(NULL));
	
    //distribuicao inicial nas filas
    if((pessoa.valor < 1000) && (pessoa.id > 15 && pessoa.id < 60)){// 5 primeiras posicoes para fila caixa eletronico

			aux= rand()% 4; //posicao escolhida randomicamente de 0-4
//			printf("AUX %d ", aux);
			if(fn[aux].fim == NULL){ //procura por fila vazia
				fn[aux].ini = no;
				fn[aux].fim = no;
					
			}else{
				fn[aux].fim->prox = no;
				fn[aux].fim = no; 	  
			}

		return 1;
			   
	}else if((pessoa.valor > 1000) && (pessoa.id > 15 && pessoa.id < 60)){ //fila caixa normal
			
			aux= 5 + rand()%4;
//			printf("AUX2 norm %d ", aux);
			if(fn[aux].fim == NULL){
				fn[aux].ini = no;
				fn[aux].fim = no;
				
			} else {
				fn[aux].fim->prox = no;
				fn[aux].fim = no; 
			}

		return 1;
	}	
}

int inserirpriori (cliente pessoa, filas *fn){ //insere na fila
	int i, aux;
	
//	if (!fn) return 0;
//	if (!fe) return 0;
	
	elem  *no = (elem *) malloc(sizeof(elem));
	if(!no) return 0;
	
//	for(i = 0; i < TAM; i++){ //auxiliares
//		tmp[i].ini= (elem *) malloc(sizeof(elem));
//		tmp[i].fim = (elem *) malloc(sizeof(elem));
//		tmp2[i].ini= (elem *) malloc(sizeof(elem));
//		tmp2[i].fim = (elem *) malloc(sizeof(elem));
//	}
	
	no->persona = pessoa;
	no->prox = NULL;
	
	srand(time(NULL));
	
    //distribuicao inicial nas filas
    if((pessoa.valor < 1000)&& (pessoa.id > 59)){// 5 primeiras posicoes para fila caixa eletronico

			aux= rand()% 4; 
			
			if(fn[aux].fim == NULL){ //procura por fila vazia
					fn[aux].ini = no;
					fn[aux].fim = no;

			} else{
				   filas tmp[TAM];
				
				   tmp[aux].ini = fn[aux].ini;
				   fn[aux].ini= no;
				   fn[aux].ini->prox = tmp[aux].ini;
			}

		return 1;
			   
	}else if((pessoa.valor > 1000)&& (pessoa.id > 59)){ // 5 ultimas posicoes para fila caixa normal
			
			aux = 5 + (rand()%(TAM-1));
			
			if(fn[i].fim == NULL){
				fn[aux].ini = no;
				fn[aux].fim = no;
				
			} else {
				   filas tmp[TAM];
				
				   tmp[aux].ini = fn[aux].ini;
				   fn[aux].ini= no;
				   fn[aux].ini->prox = tmp[aux].ini;
			}
			
		return 1;
	}	
}


void liberarcliente(filas *f){
	int i;
	
	if (f != NULL){
		elem *no;
		while(f[i].ini !=NULL){
			no = f[i].ini;
			f[i].ini = f[i].ini->prox;
			free(no);
		}
		free(f);
	}
}


int tempo_operacao(cliente pessoa, filas *fn){
	
	int i;
	
	for (i = 0; i < TAM; i++){
		
		switch(fn[i].ini->persona.op){
			
			case 1:{
				     if(fn[i].ini->persona.id > 15 && fn[i].ini->persona.id < 60)
				       sleep(2);
				     else
				       sleep(2.6);
				       
				       liberarcliente(fn);
				       printf("\a"); //emitir bip ao liberar
				
					break;
				   }
				 
				   
			case 2:{
					 if(fn[i].ini->persona.id > 15 && fn[i].ini->persona.id < 60)
				       sleep(2);
				     else
				       sleep(2.6);
				       
				       liberarcliente(fn);
				       
				       printf("\a");
				       
					break;
				   }	
			
			
			case 3:{
				     if(fn[i].ini->persona.id > 15 && fn[i].ini->persona.id < 60)
				       sleep(4);
				     else
				       sleep(5.2);
				       
				       liberarcliente(fn);
				       
				       printf("\a");
				       
					break;
				   }
			
			default: return 0;	   
		}
	}
	return 1;
}


void transformar(filas *fn, int contcliente, int i){
	
	int y = 0;
	
	filas novo[TAM]; 
	novo[i].ini = (elem *) malloc(sizeof(elem)); 
	novo[i].ini = fn[i].ini;  
	
	int *vet = (int*) malloc(contcliente * sizeof(int));//vetor criado com tamanho da capacidade da estrutura auxiliar
	
	     while (novo[i].ini != NULL) {
	     	   vet[y] = novo[i].ini->persona.id;
	           printf("     %d ", vet[y]);
	           y++;
	           novo[i].ini = novo[i].ini->prox;
	     }
	     printf("\n");
	     
}


void exibir_tela(filas *fn,int contcliente, int i){
//	int i;
	int mediaespera = 0, totalsaque = 0, totaldep = 0, totalpag = 0;
	
//	if(fn[i].ini->persona.op == 1)
//		totalsaque -=  fn[i].ini->persona.valor;
//	else if	(fn[i].ini->persona.op == 2)
//		totaldep += fn[i].ini->persona.valor;
//	else 
//	    totalpag -= fn[i].ini->persona.valor;	
		
	
	printf("                        SIMULADOR DE FILAS DE BANCO                                 \n\n");
	printf("         __________________________________________________________\n");
	printf("         |                                                        |\n");
	printf("         | Quantidade de clientes: %d                              |\n", contcliente);
	printf("         | Saques R$ %d                                            |\n", totalsaque);
	printf("         | Depositos R$ %d                                         |\n", totaldep);
	printf("         | Pagamentos R$ %d                                        |\n", totalpag);
	printf("         | Media de espera: %d                                     |\n", mediaespera);
	printf("         |________________________________________________________|\n");
	
	filas fila[TAM];//,normal[TAM];
	
//	eletro[i].ini = (elem *) malloc(sizeof(elem));
//	eletro[i].ini = fe[i].ini;
	
	fila[i].ini = (elem *) malloc(sizeof(elem));
	fila[i].ini = fn[i].ini;
	
	//transformar(fn,contcliente, i);
	
//	printf("fila eletronica\n");
//	while(eletro[i].ini != NULL){
//		puts(eletro[i].ini->persona.reacao);
//		eletro[i].ini = eletro[i].ini->prox;
//	}
	
	printf("\nfila eletronica e normal");
	while(fila[i].ini != NULL){
		printf("\n|[%d]: %d",i, fila[i].ini->persona.id);
		puts(fila[i].ini->persona.reacao);
		fila[i].ini = fila[i].ini->prox;
	}
	
}

 void limpar(){
 	 	
	#ifdef __unix 
		sleep(1); 
		system("clear");
	#elif _WIN32
		sleep(1); 
		system("cls");
	#endif
	
}

int main(void){
	int i, aux;

	cliente pessoa;
//	pessoa = (cliente *) malloc(sizeof(cliente));
	
	filas fn[TAM];// fe[TAM]; //fila normal e fila eletronica
	
	for(i = 0; i < TAM; i++){ //cria  espaco nas posicoes
		fn[i].ini= (elem *) malloc (sizeof(elem));
		fn[i].fim= (elem *) malloc (sizeof(elem));
//		fe[i].ini= (elem *) malloc (sizeof(elem));
//		fe[i].fim= (elem *) malloc (sizeof(elem));
	}
	
	
	inicia_filas(fn);
//	inicia_filas(fe);
	inicia_cliente(pessoa);
	
	int contcliente = 0;
	
	
	do{
		pessoa = randA(pessoa);	
	 	inserirfim(pessoa, fn);
	 	contcliente++;

//		for(i = 0; i < TAM; i++){
//			
//			limpar();
//            marcacao(fn, i);
////			if(fn[i].ini != NULL)
//	 			exibir_tela(fn, contcliente, i);
//	 		else{
//	 			exibir_tela(fn, contcliente, i);
//	 			printf("\n\n  | ");
//	 			continue;
//			 }	
//	 	}
	 	inserirpriori(randP(pessoa), fn);
		contcliente++;
	 		
	 	for( i = 0; i < TAM; i++){
			limpar();
			exibir_tela(fn, contcliente, i);
		}
//        exibir_tela(*fn);



//		printf("\n\nPressione 0 para sair...\n");
//		scanf("%i", &press);
	}while (contcliente != 20);
	
	
	return 0;
}
