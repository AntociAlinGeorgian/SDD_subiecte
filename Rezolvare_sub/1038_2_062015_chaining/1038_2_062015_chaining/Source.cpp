#include<iostream>
#include<stdio.h>

enum stareTask{
	DESCHIS,IN_LUCRU,DUPLICAT,REZOLVAT,INCHIS
};

struct Task {
	char* idTask;
	char* dataAsignarii;
	char* numeInginerAsignat;
	int nivelComplexitate;
	stareTask stare;
};

struct Nod {
	Task* infoNod;
	Nod* next;
};

struct HashTable {
	int dimHT;
	Nod** vector;
};

int fhash(char* numeInginer, int dimHT) {
	return numeInginer[0]%dimHT;
}

HashTable* initHT(int dimHT) {
	HashTable* ht = new HashTable;
	ht->dimHT = dimHT;
	ht->vector = (Nod**)malloc(sizeof(Nod*)*dimHT);
	for (int i = 0; i < ht->dimHT; i++) {
		ht->vector[i] = NULL;
	}

	return ht;
}

Nod* creareNod(Task* t) {
	Nod* n = new Nod;
	n->infoNod = t;
	n->next = NULL;
	return n;
}

void inserareNod(Nod*& lista, Nod* nod) {
	if (lista == NULL) {
		lista = nod;
	}
	else {
		Nod* tmp = lista;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = nod;
	}
}

void inserareHT(HashTable*& ht, Nod* nod) {
	int poz = fhash(nod->infoNod->numeInginerAsignat, ht->dimHT);

	Nod* lista = ht->vector[poz];
	inserareNod(lista, nod);
	ht->vector[poz] = lista;
}

void citireFisier(HashTable*& ht) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Task* t = new Task;
			char aux[20];
			fscanf(f, "%s", &aux);
			t->idTask = (char*)malloc(strlen(aux) + 1);
			strcpy(t->idTask, aux);
			fscanf(f, "%s", &aux);
			t->dataAsignarii = (char*)malloc(strlen(aux) + 1);
			strcpy(t->dataAsignarii, aux);
			fscanf(f, "%s", &aux);
			t->numeInginerAsignat = (char*)malloc(strlen(aux) + 1);
			strcpy(t->numeInginerAsignat, aux);
			fscanf(f, "%d", &t->nivelComplexitate);
			fscanf(f, "%d", &t->stare);

			Nod* n = creareNod(t);
			inserareHT(ht, n);
		}
	}
}

void afisareHT(HashTable* ht) {
	for (int i = 0; i < ht->dimHT; i++) {
		Nod* lista = ht->vector[i];
		while (lista != NULL) {
			printf("%s. %s %s %d %d\n", lista->infoNod->idTask, lista->infoNod->dataAsignarii, lista->infoNod->numeInginerAsignat, lista->infoNod->nivelComplexitate, lista->infoNod->stare);
			lista = lista->next;
		}
	}
}

void redenumireInginer(HashTable*& ht, char* numeInginer) {
	if (ht) {
		int poz = fhash(numeInginer, ht->dimHT);
		Nod* lista = ht->vector[poz];
		int ok = 0;
		if (lista != NULL) {
			Nod* tmp = lista;
			while (tmp != NULL) {
				if (strcmp(tmp->infoNod->numeInginerAsignat, numeInginer) == 0) {
					printf("Inginer gasit");
					ok = 1;
					char aux[20];
					printf("\nNoul nume: ");
					scanf("%s", &aux);
					tmp->infoNod->numeInginerAsignat = (char*)malloc(strlen(aux) + 1);
					strcpy(tmp->infoNod->numeInginerAsignat, aux);

					/*Log*/
					FILE* f = fopen("Text.txt", "a");
					if (f) {
						fprintf(f, "\n[LOG] idTask: %s -> %s to %s\n", tmp->infoNod->idTask, aux, tmp->infoNod->numeInginerAsignat);
						fclose(f);
					}

				}
				tmp = tmp->next;
			}
			if (ok == 0) {
				printf("Nu exista numeInginer cautat!\n");
			}
		}
		else {
			printf("Lista null\n");
		}
	}
}


void stergereTaskuri(HashTable*& ht) {
	if (ht) {
		for (int i = 0; i < ht->dimHT; i++) {
			Nod* lst = ht->vector[i];
			if (lst != 0) {
				if (lst->infoNod->stare == 5) {
					Nod* deSters = lst;
					lst = deSters->next;
					free(deSters->infoNod->dataAsignarii);
					free(deSters->infoNod->idTask);
					free(deSters->infoNod->numeInginerAsignat);
					free(deSters);
				}
				else {
					Nod* tmp = lst;
					while (tmp->next != NULL && tmp->next->infoNod->stare != 5) {
						tmp = tmp->next;
					}
					if (tmp->next != NULL) {
						Nod* deSters = tmp->next;
						tmp->next = deSters->next;
						free(deSters->infoNod->dataAsignarii);
						free(deSters->infoNod->idTask);
						free(deSters->infoNod->numeInginerAsignat);
						free(deSters);
					}
					else {
						printf("Nu exista task-uri inchise\n");
					}
				}
			}
		}
	}
}
void main() {
	HashTable* ht = initHT(5);
	citireFisier(ht);
	afisareHT(ht);
	printf("\n\n");
	/*redenumireInginer(ht, "Foo");
	printf("\n\n");
	afisareHT(ht);
	*/
	stergereTaskuri(ht);
	printf("\n\n");
	afisareHT(ht);
}