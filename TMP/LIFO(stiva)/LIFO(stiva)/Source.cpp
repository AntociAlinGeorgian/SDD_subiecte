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


void inserareNod(Nod*& stiva, Nod* n) {
	if (stiva == NULL) {
		stiva = n;
	}
	else {
		n->next = stiva;
		stiva = n;
	}
}

Nod* extragere(Nod** stiva) {
	Nod* tmp = (*stiva);
	(*stiva) = tmp->next;
	return tmp;
}

void citire(Nod*& stiva) {
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
			inserareNod(stiva, n);
		}
	}
}

void parcurgere(Nod* stiva) {
	if (stiva) {
		while (stiva != NULL) {
			Nod* tmp = extragere(&stiva);
			printf("%d. %s\n", tmp->info->id, tmp->info->nume);
		}
	}
}

void main() {
	Nod* stiva = nullptr;
	citire(stiva);
	parcurgere(stiva);
}