#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Film Film;
struct Film {
    int id;
    float rating;
    int durata;
    char* titlu;
    char* regizor;
    bool color;
    char gen;
};


Film initFilm(int id, float rating, int durata, const char* titlu, const char* regizor, bool color, char gen) {
    Film f;
    f.id = id;
    f.rating = rating;
    f.durata = durata;
    f.titlu = (char*)malloc(strlen(titlu) + 1);
    strcpy(f.titlu, titlu);
    f.regizor = (char*)malloc(strlen(regizor) + 1);
    strcpy(f.regizor, regizor);
    f.color = color;
    f.gen = gen;
    return f;
}

Film copiazaFilm(Film f) {
    return initFilm(f.id, f.rating, f.durata, f.titlu, f.regizor, f.color, f.gen);
}

void afisareFilm(Film f) {
    printf("%d. \"%s\" (%c) - Regizor: %s | Durata: %d min | Rating: %.1f | Color: %s\n",
           f.id, f.titlu, f.gen, f.regizor, f.durata, f.rating, f.color ? "Da" : "Nu");
}

void afisareVectorFilme(Film* vector, int nr) {
    for (int i = 0; i < nr; i++) {
        afisareFilm(vector[i]);
    }
}

void dezalocareFilme(Film** vector, int* nr) {
    for (int i = 0; i < *nr; i++) {
        free((*vector)[i].titlu);
        free((*vector)[i].regizor);
    }
    free(*vector);
    *vector = NULL;
    *nr = 0;
}

Film* filtreazaFilmeColor(Film* vector, int nr, int* dim) {
    *dim = 0;
    for (int i = 0; i < nr; i++) {
        if (vector[i].color) (*dim)++;
    }

    if (*dim == 0) return NULL;

    Film* colorate = malloc(sizeof(Film) * (*dim));
    int j = 0;
    for (int i = 0; i < nr; i++) {
        if (vector[i].color) {
            colorate[j++] = copiazaFilm(vector[i]);
        }
    }
    return colorate;
}
Film filmTopRating(Film* vector, int nr) {
    Film top;
    top.id = -1;
    top.titlu = NULL;
    top.regizor = NULL;
    float max = -1;
    for (int i = 0; i < nr; i++) {
        if (vector[i].rating > max) {
            max = vector[i].rating;
            if (top.id != -1) {
                free(top.titlu);
                free(top.regizor);
            }
            top = copiazaFilm(vector[i]);
        }
    }
    return top;
}

Film* copiazaPrimeleFilme(Film* vector, int nr, int n) {
    if (n > nr) return NULL;
    Film* copie = malloc(sizeof(Film) * n);
    for (int i = 0; i < n; i++) {
        copie[i] = copiazaFilm(vector[i]);
    }
    return copie;
}

int main() {
    Film f = initFilm(1, 8.5, 130, "Gladiator", "Ridley Scott", true, 'A');
    afisareFilm(f);
    printf("\n");

    int nrFilme = 5;
    Film* filme = malloc(sizeof(Film) * nrFilme);
    filme[0] = initFilm(2, 6.2, 88,  "Jack",          "Francis Coppola",  false, 'C');
    filme[1] = initFilm(3, 8.8, 169, "Interstellar",  "Christopher Nolan", true, 'S');
    filme[2] = initFilm(4, 5.4, 95,  "Pixels",        "Chris Columbus",   false, 'C');
    filme[3] = initFilm(5, 7.9, 116, "John Wick",     "Chad Stahelski",  true, 'A');
    filme[4] = initFilm(6, 9.0, 152, "The Godfather", "Francis Coppola", false, 'D');

    printf("Toate filmele:\n");
    afisareVectorFilme(filme, nrFilme);

   
    int nrCopiate = 3;
    Film* scurt = copiazaPrimeleFilme(filme, nrFilme, nrCopiate);
    printf("\nPrimele 3 filme:\n");
    afisareVectorFilme(scurt, nrCopiate);
    dezalocareFilme(&scurt, &nrCopiate);

    int nrColor = 0;
    Film* color = filtreazaFilmeColor(filme, nrFilme, &nrColor);
    printf("\nFilme color:\n");
    afisareVectorFilme(color, nrColor);
    dezalocareFilme(&color, &nrColor);

    Film top = filmTopRating(filme, nrFilme);
    printf("\nFilmul cu cel mai mare rating:\n");
    afisareFilm(top);
    if (top.id != -1) {
        free(top.titlu);
        free(top.regizor);
    }

    free(f.titlu);
    free(f.regizor);
    dezalocareFilme(&filme, &nrFilme);

    return 0;
}