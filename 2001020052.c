/*-----------------------------------------*
 *	Tugas 2 Struktur Data
 *	Anindya Sekar Paramitha - 2001020052
 *-----------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PJG_STRING 21
#define cetakbaris() printf("\n")

char** stack;
int pointer = 0;

int push(char* kata){
	//siapkan tempat penampungan sementara
	char** stackTemp = (char**) realloc(stack, pointer * PJG_STRING * sizeof(char**));
	
	if(stackTemp){
		stack = stackTemp;
		stack[pointer] = (char*) malloc(PJG_STRING * sizeof(char*));
		
		if(stack[pointer] == NULL){
			free(stackTemp);
			return 0;
		}
		else {
			//cek apakah copy string sukses
			if(strcpy(stack[pointer], kata) != NULL){
				pointer++;
				return 1;
			}
			else {
				free(stackTemp);
				return 0;
			}
		}
	}
	else {
		free(stackTemp);
		return 0;
	}
}

void pop(){
	//warna tulisan hijau pada Pop => dan warna tulisan kuning tebal dengan latar biru pada kata dari stack
	printf("\033[32mPop =>\033[0m \033[33;44;1m %s \033[0m \n", stack[--pointer]);
	
	if(pointer == 0){
		cetakbaris();
			
		//warna tulisan kuning pada Stack Empty
		printf("\033[33mStack Empty\033[0m\n");
	}
}

int main(int argc, char** argstr){
	if (argc <= 1){
		printf("Tidak ada inputan.\n");
		printf("Format yang betul \n\t ./2001020052.o kata1 kata2 kata 3 ...\n");
		return 1;
	}
	
	int flagSukses;
	stack = (char**) malloc(pointer * PJG_STRING * sizeof(char**));
	if(stack == NULL){
		printf("Gagal mengalokasikan array ke memory.\n");
		free(stack);
		return 1;
	}
	
	for(int i = 1; i < argc; i++){
		flagSukses = push(argstr[i]);
		if(!flagSukses){
			printf("Gagal mengalokasikan push ke-%d ke dalam stack.\n", i);
			break;
		}
	}
	if(flagSukses){
		//warna tulisan hijau pada Success created stack
		printf("\033[32mSuccess created stack\033[0m\n");
	}
	cetakbaris();
	
	while(pointer != 0){
		pop();
	}

	free(stack);
	return 0;
}
