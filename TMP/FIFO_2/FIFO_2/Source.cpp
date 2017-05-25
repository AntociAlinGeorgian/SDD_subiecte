#include<iostream>
#include<stdio.h>

struct Elev {
	int id;
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

Coada* initCoada() {
	Coada* c = new Coada;
	c->prim = c->ultim = NULL;
	return c;
}

void inserareNod(Coada*& coada, Nod* nod) {
	if (coada->prim==NULL) {
		coada->prim = coada->ultim = nod;
	}
	else {
		coada->ultim->next = nod;
		coada->ultim = nod;
	}
}

void citireFisier(Coada*& coada) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Elev* e = new Elev;
			fscanf(f, "%d", &e->id);

			Nod* n = creareNod(e);
			inserareNod(coada, n);
		}
	}
}

Nod* extragere(Coada** c) {
	Nod* extras = (*c)->prim;
	(*c)->prim = extras->next;
	return extras;
}

void afisareCoada(Coada* c) {
	if (c) {
		Nod* tmp = c->prim;
		while (tmp->next != NULL) {
			Nod* extras = extragere(&c);
			printf("%d\n", extras->info->id);
			tmp = tmp->next;
		}
		Nod* extras = extragere(&c);
		printf("%d\n", extras->info->id);
	}
}

void main() {
	Coada* c = initCoada();
	citireFisier(c);
	afisareCoada(c);
}