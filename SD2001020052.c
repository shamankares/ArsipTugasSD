/*-----------------------------------------*
 *	Proyek UTS Struktur Data
 *	Anindya Sekar Paramitha - 2001020052
 *-----------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

char* stack;
char* result;
int lastIdxResult;
int pointer = -1;

/*---------- Metode Umum ----------*/
bool copyToResult(char kar){
	char* resTemp = realloc(result, (++lastIdxResult * sizeof(char*)) + 1);
	
	if(resTemp == NULL){
		printf("Gagal menyalin karakter ke hasil.\n");
		lastIdxResult--;
		free(resTemp);
		return false;
	}
	
	result = resTemp;
	result[lastIdxResult] = kar;
	return true;
}

char* balikkan(char* kalimat){
	int loop = 0;
	int batasAtas = strlen(kalimat) - 1;
	int batasTgh = floor(strlen(kalimat)/2);
	char* kalimatBalik = malloc(strlen(kalimat));
	
	if(kalimatBalik == NULL){
		printf("Gagal mengalokasikan memori.\n");
		return NULL;
	}
	
	strcpy(kalimatBalik, kalimat);
	for (loop; loop < batasTgh; loop++){
		char temp = kalimatBalik[loop];
		kalimatBalik[loop] = kalimatBalik[batasAtas-loop];
		kalimatBalik[batasAtas-loop] = temp;
	}
	
	loop = 0;
	while (loop <= batasAtas){
		if(kalimatBalik[loop] == '('){
			kalimatBalik[loop] = ')';
		}
		else if(kalimatBalik[loop] == ')'){
			kalimatBalik[loop] = '(';
		}
		loop++;
	}
	return kalimatBalik;
}

/*---------- Metode untuk Stack ----------*/
bool push(char kata){
	char* stackTemp = realloc(stack, (++pointer * sizeof(char*)) + 1);
	
	if(stackTemp == NULL){
		printf("Gagal melakukan push.\n");
		pointer--;
		free(stackTemp);
		return false;
	}
	
	stack = stackTemp;
	stack[pointer] = kata;
	return true;
}

bool pop(){
	if(copyToResult(stack[pointer])){
		pointer--;
		return true;
	}
	else {
		return false;
	}
}

/*---------- Metode Mengubah Bentuk Ekspresi ----------*/
int nilaiDerajat(char op){
	switch(op){
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
		default:
			return -1;
	}
}

bool isOperator(char unit){
	switch(unit){
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '(':
		case ')':
			return true;
		default:
			return false;
	}
}

bool infKePostfix(char* exprs, int batas){
	bool sukses;
	lastIdxResult = -1;
	
	for(int i = 0; i < batas; i++){
		if(isOperator(exprs[i])){
			if(pointer == -1){
				sukses = push(exprs[i]);
			}
			else if(exprs[i] == '('){
				sukses = push(exprs[i]);
			}
			else if(exprs[i] == ')'){
				while(stack[pointer] != '('){
					sukses = pop();
				}
				pointer--;
			}
			else {
				while(nilaiDerajat(exprs[i]) <= nilaiDerajat(stack[pointer])){
					sukses = pop();
				}
				sukses = push(exprs[i]);
			}
		}
		else {
			sukses = copyToResult(exprs[i]);
		}
		
		if(!sukses){
			return false;
		}
	}
	
	for(int i = pointer; i >= 0; i--){
		if(pop()){
			continue;
		}
		else {
			return false;
		}
	}
	
	return true;
}

bool infKePrefix(char* exprs, int batas){
	char* infix = balikkan(exprs);
	lastIdxResult = -1;
	
	if(infix == NULL){
		return false;
	}
	
	if(infKePostfix(infix, batas)){
		result = balikkan(result);
		return true;
	}
	else {
		return false;
	}
}

int main(int argc, char** argstr){
	if(argc == 1){
		printf("Tidak ada inputan.\n");
		printf("Cara penggunaan:\n");
		printf("\t ./SD2001020052 ekspresi \n");
		printf("\t ./SD2001020052 a+b\'*\'c-\'(\'d/e^f\')\' \t untuk a+b*c-(d/e^f)\n");		//./sd2001020052 a+b'*'c-'('d/e')'
		printf("\t ./SD2001020052 \"a+b*c-(d/e^f)\" \t untuk a+b*c-(d/e^f)\n");				//./sd2001020052 "a+b*c-(d/e)"
		return 1;
	}
	
	bool sukses;
	char* ekspresi = argstr[1];
	stack = malloc(sizeof(char*));
	result = malloc(sizeof(char*));
	
	if(stack == NULL || result == NULL){
		printf("Gagal mengalokasikan array ke memory.\n");
		free(stack);
		return 1;
	}

	sukses = infKePrefix(ekspresi, strlen(argstr[1]));
	if(sukses){
		printf("Prefix answer\n");
		printf("2001020052 = %s\n", result);
	}
	
	sukses = infKePostfix(ekspresi, strlen(argstr[1]));
	if(sukses){
		printf("Postfix answer\n");
		printf("2001020052 = %s\n", result);
	}
	
	free(stack);
	free(result);
	return 0;
}
