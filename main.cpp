#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <string.h>
#include "menu.h"
#include "option.h"
#include "jeu.h"

int main(int argc, char *argv[])
{
    // Déclaration des variables
    int continuerProgramme = 1;
    int hiraganaActif[90] = {0}, katakanaActif[90] = {0};
    char kana[90][3] = {"a", "i", "u", "e", "o",
                            "ka", "ki", "ku", "ke", "ko",
                            "sa", "si", "su", "se", "so",
                            "ta", "ti", "tu", "te", "to",
                            "na", "ni", "nu", "ne", "no",
                            "", "", "", "", "",
                            "ha", "hi", "hu", "he", "ho",
                            "ma", "mi", "mu", "me", "mo",
                            "ya", "", "yu", "", "yo",
                            "ra", "ri", "ru", "re", "ro",
                            "wa", "wi", "", "we", "wo",
                            "", "", "", "", "n",
                            "ga", "gi", "gu", "ge", "go",
                            "za", "zi", "zu", "ze", "zo",
                            "da", "di", "du", "de", "do",
                            "ba", "bi", "bu", "be", "bo",
                            "pa", "pi", "pu", "pe", "po",
                            "", "", "", "", ""};
    SDL_Surface *ecran = NULL;

    //Initialisation des listes de kana actifs
    readKanaSelected(hiraganaActif, katakanaActif);

    // Initialisation du random et de la SDL
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);

    // Création de la fenêtre principale avec titre et icone.
    SDL_WM_SetCaption("Apprentissage des Kana", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("images/icone.bmp"), NULL);
    ecran = SDL_SetVideoMode(1000, 450, 32, SDL_HWSURFACE);

    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible d'initialiser la fenêtre : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    // ################################################################

    while(continuerProgramme)
    {
        switch (menu(ecran, &continuerProgramme))
        {
            case 0:
                jouer(ecran, &continuerProgramme, hiraganaActif, katakanaActif, kana, 0);
                break;

            case 1:
                jouer(ecran, &continuerProgramme, hiraganaActif, katakanaActif, kana, 1);
                break;

            case 2:
                option(ecran, &continuerProgramme, hiraganaActif, katakanaActif, kana);
                break;
        }
    }

    // ################################################################
    // On enregistre la sélections des kana
    writeKanaSelected(hiraganaActif, katakanaActif);

    // On fini le programme en libérant l'allocation dynamique
    SDL_Quit();
    return EXIT_SUCCESS;
}
