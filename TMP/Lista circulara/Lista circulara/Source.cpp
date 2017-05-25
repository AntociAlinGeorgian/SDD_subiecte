#include<iostream>
#include<stdio.h>

struct Elev {
	int id;
	char* nume;
};

struct Nod {
	Elev* info;
	Nod* next;
	Nod* prev;
};

Nod* creareNod(Elev* e) {
	Nod* n = new Nod;
	n->info = e;
	n->next = NULL;
	n->prev = NULL;
	return n;
}


void inserareNodInceput(Nod*& lst, Nod* n) {
	if (lst == NULL) {
		n->next = n;
		n->prev = n;
		lst = n;
	}
	else {
		n->next = lst;
		n->prev = lst->prev;
		lst->prev = n;
		n->prev->next = n;
		lst = n;
	}
}

void inserareNodSfarsit(Nod*& lst, Nod* n) {
	if (lst == NULL) {
		n->next = n;
		n->prev = n;
		lst = n;
	}
	else {
		n->next = lst;
		n->prev = lst->prev;
		lst->prev = n;
		n->prev->next = n;
	}
}

void parcurgereLista(Nod* lst) {
	if (lst) {
		Nod* prim = lst;
		while (lst->next != prim) {
			printf("%d. %s\n", lst->info->id, lst->info->nume);
			lst = lst->next;
		}
		printf("%d. %s\n", lst->info->id, lst->info->nume);
	}
}

void citireFisier(Nod*& lst) {
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
			inserareNodInceput(lst, n);
		}
		fclose(f);
	}
}

void main() {
	Nod* lst = nullptr;
	citireFisier(lst);
	parcurgereLista(lst);
}