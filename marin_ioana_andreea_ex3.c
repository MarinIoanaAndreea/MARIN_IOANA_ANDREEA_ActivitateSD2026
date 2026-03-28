#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Melodie {
    int id;
    float durata;
    char* titlu;
    char* artist;
    int esteExplicit;   // explicit -> esteExplicit
};
typedef struct Melodie Melodie;

Melodie citireMelodie() {
    Melodie m;
    char buffer[100];
    printf("Id: ");
    scanf("%d", &m.id);
    printf("Durata: ");
    scanf("%f", &m.durata);
    printf("Titlu: ");
    scanf("%s", buffer);
    m.titlu = (char*)malloc(strlen(buffer) + 1);   // cast adaugat
    strcpy(m.titlu, buffer);                        // strcpy_s -> strcpy
    printf("Artist: ");
    scanf("%s", buffer);
    m.artist = (char*)malloc(strlen(buffer) + 1);  // cast adaugat
    strcpy(m.artist, buffer);                       // strcpy_s -> strcpy
    printf("Explicit (0/1): ");
    scanf("%d", &m.esteExplicit);
    return m;
}

void afisareMelodie(Melodie m) {
    printf("Id: %d\n", m.id);
    printf("Durata: %.2f\n", m.durata);
    printf("Titlu: %s\n", m.titlu);
    printf("Artist: %s\n", m.artist);
    printf("Explicit: %s\n\n", m.esteExplicit ? "Da" : "Nu");
}

int main() {
    Melodie m = citireMelodie();
    afisareMelodie(m);
    free(m.titlu);
    free(m.artist);
    return 0;
}