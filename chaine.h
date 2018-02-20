#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <string.h>

typedef struct Element Element;
struct Element
{
    char kana[3];
    int type;
    SDL_Surface *imageKana, *imageRomaji;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
    int nombre;
};

Liste *initialiser();
void ajouter(Liste *liste, char kana[3], int type);
void supprimer(Liste *liste);
