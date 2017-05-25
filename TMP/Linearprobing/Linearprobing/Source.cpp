#include<iostream>
#include<stdio.h>

struct Elev {
	int id;
	char* nume;
};

struct Nod {
	Elev* info;
	Nod* next;
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

struct Hashtable {
	int dim;
	Nod** vector;
};

Hashtable* initHt(int dim) {
	Hashtable* ht = new Hashtable;
	ht->dim = dim;
	ht->vector = (Nod**)malloc(sizeof(Nod*)*ht->dim);
	for (int i = 0; i < ht->dim; i++) {
		ht->vector[i] = NULL;
	}
	return ht;
}

void inserareHT(Hashtable*& ht, Nod* n) {
	int poz = fhash(n->info->nume, ht->dim);

	if (ht->vector[poz] == NULL) {
		ht->vector[poz] = n;
	}
	else {
		while (ht->vector[poz] != NULL && poz < ht->dim) {
			poz++;
		}
		if (poz == ht->dim) {
			int poz = fhash(n->info->nume, ht->dim);

			while (ht->vector[poz] != NULL && poz > 0) {
				poz--;
			}
			if (poz == 0) {
				printf("coliziune!\n");
			}
			else {
				ht->vector[poz] = n;
			}
		}
		else {
			ht->vector[poz] = n;
		}
	}
}

void citireFisier(Hashtable*& ht) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Elev* e = new Elev;
			fscanf(f, "%d", &e->id);
			char aux[10];
			fscanf(f, "%s", &aux);
			e->nume = (char*)malloc(sizeof(aux) + 1);
			strcpy(e->nume, aux);

			Nod* n = creareNod(e);
			inserareHT(ht, n);
		}
	}
}

void parcurgereHT(Hashtable* ht) {
	if (ht) {
		for (int i = 0; i < ht->dim; i++) {
			if (ht->vector[i] != NULL) {
				printf("%d. %s\n", ht->vector[i]->info->id, ht->vector[i]->info->nume);
			}
		}
	}
}

void main() {
	Hashtable* ht = initHt(21);
	citireFisier(ht);
	parcurgereHT(ht);
}