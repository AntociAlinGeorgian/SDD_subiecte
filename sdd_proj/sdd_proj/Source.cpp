#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>


//Admin -> Lista simplu inlantuita
struct Printer {
	char* id;
	int paperCapacity;
	char* model;
};

struct nodeLSI {
	Printer* info;
	nodeLSI* next;
};

nodeLSI* createLSINode(Printer* info) {
	nodeLSI* node = new nodeLSI;
	node->info = info;
	node->next = NULL;
	return node;
}

bool checkPrinterDuplicateID(nodeLSI* lst,char* id) {
	if (lst) {
		while (lst != NULL) {
			if (strcmp(lst->info->id, id) == 0) {
				return true;
			}
			else {
				return false;
			}
			lst = lst->next;
		}
	}
}
bool insertInLSI(nodeLSI*& lst, nodeLSI* node) {
	if (lst == NULL) {
		lst = node;
	}
	else {
		nodeLSI* tmp = lst;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = node;
	}
	return true;
}

void printPrintersStatus(nodeLSI* printersList) {
	if (printersList) {
		while (printersList->next != NULL) {
			printf("* ID: %s Model: %s Paper: %d \n", printersList->info->id, printersList->info->model, printersList->info->paperCapacity);
			printersList = printersList->next;
		}
		printf("* ID: %s Model: %s Paper: %d \n", printersList->info->id, printersList->info->model, printersList->info->paperCapacity);
	}
	else {
		printf("No printers available.\n");
	}
}

void addPaper(nodeLSI*& printersList) {
	if (printersList) {
		char aux[10];
		int nrPapers;
		int ok = 0;
		printf("Printer ID: ");
		scanf("%s", &aux);
		printf("Nr. of papers: ");
		scanf("%d", &nrPapers);

		nodeLSI* tmp = printersList;
		while (tmp != NULL) {
			if (strcmp(printersList->info->id, aux) == 0) {
				printersList->info->paperCapacity += nrPapers;
				ok = 1;
			}
			tmp = tmp->next;
		}

		if (ok == 1) {
			printf("Paper resources added!\n");
		}
		else {
			printf("Wrong id!\n");
		}
	}
}

/* USER -> ABC */
struct Fisier {
	char* numeFisier;
	char* continutFisier;
	int nrPagesNeeded;
};

struct ABC {
	Fisier* infoFisier;
	ABC* right;
	ABC* left;
};

ABC* createNodeABC(Fisier* info) {
	ABC* nod = new ABC;
	nod->infoFisier = info;
	nod->left = NULL;
	nod->right = NULL;
	return nod;
}

void insertFileABC(ABC*& arbore, ABC* nod) {
	if (arbore == NULL) {
		arbore = nod;
	}
	else {
		if (strcmp(arbore->infoFisier->numeFisier,nod->infoFisier->numeFisier)>0) {
			insertFileABC(arbore->left, nod);
		}
		else if (strcmp(arbore->infoFisier->numeFisier, nod->infoFisier->numeFisier)<0) {
			insertFileABC(arbore->right, nod);
		}
		else {
			insertFileABC(arbore->right, nod);
		}
	}
}

int papersNeeded(FILE* f) {
	int ch;
	int lines = 0;
	int papersNr;
	int maxLinesPerPaper = 100;
	while (!feof(f)) {
		ch = fgetc(f);
		if (ch == '\n') {
			lines++;
		}
	}
	papersNr = lines / maxLinesPerPaper;
	if (papersNr == 0) {
		papersNr++;
	}

	return papersNr;
}

void readFiles(ABC*& arbore) {
	char fpath[100];
	char fname[10];
	Fisier* file = new Fisier;

	system("cls");
	printf("== PRINTER USER ==\n");
	printf("\nPath to file > ");
	scanf("%s", &fpath);

	printf("Name for file > ");
	scanf("%s", &fname);
	file->numeFisier = (char*)malloc(strlen(fname) + 1);
	strcpy(file->numeFisier, fname);
	
	FILE* f = fopen(fpath, "r");
	char* source=NULL;
	if (f) {
		if (fseek(f, 0L, SEEK_END) == 0) {
			/* Get the size of the file. */
			long bufsize = ftell(f);
			if (bufsize == -1) { /* Error */ }

			/* Allocate our buffer to that size. */
			source = (char*)malloc(sizeof(char) * (bufsize + 1));

			/* Go back to the start of the file. */
			if (fseek(f, 0L, SEEK_SET) != 0) { /* Error */ }

			/* Read the entire file into memory. */
			size_t newLen = fread(source, sizeof(char), bufsize, f);
			if (ferror(f) != 0) {
				fputs("Error reading file", stderr);
			}
			else {
				source[newLen++] = '\0'; /* Just to be safe. */
			}

			file->continutFisier = (char*)malloc(sizeof(source) + 1);
			strcpy(file->continutFisier, source);

			file->nrPagesNeeded=papersNeeded(f);

			ABC* nodFile = createNodeABC(file);
			insertFileABC(arbore, nodFile);
			printf("File scanned successful!\n");
		}
		fclose(f);
		free(source);
	}
}

void printScannedFiles(ABC* listFiles) {
	if (listFiles) {
		printf("- %s\n", listFiles->infoFisier->numeFisier);
		printScannedFiles(listFiles->left);
		printScannedFiles(listFiles->right);
	}
	
}

void quitProgram() {
	//dezalocam memoria
	exit;
}



/* Menu */
void adminMenu(nodeLSI*&, ABC*&);
void userMenu(nodeLSI*&, ABC*&);

void mainMenu(nodeLSI*& printersList,ABC*& arboreFisiere) {
	//system("cls");
	printf("== SELECTEAZA TIPUL DE UTILIZATOR ==\n\n");
	printf("1. Administrator\n");
	printf("2. Utilizator\n");
	printf("\n0. Iesire\n\n");

	int cmd;

		printf("> ");
		scanf("%d", &cmd);
		int nrTryes = 0;
		int remaining = 3;
		int ok = 0;

		switch (cmd) {
		case 1:
			system("cls");
			printf("== ADMINISTRATOR ==\n\n");
			char pass[10];

			do {
				printf("Password: ");
				scanf("%s", &pass);
				printf("\n");
				if (strcmp(pass, "parola123") == 0) {
					ok = 1;
					break;
				}
				else {
					nrTryes++;
					remaining--;
					printf("Wrong password. Try again (%d).\n", remaining);
				}
			} while (nrTryes < 3);

			if (ok == 1) {
				adminMenu(printersList,arboreFisiere);
				break;
			}
			else {
				printf("Max attemps reached!\n");
				printf("0. Exit\n");
				break;
			}
		case 2:
			printf("== UTILIZATOR ==\n");
			userMenu(printersList,arboreFisiere);
			break;
		case 0:
			quitProgram();
		}
}

void adminMenu(nodeLSI*& printersList, ABC*& arboreFisiere) {
	printf("== ADMINISTRATOR ==\n\n");
	printf("1. Add Printer\n");
	printf("2. Show Status Printers\n");
	printf("3. Allocate resources\n");
	printf("4. Solve problems\n");
	printf("5. Return to main menu\n");
	printf("0. Exit\n");

	int cmd1;
	printf("> ");
	scanf("%d", &cmd1);
	switch (cmd1) {
	case 1:
	{
		system("cls");
		printf("===ADD A NEW PRINTER===\n\n");

		Printer* p = new Printer;
		char aux[20];

		printf("Printer ID: ");
		scanf("%s", &aux);
		//check for duplicate id
		if (checkPrinterDuplicateID(printersList, aux) == true) {
			char tmp[21];
			char const *randomNr = itoa(rand() % 100,tmp,10);
			strcat(aux, "_");
			strcat(aux, randomNr);
			printf("Id already used! New ID was generate!\n");
			checkPrinterDuplicateID(printersList, aux);
		}
		p->id = (char*)malloc(strlen(aux) + 1);
		
		strcpy(p->id, aux);

		printf("Paper capacity: ");
		scanf("%d", &p->paperCapacity);

		printf("Printer model: ");
		scanf("%s", &aux);
		p->model = (char*)malloc(strlen(aux) + 1);
		strcpy(p->model, aux);


		nodeLSI* node = createLSINode(p);
		if (insertInLSI(printersList, node)) {
			system("cls");
			printf("Printer added!\n\n");
			adminMenu(printersList,arboreFisiere);
			break;
		}
		else {
			printf("Printer was not added!\n\n");
			adminMenu(printersList,arboreFisiere);
			break;
		}
	}
	case 2:
		system("cls");
		printf("===PRINTERS STATUS====\n");
		printPrintersStatus(printersList);
		
		printf("\n1. Return to main menu\n");
		printf("0. Exit\n");
		if (scanf("%d") == 1) {
			adminMenu(printersList,arboreFisiere);
			break;
		}
		else if(scanf("%d")==0){
			mainMenu(printersList,arboreFisiere);
			break;
		}
	case 3:
		system("cls");
		printf("===ALLOCATE RESOURCES===\n");
		printf("1. Add paper\n");
		printf("0. Return to main menu\n");
		switch (scanf("%d")) {
		case 1:
			addPaper(printersList);
			adminMenu(printersList,arboreFisiere);
			break;
		case 0:
			quitProgram();
		}
		break;
	case 4:
		system("cls");
		printf("===Solve problems====\n");
		break;
	case 5:
		system("cls");
		mainMenu(printersList, arboreFisiere);
		break;
	case 0:
		quitProgram();
	}
}

void userMenu(nodeLSI*& printersList,ABC*& arboreFisiere) {
	printf("== PRINTER USER ==\n\n");
	printf("1. Scan document\n");
	printf("2. Print document \n");
	printf("3. Copy document \n");
	printf("4. Home menu \n");
	printf("0. Exit\n");
	
	int cmd;
	printf("> ");
	scanf("%d", &cmd);

	switch (cmd) {
	case 1:
		system("cls");
		printf("\n== PRINTER USER ==");
		readFiles(arboreFisiere);
		printf("\n\n0. Return to user menu\n\n> ");
		int auxCmd;
		scanf("%d", &auxCmd);
		if (auxCmd == 0) {
			mainMenu(printersList, arboreFisiere);
			break;
		}
		break;
		
	case 2:
		system("cls");
		printf("== PRINTER USER ==");
		printScannedFiles(arboreFisiere);
		break;
	case 3:
		printf("copy doc");
		break;
	case 4:
		mainMenu(printersList, arboreFisiere);
		break;
	case 0:
		quitProgram();
	}

}

void main() {
	/*Menu*/
	nodeLSI* printersList = nullptr;
	ABC* arboreFisiere = nullptr;
	mainMenu(printersList,arboreFisiere);	
	
}