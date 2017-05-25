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

struct Coada {
	Nod* prim;
	Nod* ultim;
};

Nod* creareNod(Elev* e) {
	Nod* n = new Nod;
	n->info = e;
	n->next = NULL;
	return n;
}

void initCoada(Coada*& c) {
	c->prim = c->ultim = NULL;
}

void inserareNod(Coada*& c, Nod* n) {
	if (c->prim == NULL) {
		c->prim = c->ultim = n;
	}
	else {
		c->ultim->next = n;
		c->ultim = n;
	}
}

Nod* extragereNod(Coada** c) {
	Nod* extrage = (*c)->prim;
	(*c)->prim = extrage->next;
	return extrage;
}

void parcurgereLista(Coada* c) {
	if (c) {
		Nod* tmp = c->prim;
		while (tmp->next != NULL) {
			printf("%d. %s\n", tmp->info->id, tmp->info->nume);
			tmp = tmp->next;
		}
		printf("%d. %s\n", tmp->info->id, tmp->info->nume);
	}
}

void citireFisier(Coada*& c) {
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
			inserareNod(c, n);
		}
	}
}

void main() {
	Coada* c = new Coada;
	initCoada(c);
	citireFisier(c);
	parcurgereLista(c);
}