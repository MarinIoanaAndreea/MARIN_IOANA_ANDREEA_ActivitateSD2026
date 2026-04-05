#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carte Carte;
typedef struct Nod Nod;

struct Carte {
    int id;
    int nrPagini;
    float pret;
    char* titlu;
    char* autor;
};

struct Nod {
    Carte info;
    Nod* next;
};

Carte creareCarte(int id, int nrPagini, float pret, const char* titlu, const char* autor) {
    Carte c;
    c.id = id;
    c.nrPagini = nrPagini;
    c.pret = pret;
    c.titlu = (char*)malloc(strlen(titlu) + 1);
    strcpy(c.titlu, titlu);
    c.autor = (char*)malloc(strlen(autor) + 1);
    strcpy(c.autor, autor);
    return c;
}

void afisareCarte(Carte c) {
    printf("Id: %d\n", c.id);
    printf("Titlu: %s\n", c.titlu);
    printf("Autor: %s\n", c.autor);
    printf("Nr pagini: %d\n", c.nrPagini);
    printf("Pret: %.2f\n\n", c.pret);
}

void push(Nod** varf, Carte c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next = *varf;
    *varf = nou;
}

int pop(Nod** varf, Carte* c) {
    if (*varf == NULL) {
        return 0;
    }

    Nod* aux = *varf;
    *c = aux->info;
    *varf = aux->next;
    free(aux);
    return 1;
}

void afisareStiva(Nod* varf) {
    while (varf) {
        afisareCarte(varf->info);
        varf = varf->next;
    }
}

float calculeazaPretMediu(Nod* varf) {
    float suma = 0;
    int nr = 0;
    while (varf) {
        suma += varf->info.pret;
        nr++;
        varf = varf->next;
    }
    if (nr > 0) {
        return suma / nr;
    }
    return 0;
}

void dezalocareStiva(Nod** varf) {
    while (*varf) {
        Nod* aux = *varf;
        *varf = (*varf)->next;
        free(aux->info.titlu);
        free(aux->info.autor);
        free(aux);
    }
}

int main() {
    Nod* stiva = NULL;

    push(&stiva, creareCarte(1, 320, 45.5f, "Morometii", "Marin Preda"));
    push(&stiva, creareCarte(2, 210, 39.9f, "Ion", "Liviu Rebreanu"));
    push(&stiva, creareCarte(3, 500, 55.0f, "Enigma Otiliei", "George Calinescu"));

    printf("Stiva de carti:\n");
    afisareStiva(stiva);

    printf("Pret mediu: %.2f\n\n", calculeazaPretMediu(stiva));

    Carte extrasa;
    if (pop(&stiva, &extrasa)) {
        printf("Cartea extrasa din stiva:\n");
        afisareCarte(extrasa);
        free(extrasa.titlu);
        free(extrasa.autor);
    }

    printf("Stiva dupa extragere:\n");
    afisareStiva(stiva);

    dezalocareStiva(&stiva);
    return 0;
}