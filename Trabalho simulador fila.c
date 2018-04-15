#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAM 10

typedef struct clientes{ //quem compoe a fila
	short int id;
	int valor;
	short int op;//operacao 1-saque; 2-deposito; 3-pagamento; 
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

filas* inicia_filas(filas *f){ //inicia cabeça da lista
	int i;
	
//	if(f != NULL){
		for(i = 0; i < TAM; i++){
			f[i].ini = NULL;
			f[i].fim = NULL;
		}
//	}
	
	return f;
}

cliente randA(cliente pessoa){//gera adultos

	int randomid = 0, randval = 0, randop = 0, randreac = 0;
	
	srand(time(NULL));
//	for(i = 0; i <6;i++)
    randomid = 16 + (rand()%43) ;//faixa entre 16 e 59 anos
    pessoa.id = randomid;
    printf("\n\nGERA ADULTO %d", randomid);
     
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
	
	pessoa.reacao = "(^_^)";
	
	return pessoa;
}



int inserirfim (cliente pessoa, filas *fn){ //insere na fila
	int aux = 0;
	
	printf("\nENTRADA %d", pessoa.id);
	
	elem  *no = (elem * ) malloc(sizeof(elem));
	if(!no) printf("cheio");//return 0;
	
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

int inserirpriori (cliente pessoa, filas *fn){ //insere na fila
	int aux = 0;

	
	elem  *no = (elem *) malloc(sizeof(elem));
	if(!no) printf("cheio");//return 0;
	
	printf("\nENTRADA %d", pessoa.id);
	
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
//				   fn[aux].fim->prox = tmp[aux].ini;
				   
				   while(tmp[aux].ini != NULL){
				   	ultimo[aux].ini = tmp[aux].ini;
//				   	printf("\n ULTIMO %d", ultimo[aux].ini->persona.id);
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
//				   fn[aux].fim->prox = tmp[aux].ini;
				   
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

		elem *no;
		while(fn[pos].ini !=NULL){
			no = fn[pos].ini;
			fn[pos].ini = fn[pos].ini->prox;
			free(no);
		}
		free(fn);
}


int tempo_operacao(filas *fn){
	
	int aux;
	filas tmp[TAM];
	
//	for (i = 0; i < TAM; i++){
	srand(time(NULL));
	aux = rand()%9;
		
		switch(fn[aux].ini->persona.op){
			
			case 1:{
				     if(fn[aux].ini->persona.id > 15 && fn[aux].ini->persona.id < 60)
				       sleep(2);
				     else
				       sleep(2.6);
				       
				       tmp[aux].ini = fn[aux].ini;
				       fn[aux].ini = fn[aux].ini->prox;
				       
				       liberarcliente(tmp, aux);
				       printf("\a"); //emitir bip ao liberar
				
					break;
				   }
				 
				   
			case 2:{
					 if(fn[aux].ini->persona.id > 15 && fn[aux].ini->persona.id < 60)
				       sleep(2);
				     else
				       sleep(2.6);
				       
				       tmp[aux].ini = fn[aux].ini;
				       fn[aux].ini = fn[aux].ini->prox;
				       
				       liberarcliente(tmp, aux);
				       
				       printf("\a");
				       
					break;
				   }	
			
			
			case 3:{
				     if(fn[aux].ini->persona.id > 15 && fn[aux].ini->persona.id < 60)
				       sleep(4);
				     else
				       sleep(5.2);
				       
				       tmp[aux].ini = fn[aux].ini;
				       fn[aux].ini = fn[aux].ini->prox;
				       
				       liberarcliente(tmp, aux);
				       
				       printf("\a");
				       
					break;
				   }
			
			default: return 0;	   
		}
//	}
	return 1;
}


void exibir_tela(filas *fn, cliente pessoa, short int contcliente, long int *totaldep, long int *totalpag, long int *totalsaque){

	int mediaespera = 0;
	
	if(pessoa.op == 1)
		*totalsaque -=  pessoa.valor;
	else if	(pessoa.op == 2)
		*totaldep += pessoa.valor;
	else 
	   	*totalpag -= pessoa.valor;
	    
	printf("         ========================================================== \n");    
	printf("         |               SIMULADOR DE FILAS DE BANCO               |            ");
	printf("         ==========================================================|\n");
	printf("         |                                                         |\n");
	printf("         | Quantidade de clientes: %d                              |\n", contcliente);
	printf("         | Saques R$ %ld                                            |\n", *totalsaque);
	printf("         | Depositos R$ %ld                                         |\n", *totaldep);
	printf("         | Pagamentos R$ %ld                                        |\n", *totalpag);
	printf("         | Media de espera: %d                                     |\n", mediaespera);
	printf("         |=========================================================|\n");
	
	filas fila[TAM];//,normal[TAM];
	
}


void exibir_filas(filas *fn, filas *fila, int i){
//	system("color 03");
	
	if(fn[i].ini != NULL){
				fila[i].ini = (elem *) malloc(sizeof(elem));
				fila[i].ini = fn[i].ini;
				
		printf("\n\n\t  |[%d]:", i);
		
				while(fila[i].ini != NULL){
					printf("\t%d",fila[i].ini->persona.id);
			//		puts(fila[i].ini->persona.reacao);
					fila[i].ini = fila[i].ini->prox;
				}
				sleep(4);
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
	int i = 0; long int aux = 0;

	cliente pessoa1, pessoa2;
	
	filas fn[TAM], fila[TAM];;
	
	for(i = 0; i < TAM; i++){ //cria  espaco nas posicoes
		fn[i].ini= (elem *) malloc (sizeof(elem));
		fn[i].fim= (elem *) malloc (sizeof(elem));
	}
	
	
	inicia_filas(fn);
	inicia_cliente(pessoa1);
	inicia_cliente(pessoa2);
	
	long int aux1 = 0, aux2 = 0, aux3 = 0, cont = 0;
	
	short int contcliente = 0;
	int mediaespera = 0;
	long int *totaldep , *totalpag , *totalsaque ;
	
	totaldep = &aux1, totalpag = &aux2, totalsaque = &aux3;
	
	
	do{
		/*pessoa adulta*/
		pessoa1 = randA(pessoa1);	
	 	if (inserirfim(pessoa1, fn) == 1) contcliente++;

		limpar();
		
		exibir_tela(fn, pessoa1, contcliente,totaldep, totalpag, totalsaque);
		
	 	for(i = 0; i < TAM; i++)
			exibir_filas(fn,fila, i);
			
			
	 	/*pessoa idosa*/
		pessoa2 = randP(pessoa2); 	
	 	if (inserirpriori(pessoa2, fn) == 1) contcliente++;
	 	
		limpar();
		
		exibir_tela(fn, pessoa2, contcliente,totaldep, totalpag, totalsaque);

		//imprimir filas
		for(i = 0; i < TAM; i++)
			exibir_filas(fn,fila, i);
			
		cont++;	
		
		if(cont == 2){
			tempo_operacao(fn);
			cont = 0;
			contcliente--;
		}


	}while (contcliente > 0);
	
	
	return 0;
}
