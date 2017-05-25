#include<iostream>
#include<stdint.h>

struct Elev {
	int id;
	char* nume;
};

struct Nod {
	Elev* info;
	Nod* next;
};

struct HashTable {
	int dimHT;
	Nod** vector;
};

Nod* creareNod(Elev* e) {
	Nod* n = new Nod;
	n->info = e;
	n->next = NULL;
	return n;
}

int fhash(char* nume, int dim) {
	return nume[0] % dim;
}

HashTable* initHT(int dim) {
	HashTable* ht = new HashTable;
	ht->dimHT = dim;
	ht->vector = (Nod**)malloc(sizeof(Nod*)*ht->dimHT);
	for (int i = 0; i < ht->dimHT; i++) {
		ht->vector[i] = NULL;
	}
	return ht;
}

void inserareNodLista(Nod*& lst, Nod* n) {
	if (lst == NULL) {
		lst = n;
	}
	else {
		Nod* tmp = lst;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = n;
	}
}

void inserareHT(HashTable*& ht, Nod* n) {
	int poz = fhash(n->info->nume, ht->dimHT);

	Nod* lst = ht->vector[poz];
	inserareNodLista(lst, n);
	ht->vector[poz] = lst;
}

void citireFisier(HashTable*& ht) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Elev* e = new Elev;
			fscanf(f, "%d", &e->id);
			char aux[20];
			fscanf(f, "%s", &aux);
			e->nume = (char*)malloc(sizeof(aux) + 1);
			strcpy(e->nume, aux);

			Nod* n = creareNod(e);
			inserareHT(ht, n);
		}
	}
}

void parcurgereLista(HashTable* ht) {
	if (ht) {
		for (int i = 0; i < ht->dimHT; i++) {
			if (ht->vector[i] != NULL) {
				Nod* tmp = ht->vector[i];
				while (tmp->next != NULL) {
					printf("%d. %s\n", tmp->info->id, tmp->info->nume);
					tmp = tmp->next;
				}
				printf("%d. %s\n", tmp->info->id, tmp->info->nume);
			}
		}
	}
}

void main() {
	HashTable* ht = initHT(27);
	citireFisier(ht);
	parcurgereLista(ht);
}