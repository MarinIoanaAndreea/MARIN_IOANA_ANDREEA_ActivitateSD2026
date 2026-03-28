#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Zbor {
    int id;
    float pret;
    float durata;
    char* destinatie;
    char* pilot;
    char clasa;
};
typedef struct Zbor Zbor;

Zbor citireZborDinFisier(FILE* f) {
    char buffer[100];
    char sep[3] = ",\n";
    char* aux;
    fgets(buffer, 100, f);
    Zbor z;
    aux = strtok(buffer, sep);
    z.id = atoi(aux);
    aux = strtok(NULL, sep);
    z.destinatie = (char*)malloc(strlen(aux) + 1);
    strcpy(z.destinatie, aux);
    aux = strtok(NULL, sep);
    z.pilot = (char*)malloc(strlen(aux) + 1);
    strcpy(z.pilot, aux);
    z.pret = atof(strtok(NULL, sep));
    z.durata = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    z.clasa = aux[0];
    return z;
}

void afisareZbor(Zbor z) {
    printf("Id: %d\n", z.id);
    printf("Destinatie: %s\n", z.destinatie);
    printf("Pilot: %s\n", z.pilot);
    printf("Pret: %.2f\n", z.pret);
    printf("Durata: %.2f\n", z.durata);
    printf("Clasa: %c\n\n", z.clasa);
}

void dezalocareZbor(Zbor* z) {
    free(z->destinatie);
    free(z->pilot);
}

int main() {
    FILE* f = fopen("zboruri.txt", "r");
    if (f) {
        while (!feof(f)) {
            Zbor z = citireZborDinFisier(f);
            afisareZbor(z);
            dezalocareZbor(&z);
        }
        fclose(f);
    }
    else {
        printf("Fisierul nu a putut fi deschis!\n");
    }
    return 0;
}