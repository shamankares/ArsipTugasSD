/*-----------------------------------------*
 *	Proyek UAS Struktur Data
 *	Anindya Sekar Paramitha - 2001020052
 *-----------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PJG_NAMA 51
#define PJG_ID 13

typedef struct studentData {
	char id[PJG_ID];
	char nama[PJG_NAMA];
	int tinggi;
	struct studentData* kiri;
	struct studentData* kanan;
} mhs;

bool fRun = true;
mhs* akar = NULL;

/*------------------------------ Metode Umum ------------------------------*/
int maxVal(int a, int b){
	return (a > b) ? a : b;
}

/*------------------------------ Metode untuk Tree ------------------------------*/
mhs* minimal(mhs* tunjuk){
	while(tunjuk->kiri != NULL)
		tunjuk = tunjuk->kiri;
	return tunjuk;
}

/*mhs* maximal(mhs* tunjuk){
	while(tunjuk->kanan != NULL)
		tunjuk = tunjuk->kanan;
	return tunjuk;
}*/

int height(mhs* tunjuk){
	if(tunjuk == NULL)
		return 0;
	return tunjuk->tinggi;
}

int balanceDeg(mhs* tunjuk){
	if(tunjuk == NULL)
		return 0;
	return (height(tunjuk->kiri) - height(tunjuk->kanan));
}

mhs* rightRotate(mhs* node){
	mhs* anakKiri = node->kiri;
	mhs* bungsuKiri = anakKiri->kanan;
	
	anakKiri->kanan = node;
	node->kiri = bungsuKiri;
	
	node->tinggi = maxVal(height(node->kanan), height(node->kanan)) + 1;
	anakKiri->tinggi = maxVal(height(anakKiri->kanan), height(anakKiri->kanan)) + 1;
	
	return anakKiri;
}

mhs* leftRotate(mhs* node){
	mhs* anakKanan = node->kanan;
	mhs* sulungKanan = anakKanan->kiri;
	
	anakKanan->kiri = node;
	node->kanan = sulungKanan;
	
	node->tinggi = maxVal(height(node->kiri), height(node->kanan)) + 1;
	anakKanan->tinggi = maxVal(height(anakKanan->kiri), height(anakKanan->kanan)) + 1;
	
	return anakKanan;
}

mhs* balanceThem(mhs* node){
	int balance = balanceDeg(node);
	
	if(balance > 1 && balanceDeg(node->kiri) >= 0){
		return rightRotate(node);
	}
	else if(balance > 1 && balanceDeg(node->kiri) < 0){
		node->kiri = leftRotate(node->kiri);
		return rightRotate(node);
	}
	else if(balance < -1 && balanceDeg(node->kanan) <= 0){
		return leftRotate(node);
	}
	else if(balance < -1 && balanceDeg(node->kanan) > 0){
		node->kanan = rightRotate(node->kanan);
		return leftRotate(node);
	}
	
	return node;
}

/*------------------------------ Metode Record ------------------------------*/
mhs* searchRecord(char ID[], mhs* tunjuk){
	if(tunjuk == NULL)
		return NULL;
	
	if (strcmp(tunjuk->id, ID) == 0)
		return tunjuk;
	else if(strcmp(ID, tunjuk->id) < 0)
		return searchRecord(ID, tunjuk->kiri);
	else if(strcmp(ID, tunjuk->id) > 0)
		return searchRecord(ID, tunjuk->kanan);
}

mhs* insertRecord(mhs* induk, mhs* baru){
	if(induk == NULL)
		return baru;
	
	if(strcmp(baru->id, induk->id) < 0){
		if(induk->kiri == NULL)
			induk->kiri = baru;
		else
			induk->kiri = insertRecord(induk->kiri, baru);
	}
	else if(strcmp(baru->id, induk->id) > 0){
		if(induk->kanan == NULL)
			induk->kanan = baru;
		else
			induk->kanan = insertRecord(induk->kanan, baru);
	}
	
	induk->tinggi = maxVal(height(induk->kiri), height(induk->kanan)) + 1;
	
	int balance = balanceDeg(induk);
	induk = balanceThem(induk);
	
	return induk;
}

void addRecord(char no[], char studName[]){
	if(akar != NULL){
		mhs* isExist = searchRecord(no, akar);
		if(isExist){
			printf("\n");
			printf("Input Denied.\n");
			printf("Student\'s ID Number is already in the record.\n");
			return;
		}
	}
	
	mhs* baru = (mhs*) malloc(sizeof(mhs));
	if(baru == NULL){
		printf("\n");
		printf("Error when allocating a new record.\n");
		free(baru);
		return;
	}
	strcpy(baru->id, no);
	strcpy(baru->nama, studName);
	baru->tinggi = 1;
	baru->kiri = NULL;
	baru->kanan = NULL;
	
	akar = insertRecord(akar, baru);
}

void showRecords(mhs* tunjuk){
	if(tunjuk == NULL){
		return;
	}
	else {
		showRecords(tunjuk->kiri);
		printf("%-12s	%-50s\n", tunjuk->id, tunjuk->nama);
		showRecords(tunjuk->kanan);
	}
}

mhs* deleteRecord(mhs* induk, mhs* nodeHapus){
	if(induk == NULL){
		return induk;
	}
	
	if(strcmp(nodeHapus->id, induk->id) < 0){
			induk->kiri = deleteRecord(induk->kiri, nodeHapus);
	}
	else if(strcmp(nodeHapus->id, induk->id) > 0){
			induk->kanan = deleteRecord(induk->kanan, nodeHapus);
	}
	else {
		if(induk->kiri == NULL || induk->kanan == NULL){
			mhs* temp = induk->kiri ? induk->kiri : induk->kanan;
			
			if(temp == NULL){
				free(induk);
				return NULL;
			}
			else {
				*induk = *temp;
				free(temp);
			}
		}
		else {
			mhs* temp = minimal(induk->kanan);
			strcpy(induk->id, temp->id);
			strcpy(induk->nama, temp->nama);
			induk->kanan = deleteRecord(induk->kanan, temp);
		}
	}
	
	induk->tinggi = maxVal(height(induk->kiri), height(induk->kanan)) + 1;
	induk = balanceThem(induk);
	
	return induk;
}

void updateRecord(mhs* org, char newNo[], char newStudName[]){
	mhs* dupExist = searchRecord(newNo, akar);
	
	if(dupExist == org){													//Alamat yang sama dengan aslinya; hanya ingin mengubah nama
		strcpy(org->nama, newStudName);
	}
	else if(dupExist != org && dupExist != NULL){							//Ada alamat yang berisi ID yang sama dengan ID baru
		printf("\nUpdate Denied.\n");
		printf("There is another same ID Number already in the record.\n");
	}
	else {																	//Tidak ada alamat dengan ID yang sama dengan ID baru
		akar = deleteRecord(akar, org);
		addRecord(newNo, newStudName);
	}
}

void deleteAll(mhs* node){
	if(node == NULL){
		return;
	}
	else {
		deleteAll(node->kiri);
		deleteAll(node->kanan);
		free(node);
	}
}

bool menu(){
	char inID[PJG_ID];
	char inNama[PJG_NAMA];
	char choice;
	bool fCancel = false;
	
	printf("STUDENT RECORD SYSTEM\n");
	printf("1. Input New Record\n");
	printf("2. Search Record\n");
	printf("3. Update Record\n");
	printf("4. Show Records\n");
	printf("9. Delete Records\n");
	printf("0. Exit Program\n");
	printf("Your choice: ");
	scanf(" %c%*c", &choice);
	
	switch(choice){
		/*------------------------------ Input new record ------------------------------*/
		case '1':
			while(!fCancel){
				printf("\nType Student\'s ID Number: ");
				scanf("%s", inID);
				printf("Type Student\'s Name: ");
				scanf("%*c%[^\n]%*c", inNama);
				
				addRecord(inID, inNama);
				
				while(true){
					printf("\nInput another data? [Y/N]: ");
					scanf(" %c%*c", &choice);
					
					if(choice == 'Y' || choice == 'y'){
						break;
					}
					else if(choice == 'N' || choice == 'n'){
						fCancel = true;
						break;
					}
					else {
						continue;
					}
				}
			}
			
			printf("\n");
			break;
			
		/*------------------------------ Search record ------------------------------*/
		case '2':
			while(!fCancel){
					printf("Type Student\'s ID Number to look for: ");
					scanf("%s", inID);
					
					mhs* result = searchRecord(inID, akar);
					
					printf("\n");
					if(result){
						printf("Student ID	Student Name\n");
						printf("%-12s	%-50s\n", result->id, result->nama);
					}
					else {
						printf("No student data is matched with the ID Number.\n");
					}
				
				while(true){
					printf("\nSearch again? [Y/N]: ");
					scanf(" %c%*c", &choice);
					
					if(choice == 'Y' || choice == 'y'){
						break;
					}
					else if(choice == 'N' || choice == 'n'){
						fCancel = true;
						break;
					}
					else {
						continue;
					}
				}
			}

			printf("\n");
			break;
			
		/*------------------------------ Update record ------------------------------*/
		case '3':
			while(!fCancel){
				printf("\nType Student\'s ID Number to update: ");
				scanf("%s", inID);
				mhs* result = searchRecord(inID, akar);
				
				if(result){
					printf("\nType New Student\'s ID Number: ");
					scanf("%s", inID);
					printf("Type New Student\'s Name: ");
					scanf("%*c%[^\n]%*c", inNama);
					
					updateRecord(result, inID, inNama);
				}
				else {
					printf("ID not found.\n");
				}
				
				while(true){
					printf("\nUpdate another data? [Y/N]: ");
					scanf(" %c%*c", &choice);
					
					if(choice == 'Y' || choice == 'y'){
						break;
					}
					else if(choice == 'N' || choice == 'n'){
						fCancel = true;
						break;
					}
					else {
						continue;
					}
				}
			}
			
			printf("\n");
			break;
			
		/*------------------------------ Show records ------------------------------*/
		case '4':
			printf("\nStudent ID	Student Name\n");
			showRecords(akar);
			
			printf("\n");
			break;
			
		/*------------------------------ Delete record ------------------------------*/
		case '9':
			while(!fCancel){
				printf("\nType Student\'s ID Number to be deleted: ");
				scanf("%s", inID);
				mhs* result = searchRecord(inID, akar);
				
				if(result){
					printf("\n");
					printf("ID Number	: %s\n", result->id);
					printf("Name		: %s\n", result->nama);
					
					while(true){
						printf("\nAre you sure to delete this data? [Y/N]: ");
						scanf(" %c%*c", &choice);
						
						if(choice == 'Y' || choice == 'y'){
							akar = deleteRecord(akar, result);
							break;
						}
						else if(choice == 'N' || choice == 'n'){
							break;
						}
						else {
							continue;
						}
					}
				}
				else {
					printf("ID Number not found.\n");
				}
				
				while(true){
					printf("\nDelete another data? [Y/N]: ");
					scanf(" %c%*c", &choice);
					
					if(choice == 'Y' || choice == 'y'){
						break;
					}
					else if(choice == 'N' || choice == 'n'){
						fCancel = true;
						break;
					}
					else {
						continue;
					}
				}
			}
			
			printf("\n");
			break;
			
		/*------------------------------ Exit program ------------------------------*/
		case '0':
			deleteAll(akar);
			fRun = false;
			break;
			
		default:
			printf("The input is not valid.\n\n");
			break;
	}
}

int main(){
	while(fRun){
		menu();
	}
		
	return 0;
}
