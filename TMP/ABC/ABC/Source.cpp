#include<iostream>
#include<stdio.h>

struct Elev {
	int id;
};

struct ABC {
	Elev* info;
	ABC* left;
	ABC* right;
};

ABC* creareNod(Elev* e) {
	ABC* arbore = new ABC;
	arbore->info = e;
	arbore->left = NULL;
	arbore->right = NULL;
	return arbore;
}

void inserareABC(ABC*& arbore, ABC* nod) {
	if (arbore == NULL) {
		arbore = nod;
	}
	else {
		if (arbore->info->id > nod->info->id) {
			inserareABC(arbore->left, nod);
		}
		else if(arbore->info->id < nod->info->id) {
			inserareABC(arbore->right, nod);
		}
		else {
			inserareABC(arbore->right, nod);
		}
	}
}

void citireFisier(ABC*& arbore) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Elev* e = new Elev;
			fscanf(f, "%d", &e->id);
			ABC* nod = creareNod(e);
			inserareABC(arbore, nod);
		}
	}
}

void parcurgere(ABC* arbore) {
	if (arbore) {
		parcurgere(arbore->left);
		printf("%d\n", arbore->info->id);
		parcurgere(arbore->right);
	}
}

void stergereLogica(ABC*& radacina, ABC*& sleft) {
	//caut cel mai mare subarbore stang
	if (sleft->right) {
		stergereLogica(radacina, sleft->right);
	}
	else {
		Elev* deSters = radacina->info;
		radacina->info = sleft->info;
		ABC* nodDeInlocuit = sleft;
		sleft = sleft->left;
		free(deSters);
		free(sleft);
		free(nodDeInlocuit);
	}
}

void stergereNod(ABC*& arbore, int id) {
	if (arbore) {
		if (arbore->info->id > id) {
			stergereNod(arbore->left, id);
		}
		else if (arbore->info->id < id) {
			stergereNod(arbore->right, id);
		}
		else {
			//1. este nod frunza, nu are niciun descendent
			if (arbore->right == NULL && arbore->left == NULL) {
				//dezaloc memoria si anunt ca nodul a devenit null
				free(arbore->info);
				free(arbore);
			}
			else if (arbore->right != NULL && arbore->left == NULL) {
				ABC* sters = arbore;
				arbore = arbore->right;
				free(sters->info);
				free(sters);
			}
			else if (arbore->right == NULL && arbore->left != NULL) {
				ABC* sters = arbore;
				arbore = arbore->left;
				free(sters->info);
				free(sters);
			}
			else {
				stergereLogica(arbore, arbore->left);
			}
		}
	}
}

void main() {
	ABC* arbore = nullptr;
	citireFisier(arbore);
	stergereNod(arbore, 30);
	parcurgere(arbore);
}