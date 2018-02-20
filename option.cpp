#include "option.h"
#include "menu.h"

void readKanaSelected(int hiraganaActif[], int katakanaActif[])
{
    int i = 0;
    FILE *fichier = fopen("kanaSelected.jap", "r");

    if (fichier != 0)
    {
        for (i = 0 ; i < 90 ; i++)
        {
            fscanf(fichier, "%d ", &hiraganaActif[i]);
        }

        for (i = 0 ; i < 90 ; i++)
        {
            fscanf(fichier, "%d ", &katakanaActif[i]);
        }
    }
    else if (fichier == NULL)
    {
        for (i = 0 ; i < 90 ; i++)
        {
            hiraganaActif[i] = 0;
        }

        for (i = 0 ; i < 90 ; i++)
        {
            katakanaActif[i] = 0;
        }
    }

    fclose(fichier);
}

void writeKanaSelected(int hiraganaActif[], int katakanaActif[])
{
    int i = 0;
    FILE *fichier = fopen("kanaSelected.jap", "w");

    for (i = 0 ; i < 90 ; i++)
    {
        fprintf(fichier, "%d ", hiraganaActif[i]);
    }

    for (i = 0 ; i < 90 ; i++)
    {
        fprintf(fichier, "%d ", katakanaActif[i]);
    }

    fclose(fichier);
}

void option(SDL_Surface *ecran, int *continuerProgramme, int hiraganaActif[], int katakanaActif[], char kana[][3])
{
    // Déclaration des variables
    int continuerOption = 1;

    while (continuerOption)
    {
        switch (menuOption(ecran, continuerProgramme, &continuerOption))
        {
            case 0:
                changeKanaSelected(ecran, continuerProgramme, &continuerOption, hiraganaActif, kana, 0);
                break;
            case 1:
                changeKanaSelected(ecran, continuerProgramme, &continuerOption, katakanaActif, kana, 1);
                break;
            case 2:
                continuerOption = 0;
                break;
        }
    }
}

void changeKanaSelected(SDL_Surface *ecran, int *continuerProgramme, int *continuerOption, int kanaActif[], char kana[][3],
                         int type)
{
    int continuerSelection = 1, retourActif = 0, i = 0, j = 0, k = 0;
    char tampon[50] = {""}, extKana[2][10] = {"Off.bmp", "On.bmp"};
    SDL_Event event;
    SDL_Surface *kanaImage[90][2], *retour[2];
    SDL_Rect positionKana[90], positionRetour;

    // On initialise les positions
    for (i = 0 ; i < 3 ; i++)
    {
        for (j = 0 ; j < 6 ; j++)
        {
            for (k = 0 ; k < 5 ; k++)
            {
                positionKana[i*30 + j*5 + k].x = 15 + 340*i + 60*k;
                positionKana[i*30 + j*5 + k].y = 15 + 60*j;
            }
        }
    }
    positionRetour.x = 430;
    positionRetour.y = 385;

    // On charge les images
    for (i = 0 ; i < 90 ; i++)
    {
        for (j = 0 ; j < 2 ; j++)
        {
            if (type == 0)
            {
                sprintf(tampon, "images/hiraganaChoix/%s%s", kana[i], extKana[j]);
            }
            else if (type == 1)
            {
                sprintf(tampon, "images/katakanaChoix/%s%s", kana[i], extKana[j]);
            }
            kanaImage[i][j] = SDL_LoadBMP(tampon);
        }
    }
    retour[0] = SDL_LoadBMP("images/menu/retourOff.bmp");
    retour[1] = SDL_LoadBMP("images/menu/retourOn.bmp");
    // ################################################################

    while (continuerSelection)
    {
        // On actualise l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        for (i = 0 ; i < 90 ; i++)
        {
            if (kanaImage[i][0] != NULL)
            {
                SDL_BlitSurface(kanaImage[i][kanaActif[i]], NULL, ecran, &positionKana[i]);
            }
        }
        if (retourActif == 0)
        {
            SDL_BlitSurface(retour[0], NULL, ecran, &positionRetour);
        }
        else if (retourActif == 1)
        {
            SDL_BlitSurface(retour[1], NULL, ecran, &positionRetour);
        }
        SDL_Flip(ecran);

        // On regarde ce que fait l'utilisateur
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                continuerSelection = 0;
                *continuerOption = 0;
                *continuerProgramme = 0;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    continuerSelection = 0;
                }
                break;

            case SDL_MOUSEMOTION:
                if((event.motion.x> 430)&&(event.motion.x< 570)&&(event.motion.y> 385)&&(event.motion.y< 435))
                {
                    retourActif = 1;
                }
                else
                {
                    retourActif = 0;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                for (i = 0 ; i < 3 ; i++)
                {
                    for (j = 0 ; j < 6 ; j++)
                    {
                        for (k = 0 ; k < 5 ; k++)
                        {
                            if((event.button.x > 15 + 340*i + 60*k) && (event.button.x < 65 + 340*i + 60*k)
                               &&(event.button.y > 15 + 60*j) && (event.button.y < 65 + 60*j))
                            {
                                if (kanaActif[i*30 + j*5 + k] == 1)
                                {
                                    kanaActif[i*30 + j*5 + k] = 0;
                                }
                                else if (kanaActif[i*30 + j*5 + k] == 0)
                                {
                                    kanaActif[i*30 + j*5 + k] = 1;
                                }
                            }
                        }
                    }
                }
                if((event.button.x> 430)&&(event.button.x< 570)&&(event.button.y> 385)&&(event.button.y< 435))
                {
                    continuerSelection = 0;
                }
                break;
        }
    }

    // ################################################################
    // On libère les images
    for (i = 0 ; i < 90 ; i++)
    {
        for (j = 0 ; j < 2 ; j++)
        {
            SDL_FreeSurface(kanaImage[i][j]);
        }
    }
}

