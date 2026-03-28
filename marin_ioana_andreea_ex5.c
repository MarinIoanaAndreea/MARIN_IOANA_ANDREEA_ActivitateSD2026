#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Joc {
    int id;
    float pret;
    float rating;
    char* titlu;
    char* studio;
    int multiplayer;
};
typedef struct Joc Joc;
typedef struct Nod Nod;

struct Nod {
    Joc info;
    Nod* next;
};

Joc creareJoc(int id, float pret, float rating, const char* titlu, const char* studio, int multiplayer) {
    Joc j;
    j.id = id;
    j.pret = pret;
    j.rating = rating;
    j.titlu = (char*)malloc(strlen(titlu) + 1);
    strcpy(j.titlu, titlu);
    j.studio = (char*)malloc(strlen(studio) + 1);
    strcpy(j.studio, studio);
    j.multiplayer = multiplayer;
    return j;
}

void afisareJoc(Joc j) {
    printf("Id: %d\n", j.id);
    printf("Titlu: %s\n", j.titlu);
    printf("Studio: %s\n", j.studio);
    printf("Pret: %.2f\n", j.pret);
    printf("Rating: %.2f\n", j.rating);
    printf("Multiplayer: %s\n\n", j.multiplayer ? "Da" : "Nu");
}

void adaugaJocInLista(Nod** lista, Joc j) {
    Nod* nou = malloc(sizeof(Nod));
    nou->info = j;
    nou->next = NULL;
    if (*lista == NULL) {
        *lista = nou;
    }
    else {
        Nod* p = *lista;
        while (p->next) {
            p = p->next;
        }
        p->next = nou;
    }
}

void afisareListaJocuri(Nod* lista) {
    while (lista) {
        afisareJoc(lista->info);
        lista = lista->next;
    }
}

void dezalocareListaJocuri(Nod** lista) {
    while (*lista) {
        free((*lista)->info.titlu);
        free((*lista)->info.studio);
        Nod* aux = *lista;
        *lista = (*lista)->next;
        free(aux);
    }
}

// calculeaza ratingul mediu al jocurilor din lista
float calculeazaRatingMediu(Nod* lista) {
    float suma = 0;
    int count = 0;
    Nod* p = lista;
    while (p) {
        suma += p->info.rating;
        count++;
        p = p->next;
    }
    if (count > 0)
        return suma / count;
    return 0;
}

// sterge toate jocurile unui studio din lista
void stergeJocuriStudio(Nod** lista, const char* studioCautat) {
    while (*lista && strcmp((*lista)->info.studio, studioCautat) == 0) {
        Nod* aux = *lista;
        *lista = (*lista)->next;
        free(aux->info.titlu);
        free(aux->info.studio);
        free(aux);
    }
    Nod* p = *lista;
    while (p && p->next) {
        if (strcmp(p->next->info.studio, studioCautat) == 0) {
            Nod* aux = p->next;
            p->next = aux->next;
            free(aux->info.titlu);
            free(aux->info.studio);
            free(aux);
        }
        else {
            p = p->next;
        }
    }
}

int main() {
    Nod* lista = NULL;
    adaugaJocInLista(&lista, creareJoc(1, 200, 9.5, "FIFA24", "EA", 1));
    adaugaJocInLista(&lista, creareJoc(2, 150, 8.7, "GTA5", "Rockstar", 1));
    adaugaJocInLista(&lista, creareJoc(3, 100, 7.2, "Skyrim", "Bethesda", 0));
    adaugaJocInLista(&lista, creareJoc(4, 80,  9.1, "Minecraft", "Mojang", 1));
    adaugaJocInLista(&lista, creareJoc(5, 60,  6.8, "FIFA23", "EA", 1));

    printf("Lista jocuri:\n");
    afisareListaJocuri(lista);

    printf("Rating mediu: %.2f\n\n", calculeazaRatingMediu(lista));

    printf("Dupa stergerea jocurilor EA:\n");
    stergeJocuriStudio(&lista, "EA");
    afisareListaJocuri(lista);

    dezalocareListaJocuri(&lista);
    return 0;
}