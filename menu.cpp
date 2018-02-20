#include "menu.h"

int menu(SDL_Surface *ecran, int *continuerProgramme)
{
    // Déclaration des variables
    int choix = -1, continuerMenu = 1, i = 0, j = 0;
    int choixMenuActif[4] = {0};
    char tampon[50] = {""};
    char nomChoixMenu[4][20] = {"kanaRomaji", "romajiKana", "option", "aide"}, extChoixMenu[2][10] = {"Off.bmp", "On.bmp"};
    SDL_Event event;
    SDL_Surface *choixMenu[4][2];
    SDL_Rect positionChoix[4];

    // On initialise les positions
    for (i = 0 ; i < 4 ; i++)
    {
        positionChoix[i].x = 300;
        positionChoix[i].y = 10 + 110 * i;
    }

    // On charge les images du menu
    for (i = 0 ; i < 4 ; i++)
    {
        for (j = 0 ; j < 2 ; j++)
        {
            sprintf(tampon, "images/menu/%s%s", nomChoixMenu[i], extChoixMenu[j]);
            choixMenu[i][j] = SDL_LoadBMP(tampon);
        }
    }
    // ################################################################

    while (continuerMenu) // Tant que l'utilisateur n'a pas cliqué sur un des choix
    {
        // On actualise l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        for (i = 0 ; i < 4 ; i++)
        {
            if (choixMenuActif[i] == 0)
            {
                SDL_BlitSurface(choixMenu[i][0], NULL, ecran, &positionChoix[i]);
            }
            else if (choixMenuActif[i] == 1)
            {
                SDL_BlitSurface(choixMenu[i][1], NULL, ecran, &positionChoix[i]);
            }
        }
        SDL_Flip(ecran);

        // On regarde ce que fait l'utilisateur
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                continuerMenu = 0;
                *continuerProgramme = 0;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    continuerMenu = 0;
                    *continuerProgramme = 0;
                }
                break;

            case SDL_MOUSEMOTION:
                for (i = 0 ; i < 4 ; i++)
                {
                    if((event.motion.x> positionChoix[i].x) && (event.motion.x< positionChoix[i].x + choixMenu[i][0]->w) &&
                        (event.motion.y> positionChoix[i].y) && (event.motion.y< positionChoix[i].y + choixMenu[i][0]->h))
                    {
                        choixMenuActif[i] = 1;
                    }
                    else
                    {
                        choixMenuActif[i] = 0;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                for (i = 0 ; i < 4 ; i++)
                {
                    if((event.button.x> positionChoix[i].x )&& (event.button.x< positionChoix[i].x + choixMenu[i][0]->w) &&
                       (event.button.y> positionChoix[i].y) && (event.button.y< positionChoix[i].y + choixMenu[i][0]->h))
                    {
                        choix = i;
                        continuerMenu = 0;
                    }
                }
                break;
        }
    }

    // ################################################################
    // On libère les images
    for (i = 0 ; i < 4 ; i++)
    {
        for (j = 0 ; j < 2 ; j++)
        {
            SDL_FreeSurface(choixMenu[i][j]);
        }
    }
    return choix;
}

int menuOption(SDL_Surface *ecran, int *continuerProgramme, int *continuerOption)
{
    // Déclaration des variables
    int choix = -1, continuerMenu = 1, i = 0, j = 0;
    int choixMenuActif[3] = {0};
    char tampon[50] = {""};
    char nomChoixMenu[3][20] = {"choixHiragana", "choixKatakana", "retour"}, extChoixMenu[2][10] = {"Off.bmp", "On.bmp"};
    SDL_Event event;
    SDL_Surface *choixMenu[3][2];
    SDL_Rect positionChoix[3];

    // On charge les images du menu
    for (i = 0 ; i < 3 ; i++)
    {
        for (j = 0 ; j < 2 ; j++)
        {
            sprintf(tampon, "images/menu/%s%s", nomChoixMenu[i], extChoixMenu[j]);
            choixMenu[i][j] = SDL_LoadBMP(tampon);
        }
    }

    // On initialise les positions
    for (i = 0 ; i < 3 ; i++)
    {
        positionChoix[i].x = 500 - (choixMenu[i][0]->w / 2);
        positionChoix[i].y = 50 + 150 * i;
    }
    // ################################################################

    while (continuerMenu) // Tant que l'utilisateur n'a pas cliqué sur un des choix
    {
        // On actualise l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        for (i = 0 ; i < 3 ; i++)
        {
            if (choixMenuActif[i] == 0)
            {
                SDL_BlitSurface(choixMenu[i][0], NULL, ecran, &positionChoix[i]);
            }
            else if (choixMenuActif[i] == 1)
            {
                SDL_BlitSurface(choixMenu[i][1], NULL, ecran, &positionChoix[i]);
            }
        }
        SDL_Flip(ecran);

        // On regarde ce que fait l'utilisateur
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                continuerMenu = 0;
                *continuerOption = 0;
                *continuerProgramme = 0;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    continuerMenu = 0;
                    *continuerOption = 0;
                }
                break;

            case SDL_MOUSEMOTION:
                for (i = 0 ; i < 3 ; i++)
                {
                    if((event.motion.x> positionChoix[i].x) && (event.motion.x< positionChoix[i].x + choixMenu[i][0]->w) &&
                       (event.motion.y> positionChoix[i].y) && (event.motion.y< positionChoix[i].y + choixMenu[i][0]->h))
                    {
                        choixMenuActif[i] = 1;
                    }
                    else
                    {
                        choixMenuActif[i] = 0;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                for (i = 0 ; i < 3 ; i++)
                {
                    if((event.button.x> positionChoix[i].x) && (event.button.x< positionChoix[i].x + choixMenu[i][0]->w) &&
                       (event.button.y> positionChoix[i].y) && (event.button.y< positionChoix[i].y + choixMenu[i][0]->h))
                    {
                        choix = i;
                        continuerMenu = 0;
                    }
                }
                break;
        }
    }

    // ################################################################
    // On libère les images
    for (i = 0 ; i < 3 ; i++)
    {
        for (j = 0 ; j < 2 ; j++)
        {
            SDL_FreeSurface(choixMenu[i][j]);
        }
    }
    return choix;
}

