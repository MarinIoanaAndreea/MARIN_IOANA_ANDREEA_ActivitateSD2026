#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Comanda Comanda;
typedef struct Nod Nod;

struct Comanda {
    int id;
    float valoare;
    char* client;
    char* produs;
    int livrata;
};

struct Nod {
    Comanda info;
    Nod* next;
};

Comanda creareComanda(int id, float valoare, const char* client, const char* produs, int livrata) {
    Comanda c;
    c.id = id;
    c.valoare = valoare;
    c.client = (char*)malloc(strlen(client) + 1);
    strcpy(c.client, client);
    c.produs = (char*)malloc(strlen(produs) + 1);
    strcpy(c.produs, produs);
    c.livrata = livrata;
    return c;
}

void afisareComanda(Comanda c) {
    printf("Id: %d\n", c.id);
    printf("Client: %s\n", c.client);
    printf("Produs: %s\n", c.produs);
    printf("Valoare: %.2f\n", c.valoare);
    printf("Livrata: %s\n\n", c.livrata ? "Da" : "Nu");
}

void enqueue(Nod** prim, Nod** ultim, Comanda c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next = NULL;

    if (*ultim) {
        (*ultim)->next = nou;
    } else {
        *prim = nou;
    }

    *ultim = nou;
}

int dequeue(Nod** prim, Nod** ultim, Comanda* c) {
    if (*prim == NULL) {
        return 0;
    }

    Nod* aux = *prim;
    *c = aux->info;
    *prim = aux->next;

    if (*prim == NULL) {
        *ultim = NULL;
    }

    free(aux);
    return 1;
}

void afisareCoada(Nod* prim) {
    while (prim) {
        afisareComanda(prim->info);
        prim = prim->next;
    }
}

float valoareTotalaNelivrate(Nod* prim) {
    float suma = 0;
    while (prim) {
        if (prim->info.livrata == 0) {
            suma += prim->info.valoare;
        }
        prim = prim->next;
    }
    return suma;
}

void dezalocareCoada(Nod** prim, Nod** ultim) {
    while (*prim) {
        Nod* aux = *prim;
        *prim = (*prim)->next;
        free(aux->info.client);
        free(aux->info.produs);
        free(aux);
    }
    *ultim = NULL;
}

int main() {
    Nod* prim = NULL;
    Nod* ultim = NULL;

    enqueue(&prim, &ultim, creareComanda(1, 250.5f, "Ana", "Laptop", 0));
    enqueue(&prim, &ultim, creareComanda(2, 99.9f, "Mihai", "Tastatura", 1));
    enqueue(&prim, &ultim, creareComanda(3, 150.0f, "Ioana", "Monitor", 0));

    printf("Coada de comenzi:\n");
    afisareCoada(prim);

    printf("Valoare totala comenzi nelivrate: %.2f\n\n", valoareTotalaNelivrate(prim));

    Comanda extrasa;
    if (dequeue(&prim, &ultim, &extrasa)) {
        printf("Comanda extrasa din coada:\n");
        afisareComanda(extrasa);
        free(extrasa.client);
        free(extrasa.produs);
    }

    printf("Coada dupa extragere:\n");
    afisareCoada(prim);

    dezalocareCoada(&prim, &ultim);
    return 0;
}