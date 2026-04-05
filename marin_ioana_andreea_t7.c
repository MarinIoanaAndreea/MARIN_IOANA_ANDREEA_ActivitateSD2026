#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produs Produs;
typedef struct Nod Nod;

struct Produs {
    int cod;
    float pret;
    int stoc;
    char* denumire;
    char* categorie;
};

struct Nod {
    Produs info;
    Nod* st;
    Nod* dr;
};

Produs creareProdus(int cod, float pret, int stoc, const char* denumire, const char* categorie) {
    Produs p;
    p.cod = cod;
    p.pret = pret;
    p.stoc = stoc;
    p.denumire = (char*)malloc(strlen(denumire) + 1);
    strcpy(p.denumire, denumire);
    p.categorie = (char*)malloc(strlen(categorie) + 1);
    strcpy(p.categorie, categorie);
    return p;
}

void afisareProdus(Produs p) {
    printf("Cod: %d\n", p.cod);
    printf("Denumire: %s\n", p.denumire);
    printf("Categorie: %s\n", p.categorie);
    printf("Pret: %.2f\n", p.pret);
    printf("Stoc: %d\n\n", p.stoc);
}

Nod* inserareArbore(Nod* rad, Produs p) {
    if (rad == NULL) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = p;
        nou->st = NULL;
        nou->dr = NULL;
        return nou;
    }

    if (p.cod < rad->info.cod) {
        rad->st = inserareArbore(rad->st, p);
    } else if (p.cod > rad->info.cod) {
        rad->dr = inserareArbore(rad->dr, p);
    }

    return rad;
}

void afisareSRD(Nod* rad) {
    if (rad) {
        afisareSRD(rad->st);
        afisareProdus(rad->info);
        afisareSRD(rad->dr);
    }
}

int numaraProduseStocMic(Nod* rad, int prag) {
    if (rad == NULL) {
        return 0;
    }

    int nr = 0;
    if (rad->info.stoc < prag) {
        nr = 1;
    }

    return nr + numaraProduseStocMic(rad->st, prag) + numaraProduseStocMic(rad->dr, prag);
}

Produs* cautaProdusDupaCod(Nod* rad, int cod) {
    if (rad == NULL) {
        return NULL;
    }

    if (rad->info.cod == cod) {
        return &rad->info;
    }

    if (cod < rad->info.cod) {
        return cautaProdusDupaCod(rad->st, cod);
    } else {
        return cautaProdusDupaCod(rad->dr, cod);
    }
}

void dezalocareArbore(Nod* rad) {
    if (rad) {
        dezalocareArbore(rad->st);
        dezalocareArbore(rad->dr);
        free(rad->info.denumire);
        free(rad->info.categorie);
        free(rad);
    }
}

int main() {
    Nod* rad = NULL;

    rad = inserareArbore(rad, creareProdus(10, 2500, 5, "Laptop", "IT"));
    rad = inserareArbore(rad, creareProdus(4, 120, 20, "Mouse", "Periferice"));
    rad = inserareArbore(rad, creareProdus(15, 800, 3, "Monitor", "IT"));
    rad = inserareArbore(rad, creareProdus(2, 60, 50, "Mousepad", "Accesorii"));
    rad = inserareArbore(rad, creareProdus(8, 300, 7, "Tastatura", "Periferice"));

    printf("Afisare produse in SRD:\n");
    afisareSRD(rad);

    printf("Numar produse cu stoc mai mic decat 10: %d\n\n", numaraProduseStocMic(rad, 10));

    Produs* p = cautaProdusDupaCod(rad, 15);
    if (p) {
        printf("Produsul cautat este:\n");
        afisareProdus(*p);
    }

    dezalocareArbore(rad);
    return 0;
}