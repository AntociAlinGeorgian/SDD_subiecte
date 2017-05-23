#include<iostream>
#include<stdio.h>

struct Tranzactie {
	char* numeBeneficiar;
	float sumaPlata;
	char* IBAN;
	char* dataPlatii;
	int idTranzactie;
};

struct Nod {
	Tranzactie* info;
	Nod* next;
};

struct Coada {
	Nod* prim;
	Nod* ultim;
};


struct ABC {
	Tranzactie* info;
	ABC* left;
	ABC* right;
};

ABC* creareNodABC(Tranzactie* t) {
	ABC* nod = new ABC;
	nod->info = t;
	nod->left = NULL;
	nod->right = NULL;
	return nod;
}

void inserareABC(ABC*& arbore, ABC* nod) {
	if (arbore == NULL) {
		arbore = nod;
	}
	else {
		if (arbore->info->idTranzactie > nod->info->idTranzactie) {
			inserareABC(arbore->left, nod);
		}
		else if (arbore->info->idTranzactie < nod->info->idTranzactie) {
			inserareABC(arbore->right, nod);
		}
		else {
			inserareABC(arbore->right, nod);
		}
	}
}

void parcurgereABC(ABC* arbore) {
	if (arbore) {
		parcurgereABC(arbore->left);
		printf("%d\n", arbore->info->idTranzactie);
		parcurgereABC(arbore->right);
	}
}


Nod* creareNod(Tranzactie* t) {
	Nod* n = new Nod;
	n->info = t;
	n->next = NULL;
	return n;
}

void initCoada(Coada*& c) {
	c->prim = c->ultim = NULL;
}

void inserareCoada(Coada*& c, Nod* n) {
	if (c->prim == NULL) {
		c->prim = c->ultim = n;
	}
	else {
		c->ultim->next = n;
		c->ultim = n;
	}
}


Nod* extragere(Coada** c) {
	Nod* tmp = (*c)->prim;
	(*c)->prim = tmp->next;
	return tmp;
}

void parcurgereLista(Coada* c,ABC*& arbore) {
	if (c) {
		Nod* tmp = c->prim;
		while (tmp != NULL) {
			printf("%d\n", tmp->info->idTranzactie);
			Tranzactie* t = new Tranzactie;

			t->dataPlatii = (char*)malloc(sizeof(tmp->info->dataPlatii)+1);
			strcpy(t->dataPlatii, tmp->info->dataPlatii);
			t->IBAN= (char*)malloc(sizeof(tmp->info->IBAN)+1);
			strcpy(t->IBAN, tmp->info->IBAN);
			t->idTranzactie = tmp->info->idTranzactie;
			t->numeBeneficiar= (char*)malloc(strlen(tmp->info->numeBeneficiar)+1);
			strcpy(t->numeBeneficiar, tmp->info->numeBeneficiar);
			t->sumaPlata = tmp->info->sumaPlata;

			ABC* nodABC = creareNodABC(t);
			inserareABC(arbore, nodABC);

			//Nod* deExtras = tmp;
			tmp = tmp->next;
			/*free(deExtras->info->dataPlatii);
			free(deExtras->info->IBAN);
			free(deExtras->info->numeBeneficiar);
			free(deExtras->info);
			free(deExtras);*/
		}
	}
}

int detNrTranzactii(Coada* c, char* dataTranzactii) {
	int nrTranz = 0;
	if (c) {
		Nod* tmp = c->prim;
		while (tmp != NULL) {
			if (strcmp(tmp->info->dataPlatii, dataTranzactii) == 0) {
				nrTranz++;
			}
			tmp = tmp->next;
		}
	}
	return nrTranz;
}

void main() {
	Coada* c = new Coada;
	c->prim = c->ultim = NULL;

	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Tranzactie* t = new Tranzactie;
			char aux[20];
			fscanf(f, "%s", &aux);
			t->numeBeneficiar = (char*)malloc(strlen(aux) + 1);
			strcpy(t->numeBeneficiar, aux);

			fscanf(f, "%f", &t->sumaPlata);

			fscanf(f, "%s", &aux);
			t->IBAN = (char*)malloc(strlen(aux) + 1);
			strcpy(t->IBAN, aux);

			fscanf(f, "%s", &aux);
			t->dataPlatii = (char*)malloc(sizeof(aux) + 1);
			strcpy(t->dataPlatii, aux);

			fscanf(f, "%d", &t->idTranzactie);

			Nod* n = creareNod(t);
			inserareCoada(c, n);
		}
	}

	ABC* arbore = nullptr;
	/*afisare coada*/
	parcurgereLista(c,arbore);

	printf("Nr tranzactii: %d\n", detNrTranzactii(c, "19may"));

	parcurgereABC(arbore);
}