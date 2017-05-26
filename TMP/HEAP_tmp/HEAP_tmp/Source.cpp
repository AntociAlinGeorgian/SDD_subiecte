#include<stdio.h>
#include<iostream>

struct Student {
	int id;
	char* nume;
};

struct Heap{
	Student* vectorStudenti;
	int memorieAlocata;
	int nrElemente;
};

//1. interschimbare elemente
void interschimbareElemente(Heap*& heap, int poz1, int poz2) {
	Student aux = heap->vectorStudenti[poz1];
	heap->vectorStudenti[poz1] = heap->vectorStudenti[poz2];
	heap->vectorStudenti[poz2] = aux;
}

//2. filtrare
void filtrare(Heap*& heap, int index) {
	int indexMax = index;
	int indexStanga = 2 * index + 1;
	int indexDreapta = 2 * index + 2;

	if (indexStanga<heap->nrElemente && heap->vectorStudenti[index].id>heap->vectorStudenti[indexDreapta].id) {
		indexMax = indexStanga;
	}
	if (indexDreapta<heap->nrElemente && heap->vectorStudenti[index].id>heap->vectorStudenti[indexDreapta].id) {
		indexMax = indexDreapta;
	}

	if (index != indexMax) {
		interschimbareElemente(heap, index, indexMax);
		filtrare(heap, indexMax);
	}
}

//3. construireheap
void construireHeap(Heap*& heap, Student vector[], int nrStudenti) {
	heap = new Heap;
	heap->memorieAlocata = nrStudenti;
	heap->nrElemente = nrStudenti;
	int index = heap->nrElemente - 1;
	heap->vectorStudenti = (Student*)malloc(sizeof(Student)*nrStudenti);

	for (int i = 0; i < nrStudenti; i++) {
		heap->vectorStudenti[i] = vector[i];
	}

	for (int i = (nrStudenti - 1) / 2; i >= 0; i--) {
		filtrare(heap, i);
	}
}

//4. alocare memorie extra
void alocareMemorieExtra(Heap*& heap) {
	Student* vectorNou = (Student*)malloc(sizeof(heap->memorieAlocata + 1));
	for (int i = 0; i < heap->nrElemente; i++) {
		vectorNou[i] = heap->vectorStudenti[i];
		free(heap->vectorStudenti);
		heap->vectorStudenti[i] = vectorNou[i];
		heap->memorieAlocata++;
	}
}

//5. functie adaugare element in heap
void adaugareElement(Heap*& heap, Student stud) {
	if (heap->memorieAlocata == heap->nrElemente) {
		alocareMemorieExtra(heap);
	}
	heap->nrElemente++;
	int index = heap->nrElemente - 1;
	heap->vectorStudenti[index] = stud;
	int indexParinte = (index - 1) / 2;
	while (indexParinte >= 0 && heap->vectorStudenti[index].id > heap->vectorStudenti[index].id) {
		interschimbareElemente(heap, index, indexParinte);
		index = indexParinte;
		indexParinte = (index - 1) / 2;
	}
}

//6. extragere nod
Student extragereMaxim(Heap*& heap) {
	heap->nrElemente--;
	interschimbareElemente(heap, 0, heap->nrElemente);
	filtrare(heap, 0);
	return heap->vectorStudenti[heap->nrElemente];
}

//7. citire fisier
void citireFisier(Heap*& heap) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		int nrStudenti;
		Student vectorStudenti[100];
		int i = 0;

		fscanf(f, "%d", &nrStudenti);
		while (!feof(f)) {
			Student stud;
			char tmp[20];
			fscanf(f, "%s", &tmp);
			stud.nume = (char*)malloc(sizeof(tmp) + 1);
			strcpy(stud.nume, tmp);
			fscanf(f, "%d", &stud.id);
			vectorStudenti[i] = stud;
			i++;
		}
		construireHeap(heap, vectorStudenti, nrStudenti);
	}
	fclose(f);
}

//8. afisare
void afisare(Heap* heap) {
	for (int i = 0; i < heap->nrElemente; i++) {
		printf("%d. %s\n", heap->vectorStudenti[i].id, heap->vectorStudenti[i].nume);
	}
}

void main() {
	Heap* heap = NULL; 
	citireFisier(heap);
	afisare(heap);

	printf("\n\n");
	Student stud = extragereMaxim(heap);
	printf("maxim: %d. %s\n", stud.id, stud.nume);
	afisare(heap);
}