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
		lst = n;
	}
	else {
		n->next = lst;
		lst->prev = n;
		lst = n;
	}
}

void inserareNodSf(Nod*& lst, Nod* n) {
	if (lst == NULL) {
		lst = n;
	}
	else {
		Nod* tmp = lst;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = n;
		n->prev = tmp;
	}
}

void parcurgereLista(Nod* lst) {
	if (lst) {
		Nod* tmp = lst;
		while (tmp->next != NULL) {
			printf("%d.  %s\n", tmp->info->id, tmp->info->nume);
			tmp = tmp->next;
		}
		printf("%d.  %s\n", tmp->info->id, tmp->info->nume);
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
			//inserareNodInceput(lst, n);
			inserareNodSf(lst, n);
		}
	}
}

void stergereNod(Nod*& lst, int id) {
	if (lst) {
		if (lst->info->id == id) {
			Nod* deSters = lst;
			lst = deSters->next;
			free(deSters->info->nume);
			free(deSters);
		}
		else {
			Nod* tmp = lst;
			while (tmp->next != NULL && tmp->next->info->id != id) {
				tmp = tmp->next;
			}
			if (tmp->next != NULL) {
				Nod* deSters = tmp->next;
				tmp->next = deSters->next;
				if (deSters->next != NULL) {
					deSters->next->prev = tmp;
				}
				free(deSters->info->nume);
				free(deSters);
			}
			else {
				printf("nu exista id\n");
			}
		}
	}
}

void main() {
	Nod* lst = nullptr;
	citireFisier(lst);
	stergereNod(lst, 3);
	parcurgereLista(lst);
}