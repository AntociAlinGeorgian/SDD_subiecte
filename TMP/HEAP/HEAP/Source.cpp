#include<stdio.h>
#include<iostream>

struct Student {
	int id;
	char* nume;
};

struct Heap {
	Student* vectorStudenti;
	int nrElementeHeap; // nr de elemente existente in heap
	int memorieAlocata; //dimensiunea memoriei alocate (ca si nr de elemente) ptr heap
};

//prelucrari
//1. functie pentru interschimbarea a doua pozitii in vectorul heap
void interschimbarePozitii(Heap*& heap, int poz1, int poz2) {
	Student tmp = heap->vectorStudenti[poz1];
	heap->vectorStudenti[poz1] = heap->vectorStudenti[poz2];
	heap->vectorStudenti[poz2] = tmp;
}

//2. functie pentru reordonarea heap-ului
void filtrare(Heap*& heap, int index) {
	int indexMax = index;
	int indexStanga = 2 * index + 1;
	int indexDreapta = 2 * index + 2;

	if (indexStanga<heap->nrElementeHeap && heap->vectorStudenti[indexStanga].id > heap->vectorStudenti[indexMax].id) {
		indexMax = indexStanga;
	}
	if (indexDreapta<heap->nrElementeHeap && heap->vectorStudenti[indexDreapta].id > heap->vectorStudenti[indexMax].id) {
		indexMax = indexDreapta;
	}

	if (indexMax != index) {
		interschimbarePozitii(heap, indexMax, index);
		filtrare(heap, indexMax);
	}
}

//3. functie pentru construirea structurii heap
void construireHeap(Heap*& heap, Student vector[], int nrstudenti) {
	heap = (Heap*)malloc(sizeof(Heap));
	heap->memorieAlocata = nrstudenti;
	heap->nrElementeHeap = nrstudenti;
	heap->vectorStudenti = (Student*)malloc(sizeof(Student)*nrstudenti);
	for (int i = 0; i < nrstudenti; i++) {
		heap->vectorStudenti[i] = vector[i];
	}

	for (int i = (nrstudenti - 1) / 2; i >= 0; i--) {
		filtrare(heap, i);
	}
}

//4. functie pentru cresterea memoriei heap
void crestereMemorieAlocata(Heap*& heap) {
	Student* vectorNou = (Student*)malloc(sizeof(Student)*(heap->memorieAlocata + 1));
	for (int i = 0; i < heap->nrElementeHeap; i++) {
		vectorNou[i] = heap->vectorStudenti[i];
		free(heap->vectorStudenti);
		heap->vectorStudenti = vectorNou;
		heap->memorieAlocata++;
	}
}

//5. functie pentru inserarea unui element in heap
void insereazaElement(Heap*& heap, Student element) {
	if (heap->memorieAlocata == heap->nrElementeHeap) {
		crestereMemorieAlocata(heap);
	}
	heap->nrElementeHeap++;
	int index = heap->nrElementeHeap - 1;
	heap->vectorStudenti[index] = element;

	int indexParinte = (index - 1 / 2);
	while (indexParinte >= 0 && heap->vectorStudenti[index].id > heap->vectorStudenti[indexParinte].id) {
		interschimbarePozitii(heap, index, indexParinte);
		index = indexParinte;
		indexParinte = (index - 1) / 2;
	}
}

//6. functie pentru extragerea elementului maxim din heap
Student extragereMaxim(Heap*& heap) {
	heap->nrElementeHeap--;
	interschimbarePozitii(heap, 0, heap->nrElementeHeap);
	filtrare(heap, 0);
	return heap->vectorStudenti[heap->nrElementeHeap];
}

//7. citire din fisier
void citireFisier(Heap*& heap) {
	FILE* f = fopen("Text.txt", "r");
	int nrStudenti;
	Student vectorStudenti[100];
	int i = 0;
	if (f) {
		fscanf(f, "%d", &nrStudenti);
		while (!feof(f)) {
			Student stud;
			char tmp[50];
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