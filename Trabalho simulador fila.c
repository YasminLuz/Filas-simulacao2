#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define TAM 10

typedef struct clientes{ //quem compoe a fila
	short int id;
	int valor;
	short int op;//operacao 1-saque; 2-pagamento; 3-deposito; 
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
}


void inicia_filas(filas *f){ //inicia cabeça da lista
	int i;

		for(i = 0; i < TAM; i++){
			f[i].ini = NULL;
			f[i].fim = NULL;
		}
}


cliente randA(cliente pessoa){//gera adultos

	int randomid = 0, randval = 0, randop = 0, randreac = 0;
	
	srand(time(NULL));

    randomid = 16 + (rand()%43) ;//faixa entre 16 e 59 anos
    pessoa.id = randomid;
//    printf("\n\nGERA ADULTO %d", randomid);
     
    randval = 50 + (rand()%5000); 
    pessoa.valor = randval;
//    printf("\n\nVALOR ADULTO %d", randval);
	 
    randop = 1 + (rand()%3);      
	pessoa.op = randop;	 
//	printf("\nOP ADULTO %d", randop);
	pessoa.reacao = "(^_^)";
	
	return pessoa;
}


cliente randP(cliente pessoa){//gera 60+

	int randomid = 0, randval = 0, randop = 0, randreac = 0;
	
	srand(time(NULL));
	
    randomid = 60 + (rand()%30);  // x = valor_minimo + rand() % ( valor_maximo - valor_minimo ) ;
    pessoa.id = randomid;
//    printf("\n\nGERA IDOSO %d", random);
     
    randval = 50 + (rand()%5000); 
    pessoa.valor = randval;
//    printf("\n\nVALOR IDOSO %d", randval);
	
    randop = 1 + (rand()%3); 
	pessoa.op = randop;	 
//		printf("\n OPERA IDOS %d", pessoa.op);
	pessoa.reacao = "(^_^)";
	
	return pessoa;
}


int inserirfim (cliente pessoa, filas *fn){ //insere na fila
	int aux = 0;
	
//	printf("\nENTRADA %d", pessoa.id);
	
	elem  *no = (elem * ) malloc(sizeof(elem));
	if(!no) return 0;
	
	no->persona = pessoa;
	no->prox = NULL;
	
	srand(time(NULL));
	
    //distribuicao inicial nas filas
    if((pessoa.valor < 1000) && ((pessoa.id > 15) && (pessoa.id < 60))){// 5 primeiras posicoes para fila caixa eletronico

			aux = rand()%4; //posicao escolhida randomicamente de 0-4

			if(fn[aux].fim == NULL){ //procura por fila vazia
				fn[aux].ini = no;
				fn[aux].fim = no;
					
			}else{
				fn[aux].fim->prox = no;
				fn[aux].fim = no; 	
			}
			
		return 1;
			   
	}else if((pessoa.valor > 1000) && ((pessoa.id > 15) && (pessoa.id < 60))){ //fila caixa normal
			
			aux= 5 + (rand()%4);

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


int inserirprioridade (cliente pessoa, filas *fn){ //insere na fila
	int aux = 0;

	
	elem  *no = (elem *) malloc(sizeof(elem));
	if(!no) return 0; //printf("cheio");
	
//	printf("\nENTRADA %d", pessoa.id);
	
	no->persona = pessoa;
	no->prox = NULL;
	
	srand(time(NULL));
	
    //distribuicao inicial nas filas
    if((pessoa.valor < 1000)&& (pessoa.id > 59)){// 5 primeiras posicoes para fila caixa eletronico

			aux = rand()%4; 
			
			if(fn[aux].fim == NULL){ //procura por fila vazia
				fn[aux].ini = no;
				fn[aux].fim = no;
					
			} else{
				filas tmp[TAM], ultimo[TAM];
				   				
				tmp[aux].ini = fn[aux].ini;
				fn[aux].ini= no;
				fn[aux].ini->prox = tmp[aux].ini;
				   
				ultimo[aux].ini = tmp[aux].ini;   //caso nao entre no laco
				while(tmp[aux].ini != NULL){
				   	ultimo[aux].ini = tmp[aux].ini;
	//			   	printf("\n ULTIMO %d", ultimo[aux].ini->persona.id);
				   	tmp[aux].ini = tmp[aux].ini->prox;
				}
				   
				fn[aux].fim = ultimo[aux].ini;
			}
						
		return 1;
			   
	}else if((pessoa.valor > 1000)&& (pessoa.id > 59)){ // 5 ultimas posicoes para fila caixa normal
			
			aux = 5 + (rand()%4);
			
			if(fn[aux].fim == NULL){
				fn[aux].ini = no;
				fn[aux].fim = no;
				
			} else {
				filas tmp[TAM], ultimo[TAM];
				   				
				tmp[aux].ini = fn[aux].ini;
			    fn[aux].ini= no;
			    fn[aux].ini->prox = tmp[aux].ini;
//			    fn[aux].fim->prox = tmp[aux].ini;
				
				ultimo[aux].ini = tmp[aux].ini;   
			    while(tmp[aux].ini != NULL){
				   	ultimo[aux].ini = tmp[aux].ini;
				   	tmp[aux].ini = tmp[aux].ini->prox;
				}
				   
				fn[aux].fim = ultimo[aux].ini;
			}
			
		return 1;
	}	
}


void liberarcliente(filas *fn, int pos){

		elem *no =  (elem *) malloc(sizeof(elem));
		
		if(fn[pos].ini == NULL) return ;//nada na posicao
		
		no = fn[pos].ini;
		fn[pos].ini = fn[pos].ini->prox;
		
		if(fn[pos].ini == NULL)
			fn[pos].fim = NULL;
			
		free(no);
}


int tempo_operacao(filas *fn, char expressoes[][6]){
	
	int aux2 = 0;
//	clock_t t_ini, t_fim;
//	float tempo;
//	filas tmp[TAM];
//	inicia_filas(tmp);
	filas tmp[TAM];int aux, auxt = 0;
			
			srand(time(NULL));
	
			do{
				aux = rand()%9;
			}while(fn[aux].ini == NULL); //enquanto o randomico nao selecionar posicao vazia
			
			tmp[aux].ini = fn[aux].ini;
			
			while(tmp[aux].ini != NULL){
				auxt = 1 + (rand()%2);
				tmp[aux].ini->persona.reacao = expressoes[auxt];
				tmp[aux].ini = tmp[aux].ini->prox;
			}
	
	printf("\n\nVALOR RAND %d", aux);
	printf("\nOPERACAO ENTRADA %d", fn[aux].ini->persona.op);
	
		switch(fn[aux].ini->persona.op){
			
			case 1:{//saque

							if(fn[aux].ini->persona.id > 15 && fn[aux].ini->persona.id < 60)
						    	sleep(4);
							else
						    	sleep(5.2);
//				    	
				        liberarcliente(fn, aux);
				        
				        printf("\a"); //emitir bip ao liberar
				
					break;
				   }
				 
				   
			case 2:{//pagamento  
					  if(fn[aux].ini->persona.id > 15 && fn[aux].ini->persona.id < 60)
				        sleep(5);
				      else
				        sleep(5.5);

				       liberarcliente(fn, aux);
				       
				       printf("\a");
				       
					break;
				   }	
			
			
			case 3:{//deposito
					 
					 if(fn[aux].ini->persona.id > 15 && fn[aux].ini->persona.id < 60)
				       sleep(4);
				     else
				       sleep(5.2);

				     liberarcliente(fn, aux);
				       
				     printf("\a");
				       
					break;
				   }
			
			default: return 0;	   
		}

	return 1;
}


void exibir_tela(filas *fn, cliente pessoa, int contcliente, long int *totaldep, long int *totalpag, long int *totalsaque){

	int mediaespera = 0;
	
	if(pessoa.op == 1)
		*totalsaque -=  pessoa.valor;
	else if	(pessoa.op == 2)
		*totaldep += pessoa.valor;
	else 
	   	*totalpag -= pessoa.valor;
	    
	printf("         ========================================================== \n");    
	printf("         |               SIMULADOR DE FILAS DE BANCO               |\n");
	printf("         ==========================================================|\n");
	printf("         |              Eletronico 0 - 4 | Caixa 5- 9              |\n");
	printf("                                                                    \n");
	printf("          Quantidade total de clientes: %i                          \n", contcliente);
	printf("          Saques R$ %ld                                             \n", *totalsaque);
	printf("          Depositos R$ %ld                                          \n", *totaldep);
	printf("          Pagamentos R$ %ld                                         \n", *totalpag);
	printf("          Media de espera: %d                                       \n", mediaespera);
	printf("         |=========================================================|\n");
	
}


void exibir_filas(filas *fn, filas *fila, int i){
//	system("color 03");
	
		fila[i].ini = fn[i].ini;

			printf("\n\n\t  |[%d]:", i);

				while(fila[i].ini != NULL){
//					printf("\t%d",fila[i].ini->persona.id);
					printf("\t %s",fila[i].ini->persona.reacao);
					fila[i].ini = fila[i].ini->prox;
				}

}


 void limpar(){
 	 	
	#ifdef __unix 
		sleep(2); 
		system("clear");
	#elif _WIN32
		sleep(2); 
		system("cls");
	#endif
}


int main(void){
	int i = 0,  contaux = 0; 

	cliente pessoa1, pessoa2;
	
	filas fn[TAM], fila[TAM];
	
	for(i = 0; i < TAM; i++){ //cria  espaco nas posicoes
		fn[i].ini= (elem *) malloc (sizeof(elem));
		fn[i].fim= (elem *) malloc (sizeof(elem));
		fila[i].ini = (elem *) malloc(sizeof(elem));
		fila[i].fim = (elem *) malloc(sizeof(elem));
	}
	
	char expressoes[3][6] = {"(^_^)", "(-_-)", "(>_<)"}; //o(>< )o
	
//	printf(" %s", expressoes[2]);
	sleep(2);
	
	
	inicia_filas(fn);
	inicia_filas(fila);
	inicia_cliente(pessoa1);
	inicia_cliente(pessoa2);
	
	long int aux1 = 0, aux2 = 0, aux3 = 0;
	
	int contcliente = 0;
	int mediaespera = 0;
	long int *totaldep , *totalpag , *totalsaque ;
	
	totaldep = &aux1, totalpag = &aux2, totalsaque = &aux3;
	
	
	do{
		/*pessoa adulta*/
		pessoa1 = randA(pessoa1);	
	 	if (inserirfim(pessoa1, fn) == 1) contcliente++;
		contaux++;
		
		limpar();
		
		exibir_tela(fn, pessoa1, contcliente, totaldep, totalpag, totalsaque);
		
		/*imprimir filas*/
	 	for(i = 0; i < TAM; i++)
			exibir_filas(fn, fila, i);
			
			
	 	/*pessoa idosa*/
		pessoa2 = randP(pessoa2); 	
	 	if (inserirprioridade(pessoa2, fn) == 1) contcliente++;
	 	contaux++;
	 	
		limpar();
		
		exibir_tela(fn, pessoa2, contcliente, totaldep, totalpag, totalsaque);

		/*imprimir filas*/
		for(i = 0; i < TAM; i++)
			exibir_filas(fn, fila, i);
		
		
		if(contaux == 2){
			tempo_operacao(fn, expressoes);
			contcliente--;
			contaux = 0;
		}


	}while (contcliente > 0);
	
	
	return 0;
}
