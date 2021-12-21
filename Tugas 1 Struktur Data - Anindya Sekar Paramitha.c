/*-----------------------------------------*
 *	Tugas 1 Struktur Data
 *	Anindya Sekar Paramitha - 2001020052
 *-----------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PJG_NAMA 21
#define cetakbaris() printf("\n")

int ruang = 0;
unsigned int* ID;
char (* nama)[PJG_NAMA];
unsigned int* usia;

int inputID;
char inputName[PJG_NAMA];
int inputAge;

int SearchID(int idNum){
	if(ruang > 0){
		for(int i = 0; i < ruang; i++){
			if (ID[i] == idNum){
				return i;
			}
		}
		return -1;
	}
	else {
		return -1;
	}
}

void AddData(){
	++ruang;
	ID = realloc(ID, ruang * sizeof(int));
	nama = realloc(nama, ruang * PJG_NAMA);
	usia = realloc(usia, ruang * sizeof(int));
	
	if (ID == NULL || nama == NULL || usia == NULL) {
		printf("ERROR: Failed to insert the data.\n");
	}
	else {
		ID[ruang - 1] = inputID;
		memcpy((nama + (ruang - 1)), inputName, PJG_NAMA);
		usia[ruang - 1] = inputAge;
	}
}

void DeleteData(int IDNum){
	int idx = SearchID(IDNum);
	if(idx < 0){
		printf("ID Not Found");
	}
	else {
		for(int i = idx; i < ruang; i++){
			ID[i] = ID[i + 1];
			memcpy((nama + i), (nama + (i + 1)), PJG_NAMA);
			usia[i] = usia[i + 1];
		}
		
		--ruang;
		ID = realloc(ID, ruang * sizeof(int));
		nama = realloc(nama, ruang * PJG_NAMA);
		usia = realloc(usia, ruang * sizeof(int));
		
		printf("Data deleted");
	}
}

void ShowData(){
	printf("ID	Name			Age\n");
	for(int i = 0; i < ruang; i++){
		printf("%-5d	%-20s	%-3d\n", ID[i], nama[i], usia[i]);
	}
}

int main(){
	short choice;
	
	ID = malloc(ruang * sizeof(int));
	nama = calloc(ruang, PJG_NAMA);
	usia = malloc(ruang * sizeof(int));
	
	while (1){
		printf("Activity\n");
		printf("1. Input new data\n");
		printf("2. Delete data\n");
		printf("3. Show data list\n");
		printf("4. Exit Program\n");
		printf("Your choice:");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				printf("Insert the ID:");
				scanf("%d", &inputID);
				
				if(SearchID(inputID) != -1){
					printf("Data with ID %d are already inserted.\n", inputID);
				}
				else {
					printf("Insert the name (max 20 chars):");
					scanf("%*c%[^\n]%*c", inputName);
					printf("Insert the age:");
					scanf("%d", &inputAge);
					
					AddData();
				}
				break;
				
			case 2:
				printf("Select an ID to delete:");
				scanf("%d", &inputID);
				DeleteData(inputID);
				cetakbaris();
				break;
				
			case 3:
				ShowData();
				break;
				
			case 4:
				exit(0);
				break;
				
			default:
				printf("ERROR: The input is not valid.\n");
				break;
		}
		
		cetakbaris();
	}
	return 0;
}

