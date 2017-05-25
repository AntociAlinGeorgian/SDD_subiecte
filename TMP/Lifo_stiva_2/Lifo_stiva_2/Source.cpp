#include<iostream>
#include<stdio.h>

struct Elev {
	int id;
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

void inserare(Nod*& stiva, Nod* n) {
	if (stiva == NULL) {
		stiva = n;
	}
	else {
		n->next = stiva;
		stiva = n;
	}
}

Nod* extragere(Nod** stiva) {
	Nod* extras = (*stiva);
	(*stiva) = extras->next;
	return extras;
}

void afisare(Nod* stiva) {
	if (stiva) {
		while (stiva->next != NULL) {
			Nod* extras = extragere(&stiva);
			printf("%d\n", extras->info->id);
		}
		Nod* extras = extragere(&stiva);
		printf("%d\n", extras->info->id);
	}
}

void citireFisier(Nod*& stiva) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Elev*  e = new Elev;
			fscanf(f, "%d", &e->id);
			Nod* n = creareNod(e);
			inserare(stiva, n);
		}
	}
}

void main() {
	Nod* stiva = nullptr;
	citireFisier(stiva);
	afisare(stiva);
}