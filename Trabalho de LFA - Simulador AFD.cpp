#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct{//Struct que armazena as transições criadas
	char simb;
	int estAtual;
	int estFuturo;
} Transicao;

void criaEstados(int *nomeEst, int nEst){ // função que cria os estados do automato
	
	int i;
	
	for(i = 0; i < nEst; i++){
		nomeEst[i]=i;
	}
}

int infoAlfabeto(char alf[]){//Função que cria o alfabeto
	
	int nAlf = 0, i;
	
	printf("\nInforme a quantidade de caracteres do alfabeto: ");
	scanf("%d", &nAlf);	
	
	for(i = 0; i < nAlf; i++){
		fflush(stdin);
		printf("\nInforme o %d° caractere: ", i+1);
		scanf("%c", &alf[i]);	
	}
	
	return nAlf;
}

void mostraEst(int *nomeEst, int nEst){ // Função que mostra os estados criados
	
	int i;
	
	printf("Estados criados\n");
	for(i = 0; i < nEst; i++){
		printf("q%d   ", nomeEst[i]);
	}
	
}

void criaTrans(int nomeEst[], char alf[], int nEst, int nAlf, Transicao vetTrans[]){//Função que cria as transições
	
	int i, j=0, k=0;
	int estFuturo=0;
	
	for(i = 0; i < nEst; i++){
		for(j = 0; j < nAlf; j++){
			printf("\nInforme a transição do q%d com %c: ", nomeEst[i], alf[j]);
			scanf("%d", &estFuturo);
			Transicao trans;
			trans.estAtual = nomeEst[i];
			trans.simb = alf[j];
			trans.estFuturo = estFuturo;
			vetTrans[k] = trans;
			k++;
		}	
	}
}

void verifiPalavra(int nomeEst[], char alf[], int nEst, int nAlf, Transicao vetTrans[], int estInicio, int estFinal[], int nFinal){// Verifica a palavra
	
	char palavra[25];
	
	int posAtual, i, tam, j, auxFinal, info = 1, l, aux=0, k, verPalavra;
	
	while(info != 0){//Menu para saber se continua ou não a execução 
		verPalavra=0;
		k=0;
		system("cls");
		
		printf("      ");
		for(i = 0; i < nAlf; i++){
			printf(" %c ", alf[i]);
		}
		printf("\n");
		
		for(i = 0; i < (nEst*nAlf); i = i + nAlf){ // Mostrar caso a posição seja inicial e final
			
			if(vetTrans[i].estAtual == estInicio){
				for(l = 0; l < nFinal; l++){
			
					if(vetTrans[i].estAtual == estFinal[l]){
						aux=1;
					}
				}
				if(aux == 1){
					printf("*->q%d| ", vetTrans[i].estAtual);
				}else{
					printf(" ->q%d| ", vetTrans[i].estAtual);
				}
				
			}else{
				aux=0;
				for(l = 0; l < nFinal; l++){
			
					if(vetTrans[i].estAtual == estFinal[l]){
						aux=1;
					}
				}
				if(aux == 1){
					printf(" * q%d| ", vetTrans[i].estAtual);	
				}else{
					printf("   q%d| ", vetTrans[i].estAtual);	
				}
				aux=0;
			}
			for(j = 0; j < nAlf; j++){
				printf("q%d ", vetTrans[k].estFuturo);
				k++;
			}
			printf("\n");
		}
	
		j=0;
		
		posAtual = estInicio;
		while(verPalavra == 0){
			printf("\nInforme a palavra a ser verificada: ");//Pega a palavra a ser verificada
			fflush(stdin);
			gets(palavra);
			tam=strlen(palavra);
			for(i = 0; i < tam; i++){//Verifica se tem algum caractere inválido
				for(j = 0; j < nAlf; j++){
					
					if(palavra[i] == alf[j]){
				
						verPalavra = 1;
						break;
					}else{
					
						verPalavra = 0;
					}
				}
				if(verPalavra == 0){
					printf("\nPalavra inválida");
					
					break;
				}
			}
		}
		j=0;
		
		for(i = 0; i < tam; i++){//Mostra as transições feitas pela máquina
			while(posAtual != vetTrans[j].estAtual){
				j++;
			}
			while(palavra[i] != vetTrans[j].simb){
				j++;
			}
			printf("\nq%d - %c -> ", posAtual, palavra[i]);
			posAtual = vetTrans[j].estFuturo;
			printf("q%d", posAtual);
			if(posAtual == -1){
				printf("\nEstado Vazio");
				break;
			}
			j=0;
		}
		for(i = 0; i <= nFinal; i++){//Verifica se a palavra terminou em um estado final
			if(posAtual == estFinal[i]){
				auxFinal=1;
				break;
			}
		}
		if(auxFinal == 1){
			printf("\n\nPalavra aceita\n");
		}else{
			printf("\n\nPalavra rejeitada\n");
		}
		auxFinal=0;
		
		printf("\n1- Continuar /");
		printf(" 0- Sair: ");
		scanf("%d", &info);
	}
}

main(){
	
	setlocale(LC_ALL,"");
	
	int info, nEst, nAlf, estInicio, i = 0, busca = 0, j=0, k=0, l=0, aux=0, nFinal=0, info2=1;
	
	char alf[10];
	
	printf("Informe o numero de estados: ");//Pega a quantidades de estados a serem criados 
	scanf("%d", &nEst);
	
	int estFinal[nEst], nomeEst[nEst];
	
	criaEstados(nomeEst, nEst);//Chama a função que cria os estados
	
	mostraEst(nomeEst, nEst);//Mostra os estados criados
	
	printf("\n\nInforme o estado inicial: ");//Armazena o estado inicial
	scanf("%d", &estInicio);
	
	printf("\n1- Adicionar estados finais / ");
	printf("0- Sair: ");
	scanf("%d", &info);

	if(info == 0){
		return 0;
	}

	while(info == 1){//Armazena os estados finais
		printf("\nInforme o estado final: ");
		fflush(stdin);
		scanf("%d", &estFinal[i]);
			
		nFinal++;
		i++;
			
		printf("\n1- Adicionar mais estados finais /");
		printf(" 0- Não adicionar mais estados finais: ");
		fflush(stdin);
		scanf("%d", &info); 
		
		if(info == 0){
			break;
		}
	}
	
	estFinal[i] = 1000;
	nAlf = infoAlfabeto(alf);//Chama a função que cria o alfabeto

	Transicao vetTrans[(nEst * nAlf)];//Cria um vetor de transições 
	criaTrans(nomeEst, alf, nEst, nAlf, vetTrans);//Cria as transições 
	
	verifiPalavra(nomeEst, alf, nEst, nAlf, vetTrans, estInicio, estFinal, nFinal);//Chama a função que verifica a palavra
}
