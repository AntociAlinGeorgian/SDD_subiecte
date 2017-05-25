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

//ABC
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


/* hash table */
struct nodeHT {
	Fisier* info;
	nodeHT* next;
};

struct HashTable {
	nodeHT** vector;
	int dimHT;
};

int fhash(char* id, int dim) {
	return id[0] % dim;
}

HashTable* initHT(int dim) {
	HashTable* ht = new HashTable;
	ht->dimHT = dim;
	ht->vector = (nodeHT**)malloc(sizeof(nodeHT*)*dim);

	for (int i = 0; i < ht->dimHT; i++) {
		ht->vector[i] = NULL;
	}

	return ht;
}

nodeHT* creareNod(Fisier* f) {
	nodeHT* n = new nodeHT;
	n->info = f;
	n->next = NULL;
	return n;
}

void insertNodeHT(nodeHT*& lst, nodeHT* nod) {
	if (lst == NULL) {
		lst = nod;
	}
	else {
		nodeHT* tmp = lst;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = nod;
	}
}

void inserareHT(HashTable*& ht, nodeHT* n) {
	int poz = fhash(n->info->numeFisier, ht->dimHT);

	nodeHT* lista = ht->vector[poz];
	insertNodeHT(lista, n);

	ht->vector[poz] = lista;
}

// globale
nodeLSI* printersList = NULL;
ABC* arboreFisiere = NULL;
HashTable* ht = initHT(27);

void copyFilesFromABCtoHT(HashTable*& ht, ABC* arbore) {
	if (ht) {
		Fisier* f = new Fisier;

		f->continutFisier = arbore->infoFisier->continutFisier;
		f->nrPagesNeeded = arbore->infoFisier->nrPagesNeeded;
		f->numeFisier = arbore->infoFisier->numeFisier;

		nodeHT* node = creareNod(f);
		inserareHT(ht, node);
		copyFilesFromABCtoHT(ht, arbore->left);
		copyFilesFromABCtoHT(ht, arbore->right);

		printf("Fisiere copiate cu succes din ABC in HT!\n");
	}
}

nodeLSI* createLSINode(Printer* info) {
	nodeLSI* node = new nodeLSI;
	node->info = info;
	node->next = NULL;
	return node;
}

bool checkPrinterDuplicateID(nodeLSI* lst, char* id) {
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
void sortPrinterList() {
	nodeLSI *t, *t1, *t2, *tt;
	if (printersList == NULL)
		printf("\nNu exista imprimante.");
	else
	{
		t1 = printersList->next;
		while (t1 != NULL)
		{
			t2 = t1->next;
			for (t = printersList; t != t1; t = t->next) {
				if (t1->info->paperCapacity < t->info->paperCapacity)
				{
					t1->next = t;
					for (tt = printersList; tt->next != t1; tt = tt->next);

					tt->next = t2;
					if (t == printersList)
						printersList = t1;
					else
					{
						for (tt = printersList; tt->next != t; tt = tt->next);

						tt->next = t1;
					}
					break;
				}
			}
			t1 = t2;
		}
	}
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

nodeLSI* searchPrinterByID(char* id)
{
	if (printersList == NULL)
		return NULL;
	else
	{
		nodeLSI* tmp = printersList;
		while (tmp != NULL)
		{
			if (strcmp(tmp->info->id, id) == 0)
				return tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return NULL;
	}
}

/* USER -> ABC */


ABC* createNodeABC(Fisier* info) {
	ABC* nod = new ABC;
	nod->infoFisier = new Fisier;
	nod->infoFisier->nrPagesNeeded = info->nrPagesNeeded;
	nod->infoFisier->numeFisier = (char*)malloc(strlen(info->numeFisier) + 1);
	strcpy(nod->infoFisier->numeFisier, info->numeFisier);

	nod->infoFisier->continutFisier = (char*)malloc(strlen(info->continutFisier) + 1);
	strcpy(nod->infoFisier->continutFisier, info->continutFisier);
	nod->left = NULL;
	nod->right = NULL;
	return nod;
}

void insertFileABC(ABC*& arbore, ABC* nod) {
	if (arbore == NULL) {
		arbore = nod;
	}
	else {
		if (strcmp(arbore->infoFisier->numeFisier, nod->infoFisier->numeFisier)>0) {
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

void readFiles() {
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

	FILE* f = fopen(fpath, "rb");
	char* buffer = 0;
	long length;
	if (f) {
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = (char*)malloc(length);
		if (buffer)
		{
			fread(buffer, 1, length, f);

			file->continutFisier = (char*)malloc(strlen(buffer) + 1);
			strcpy(file->continutFisier, buffer);

			file->nrPagesNeeded = papersNeeded(f);

			ABC* nodFile = createNodeABC(file);
			insertFileABC(arboreFisiere, nodFile);
			printf("File scanned successful!\n");
		}
		fclose(f);
		free(buffer);
		free(file->numeFisier);
		free(file->continutFisier);
		free(file);
	}
}

void updateNrPages(nodeLSI*& printerList1, char* id, int nr)
{
	nodeLSI* tmp = printerList1;
	while (tmp != NULL)
	{
		if (strcmp(tmp->info->id, id) == 0)
			tmp->info->paperCapacity -= nr;
		tmp = tmp->next;
	}
}


void printScannedFiles(ABC* listFiles) {
	if (listFiles) {
		printf("\n- %s\n", listFiles->infoFisier->numeFisier);
		printf("\n Alegeti o imprimanta disponibila: \n");
		printPrintersStatus(printersList);
		printf("\n Imprimanta: >");
		char auxPrinter[10];
		scanf("%s", &auxPrinter);
		int nrPag = listFiles->infoFisier->nrPagesNeeded;
		nodeLSI* printerCk = searchPrinterByID(auxPrinter);
		if (printerCk != NULL)
		{
			if (printerCk->info->paperCapacity < nrPag)
				printf("\nAceasta imprimanta nu are suficiente foi. Alegeti un alt model.\n");
			else {
				updateNrPages(printersList, auxPrinter, nrPag);
				printf("Printat cu success!\n");
			}
		}
		else {
			printf("\n\Aceasta imprimanta nu este disponibila. n");
		}


		printScannedFiles(listFiles->left);
		printScannedFiles(listFiles->right);
	}

}

ABC* searchABCNode(ABC* arbore, char* cheie) {
	if (strcmp(arbore->infoFisier->numeFisier, cheie) > 0) {
		return searchABCNode(arbore->left, cheie);
	}
	else if (strcmp(arbore->infoFisier->numeFisier, cheie)<0) {
		return searchABCNode(arbore->right, cheie);
	}
	else if (strcmp(arbore->infoFisier->numeFisier, cheie) == 0) {
		return arbore;
	}
	else {
		return NULL;
	}
}

/* Menu */
void adminMenu(nodeLSI*&, ABC*&);
void userMenu(nodeLSI*&, ABC*&);

void copyFileFromScanned(ABC* arboreFisiere) {
	if (arboreFisiere) {
		printf("\n");
		printf("File name: > ");
		char aux[10];
		char* nameScanned;
		scanf("%s", &aux);
		nameScanned = (char*)malloc(strlen(aux) + 1);
		strcpy(nameScanned, aux);

		ABC* result = searchABCNode(arboreFisiere, nameScanned);
		if (result != NULL) {
			printf("%s Gasit", result->infoFisier->numeFisier);
			strcat(nameScanned, "_scanned");

			FILE* f = fopen(nameScanned, "a");
			if (f) {
				fprintf(f, "%s", result->infoFisier->continutFisier);
				printf("Success!\n");
			}
			fclose(f);
		}
		else {
			printf("\nWrong name.\n");
			userMenu(printersList, arboreFisiere);
		}
	}
	else {
		//system("cls");
		printf("No files scanned!\n");
		userMenu(printersList, arboreFisiere);
	}

}




void mainMenu(nodeLSI*& printersList, ABC*& arboreFisiere) {
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
			adminMenu(printersList, arboreFisiere);
			break;
		}
		else {
			printf("Max attemps reached!\n");
			printf("0. Exit\n");
			break;
		}
	case 2:
		printf("== UTILIZATOR ==\n");
		userMenu(printersList, arboreFisiere);
		break;
	case 0:
		exit;
	}
}

void adminMenu(nodeLSI*& printersList, ABC*& arboreFisiere) {
	printf("== ADMINISTRATOR ==\n\n");
	printf("1. Add Printer\n");
	printf("2. Show Status Printers\n");
	printf("3. Allocate resources\n");
	printf("4. Return to main menu\n");

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
			char const *randomNr = itoa(rand() % 100, tmp, 10);
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
			adminMenu(printersList, arboreFisiere);
			break;
		}
		else {
			printf("Printer was not added!\n\n");
			adminMenu(printersList, arboreFisiere);
			break;
		}
	}
	case 2:
		system("cls");
		printf("===PRINTERS STATUS====\n");
		sortPrinterList();
		printPrintersStatus(printersList);

		printf("\n1. Return to menu\n");
		if (scanf("%d") == 1) {
			adminMenu(printersList, arboreFisiere);
			break;
		}
		else if (scanf("%d") == 0) {
			mainMenu(printersList, arboreFisiere);
			break;
		}
	case 3:
		system("cls");
		printf("===ALLOCATE RESOURCES===\n");
		printf("1. Add paper\n>");
		switch (scanf("%d")) {
		case 1:
			addPaper(printersList);
			adminMenu(printersList, arboreFisiere);
			break;
		}
		break;
	case 4:
		//system("cls");
		mainMenu(printersList, arboreFisiere);
		break;
	}
}

void userMenu(nodeLSI*& printersList, ABC*& arboreFisiere) {
	printf("== PRINTER USER ==\n\n");
	printf("1. Scan document\n");
	printf("2. Print document \n");
	printf("3. Copy document \n");
	printf("0. Exit\n");

	int cmd;
	printf("> ");
	scanf("%d", &cmd);

	switch (cmd) {
	case 1:
		system("cls");
		printf("\n== PRINTER USER ==");
		readFiles();
		printf("\n\n0. Return to user menu\n\n> ");
		int auxCmd;
		scanf("%d", &auxCmd);
		if (auxCmd == 0) {
			userMenu(printersList, arboreFisiere);
			break;
		}
		break;

	case 2:
		system("cls");
		printf("== PRINTER USER ==");
		printScannedFiles(arboreFisiere);
		printf("\n\n0. Return to user menu\n\n> ");
		int auxCmd1;
		scanf("%d", &auxCmd1);
		if (auxCmd1 == 0) {
			userMenu(printersList, arboreFisiere);
			break;
		}
		break;
	case 3:
		printf("== PRINTER USER ==");
		copyFileFromScanned(arboreFisiere);
		//copyFilesFromABCtoHT(ht, arboreFisiere);
		printf("\n\n0. Return to user menu\n\n> ");
		int auxCmd3;
		scanf("%d", &auxCmd3);
		if (auxCmd3 == 0) {
			userMenu(printersList, arboreFisiere);
			break;
		}
		break;
	case 0:
		exit;
	}

}

void main() {
	/*Menu*/

	mainMenu(printersList, arboreFisiere);

}
