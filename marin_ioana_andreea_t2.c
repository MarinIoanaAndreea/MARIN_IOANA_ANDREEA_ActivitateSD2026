/* Exemplu scurt student: clasa Televizor (stil profesor adaptat) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Televizor Televizor;

struct Televizor {
	int id;
	float diagonala; /* in inci */
	int smart;       /* 1 = da, 0 = nu */
	char* marca;
};

/* initializare: aloca si seteaza campurile */
struct Televizor initializare(int id, float diagonala, int smart, const char* marca) {
	struct Televizor t;
	t.id = id;
	t.diagonala = diagonala;
	t.smart = smart;
	t.marca = (char*)malloc(strlen(marca) + 1);
	strcpy(t.marca, marca);
	return t;
}

/* copiaza: intoarce o copie completa (deep copy) */
Televizor copiaza(Televizor t) {
	return initializare(t.id, t.diagonala, t.smart, t.marca);
}

/* afisare simpla */
void afisare(Televizor t) {
	printf("%d. %s - %.1f\" %s\n", t.id, t.marca, t.diagonala, t.smart ? "(Smart)" : "(Non-smart)");
}

void afisareVector(Televizor* v, int n) {
	for (int i = 0; i < n; i++) {
		afisare(v[i]);
	}
}

/* dezalocare: elibereaza toate stringurile si vectorul */
void dezalocare(Televizor** v, int* n) {
	for (int i = 0; i < *n; i++) {
		free((*v)[i].marca);
	}
	free(*v);
	*v = NULL;
	*n = 0;
}

/* filtreazaTelevizoare: copiaza televizoarele cu diagonala > prag */
void filtreazaTelevizoare(Televizor* v, int n, float prag, Televizor** out, int* outN) {
	*outN = 0;
	for (int i = 0; i < n; i++) if (v[i].diagonala > prag) (*outN)++;
	if (*outN == 0) { *out = NULL; return; }
	*out = (Televizor*)malloc(sizeof(Televizor) * (*outN));
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (v[i].diagonala > prag) {
			(*out)[j++] = copiaza(v[i]);
		}
	}
}

int main() {
	int n = 4;
	Televizor* tv = (Televizor*)malloc(sizeof(Televizor) * n);
	tv[0] = initializare(1, 32.0f, 0, "BrandX");
	tv[1] = initializare(2, 55.0f, 1, "BrandY");
	tv[2] = initializare(3, 43.5f, 1, "BrandZ");
	tv[3] = initializare(4, 24.0f, 0, "BrandLite");

	printf("Catalog televizoare:\n");
	afisareVector(tv, n);

	Televizor* mari = NULL;
	int m = 0;
	filtreazaTelevizoare(tv, n, 40.0f, &mari, &m);

	printf("\nTelevizoare cu diagonala > 40:\n");
	if (mari) {
		afisareVector(mari, m);
		dezalocare(&mari, &m);
	} else {
		printf("(niciunul)\n");
	}

	dezalocare(&tv, &n);
	return 0;
}

