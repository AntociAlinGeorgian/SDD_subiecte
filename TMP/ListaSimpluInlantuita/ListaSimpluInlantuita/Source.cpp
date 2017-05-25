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
	Nod* n = (Nod*)malloc(sizeof(Nod));
	n->info = e;
	n->next = NULL;
	return n;
}

void inserareNodInceput(Nod*& lst, Nod* n) {
	if (lst == NULL) {
		lst = n;
	}
	else {
		n->next = lst;
		lst = n;
	}
}

void inserareNodSfarsit(Nod*& lst, Nod* n) {
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

void parcurgereLista(Nod* lst) {
	if (lst) {
		while (lst->next!= NULL) {
			printf("%d %s\n", lst->info->id, lst->info->nume);
			lst = lst->next;
		}
		printf("%d %s\n", lst->info->id, lst->info->nume);
	}
}

void citireFisier(Nod*& lst) {
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
			//inserareNodInceput(lst, n);
			inserareNodSfarsit(lst, n);
		}
	}
}

void stergereId(Nod*& lst, int id) {
	if (lst) {
		if (lst->info->id == id) {
			Nod* deSters = lst;
			lst = deSters->next;
			free(deSters->info->nume);
			free(deSters);
		}
		else {
			Nod* tmp = lst;
			while (tmp->next != NULL && id != tmp->next->info->id) {
				tmp = tmp->next;
			}
			if (tmp->next != NULL) {
				Nod* deSters = tmp->next;
				tmp->next = deSters->next;
				free(deSters->info->nume);
				free(deSters);
			}
			else {
				printf("nu s-a gasit id\n");
			}
		}
	}
}

void main() {
	Nod* lst = nullptr;
	citireFisier(lst);
	stergereId(lst, 3);
	parcurgereLista(lst);
}