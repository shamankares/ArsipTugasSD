/*-----------------------------------------*
 *	Tugas 3 Struktur Data
 *	Anindya Sekar Paramitha - 2001020052
 *-----------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PJG_NAMA 51
#define PJG_ID 13

typedef struct studentData {
	char id[PJG_ID];
	char nama[PJG_NAMA];
	struct studentData* prev;
	struct studentData* next;
} mhs;

bool fRun = true;
int jumlahData = 0;
mhs* awal;
mhs* akhir;

/*---------- Metode untuk Record ----------*/
mhs* searchRecordID(char no[]){
	mhs* pFwd = awal;
	mhs* pBwd = akhir;
	
	while(strcmp(pFwd->id, no) != 0 && strcmp(pBwd->id, no) != 0){
		if(pFwd->next == pBwd || pFwd == pBwd){
			return NULL;
		}
		pFwd = pFwd->next;
		pBwd = pBwd->prev;
	}
	if(strcmp(pFwd->id, no) == 0){
		return pFwd;
	}
	else if(strcmp(pBwd->id, no) == 0){
		return pBwd;
	}
}

mhs** searchRecordName(char studName[], mhs** hasil, int* count){
	mhs* pFwd = awal;
    mhs* pBwd = akhir;

    while(pBwd->next != pFwd){
		if(pBwd->next != NULL){
			if(pFwd == pBwd){
				if(strcmp(pFwd->nama, studName) == 0){
					(*count)++;
					hasil = realloc(hasil, (*count) * sizeof(mhs*));
					if(hasil){
						hasil[(*count) - 1] = (mhs*) malloc(sizeof(mhs*));
						if(hasil[(*count) - 1]){
							hasil[(*count) - 1] = pFwd;
							return hasil;
						}
						else {
							free(hasil[(*count) - 1]);
							return NULL;
						}
					}
					else {
						return NULL;
					}
				}
				else {
					return hasil;
				}
			}
		}
		
        if(strcmp(pFwd->nama, studName) == 0){
            (*count)++;
            hasil = realloc(hasil, (*count) * sizeof(mhs*));
			if(hasil){
				hasil[(*count) - 1] = (mhs*) malloc(sizeof(mhs*));
				if(hasil[(*count) - 1]){
					hasil[(*count) - 1] = pFwd;
				}
				else {
					free(hasil[(*count) - 1]);
					return NULL;
				}
			}
			else {
				return NULL;
			}
        }
        if(strcmp(pBwd->nama, studName) == 0){
            (*count)++;
            hasil = (mhs**) realloc(hasil, (*count) * sizeof(mhs*));
			if(hasil){
				hasil[(*count) - 1] = (mhs*) malloc(sizeof(mhs*));
				if(hasil[(*count) - 1]){
					hasil[(*count) - 1] = pBwd;
				}
				else {
					free(hasil[(*count) - 1]);
					return NULL;
				}
			}
			else {
				return NULL;
			}
        }

        pFwd = pFwd->next;
        pBwd = pBwd->prev;
    }
	return hasil;
}

void addRecord(char no[], char studName[]){
	if(awal != NULL){
		mhs* isExist = searchRecordID(no);
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
	baru->next = NULL;
	baru->prev = NULL;
	jumlahData++;
		
	if(awal == NULL){
		awal = baru;
		akhir = baru;
	}
	else {
		akhir->next = baru;
		baru->prev = akhir;
		akhir = baru;
	}
}

void updateRecord(mhs* org, char no[], char studName[]){
	mhs* dupExist = searchRecordID(no);
	
	if(dupExist == org){													//Alamat yang sama dengan aslinya; hanya ingin mengubah nama
		strcpy(org->nama, studName);
	}
	else if(dupExist != org && dupExist != NULL){							//Ada alamat yang berisi ID yang sama dengan ID baru
		printf("\nUpdate Denied.\n");
		printf("There is another same ID Number already in the record.\n");
	}
	else {																	//Tidak ada alamat dengan ID yang sama dengan ID baru
		strcpy(org->id, no);
		strcpy(org->nama, studName);
	}
}

void showRecords(){
	mhs* tunjuk = awal;

	printf("\nStudent ID	Student Name\n");
	while(tunjuk != NULL){
		printf("%-12s	%-50s\n", tunjuk->id, tunjuk->nama);
		tunjuk = tunjuk->next;
	}
}

void delRecord(mhs* dataDel){
/*	mhs* dataDel = searchRecordID(no);
	if(!dataDel){
		return;
	}*/
	mhs* dataTemp;
	
	if(dataDel != awal){
		dataTemp = dataDel->prev;
	}
	else if(dataDel == awal){
		dataTemp = dataDel->next;
	}
	
	if(dataDel == akhir){
		dataTemp->next = NULL;
		akhir = dataTemp;
	}
	else if(dataDel == awal){
		awal = dataTemp;
		dataTemp->prev = NULL;
	}
	else {
		dataTemp->next = dataDel->next;
		dataTemp = dataTemp->next;
		dataTemp->prev = dataDel->prev;
	}
	
	free(dataDel);
	jumlahData--;
}

void clearData(){
	mhs* tunjuk = awal;
	while(tunjuk != NULL){
		mhs* temp = tunjuk;
		tunjuk = tunjuk->next;
		free(temp);
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
		/*----- Input new record -----*/
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
			
		/*----- Search record -----*/
		case '2':
			while(!fCancel){
				printf("\nSearch based on ID [I] or Name [N]?: ");
				scanf(" %c%*c", &choice);
				
				if(choice == 'I' || choice == 'i'){
					printf("Type Student\'s ID Number to look for: ");
					scanf("%s", inID);
					
					mhs* result = searchRecordID(inID);
					
					printf("\n");
					if(result){
						printf("Student ID	Student Name\n");
						printf("%-12s	%-50s\n", result->id, result->nama);
					}
					else {
						printf("No student data is matched with the ID Number.\n");
					}
				}
				else if(choice == 'N' || choice == 'n'){
					printf("Type Student\'s Name to look for: ");
					scanf("%[^\n]%*c", inNama);
					
					int count = 0;
					mhs** hasil = malloc(count * sizeof(mhs*));

					hasil = searchRecordName(inNama, hasil, &count);
					
					printf("\n");
					if(count > 0 && hasil != NULL){
						printf("Student ID	Student Name\n");
						for(int i = 0; i < count; i++){
							printf("%-12s	%-50s\n", hasil[i]->id, hasil[i]->nama);
						}
					}
					else if(hasil == NULL){
						printf("Error while allocating the result.\n");
					}
					else {
						printf("No student data is matched with the Name.\n");
					}

					free(hasil);
				}
				else {
					continue;
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
			
		/*----- Update record -----*/
		case '3':
			while(!fCancel){
				printf("\nType Student\'s ID Number to update: ");
				scanf("%s", inID);
				mhs* result = searchRecordID(inID);
				
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
			
		/*----- Show records -----*/
		case '4':
			showRecords();
			
			printf("\n");
			break;
			
		/*----- Delete record -----*/
		case '9':
			while(!fCancel){
				printf("\nType Student\'s ID Number to be deleted: ");
				scanf("%s", inID);
				mhs* result = searchRecordID(inID);
				
				if(result){
					printf("\n");
					printf("ID Number	: %s\n", result->id);
					printf("Name		: %s\n", result->nama);
					
					while(true){
						printf("\nAre you sure to delete this data? [Y/N]: ");
						scanf(" %c%*c", &choice);
						
						if(choice == 'Y' || choice == 'y'){
							delRecord(result);
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
			
		/*----- Exit program -----*/
		case '0':
			clearData();
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
