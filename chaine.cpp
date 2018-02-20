#include "chaine.h"

Liste *initialiser()
{
    Liste *liste = (Liste*) malloc(sizeof(*liste));

    if (liste == NULL)
    {
        fprintf(stderr, "Impossible d'initialiser la liste chainee\n");
        exit(EXIT_FAILURE);
    }

    liste->premier = NULL;
    liste->nombre = 0;

    return liste;
}

void ajouter(Liste *liste, char kana[3], int type)
{
    char tampon[75];
    Element *nouveau = (Element*) malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        fprintf(stderr, "Impossible d'ajouter un element a la liste chainee\n");
        exit(EXIT_FAILURE);
    }
     strcpy(nouveau->kana, kana);
     nouveau->type = type;

     if (type == 0)
     {
         sprintf(tampon, "images/hiragana/%s.bmp", kana);
         nouveau->imageKana = SDL_LoadBMP(tampon);
         sprintf(tampon, "images/romajiHiragana/%s.bmp", kana);
         nouveau->imageRomaji = SDL_LoadBMP(tampon);
     }
     else if (type == 1)
     {
         sprintf(tampon, "images/katakana/%s.bmp", kana);
         nouveau->imageKana = SDL_LoadBMP(tampon);
         sprintf(tampon, "images/romajiKatakana/%s.bmp", kana);
         nouveau->imageRomaji = SDL_LoadBMP(tampon);
     }

     liste->nombre = liste->nombre + 1;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void supprimer(Liste *liste)
{
    if (liste == NULL)
    {
        fprintf(stderr, "Impossible de supprimer la liste chainee\n");
        exit(EXIT_FAILURE);
    }

    while (liste->premier != NULL)
    {
        Element *aSupprimer = liste->premier;
        SDL_free(aSupprimer->imageKana);
        SDL_free(aSupprimer->imageRomaji);
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }

    free(liste);
}

