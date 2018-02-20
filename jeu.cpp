#include "jeu.h"

void jouer(SDL_Surface *ecran, int *continuerProgramme, int hiraganaActif[], int katakanaActif[], char kana[][3], int ordre)
{
    int continuerJeu = 1, continuerEvent = 1, randomKana = 0, lastKana = -1, i = 0, j = 0, retourActif = 0;
    const int MIN = 1;
    char nomBouton[3][15] = {"solution", "suivant", "retour"}, extBouton[2][10] = {"Off.bmp", "On.bmp"};
    char tampon[50] = "";
    SDL_Surface *fleche, *bouton[3][2], *erreur;
    SDL_Rect positionGauche, positionDroite, positionFleche, positionBouton[3], positionErreur;
    SDL_Event event;
    Liste *liste = initialiser();
    Element *kanaTravail = NULL;

    // On initialise la liste chainée qui va ensuite charger toutes les images
    for (i = 0 ; i < 90 ; i++)
    {
        if ((hiraganaActif[i] == 1) && (strcmp(kana[i], "") != 0))
        {
            ajouter(liste, kana[i], 0);
        }
    }
    for (i = 0 ; i < 90 ; i++)
    {
        if ((katakanaActif[i] == 1) && (strcmp(kana[i], "") != 0))
        {
            ajouter(liste, kana[i], 1);
        }
    }

    // On charge les images des boutons
    for (i = 0 ; i < 4 ; i++)
    {
        for (j = 0 ; j < 2 ; j++)
        {
            sprintf(tampon, "images/menu/%s%s", nomBouton[i], extBouton[j]);
            bouton[i][j] = SDL_LoadBMP(tampon);
        }
    }
    // On met ensuite les positions
    positionBouton[0].x = 180;
    positionBouton[0].y = 290;
    positionBouton[1].x = 520;
    positionBouton[1].y = 290;
    positionBouton[2].x = 430;
    positionBouton[2].y = 375;

    fleche = SDL_LoadBMP("images/fleche.bmp");
    positionFleche.x = 425;
    positionFleche.y = 25;

    positionDroite.y = 25;
    positionGauche.y = 25;
    // ################################################################

    if (liste->nombre < 2)
    {
        erreur = SDL_LoadBMP("images/menu/erreur.bmp");
        positionErreur.x = 25;
        positionErreur.y = 0;
        while (continuerJeu)
        {
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
            SDL_BlitSurface(erreur, NULL, ecran, &positionErreur);
            if (retourActif == 0)
            {
                SDL_BlitSurface(bouton[2][0], NULL, ecran, &positionBouton[2]);
            }
            else if (retourActif == 1)
            {
                SDL_BlitSurface(bouton[2][1], NULL, ecran, &positionBouton[2]);
            }
            SDL_Flip(ecran);

            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuerEvent = 0;
                    continuerJeu = 0;
                    *continuerProgramme = 0;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        continuerEvent = 0;
                        continuerJeu = 0;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if((event.motion.x> positionBouton[2].x) && (event.motion.x< positionBouton[2].x + bouton[2][0]->w) &&
                       (event.motion.y> positionBouton[2].y) && (event.motion.y< positionBouton[2].y + bouton[2][0]->h))
                    {
                         retourActif = 1;
                    }
                    else
                    {
                        retourActif = 0;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if((event.button.x> positionBouton[2].x) && (event.button.x< positionBouton[2].x + bouton[2][0]->w) &&
                       (event.button.y> positionBouton[2].y) && (event.button.y< positionBouton[2].y + bouton[2][0]->h))
                    {
                        continuerEvent = 0;
                        continuerJeu = 0;
                    }
                    break;
            }
        }
    }

    while (continuerJeu)
    {
        do // Tirage d'un kana aléatoire
        {
            randomKana = (rand() % (liste->nombre - MIN + 1)) + MIN;
        }while (randomKana == lastKana);
        lastKana = randomKana;

        // On va chercher le bon kana dans la liste chainée
        kanaTravail = liste->premier;
        for (i = 1 ; i < randomKana ; i++)
        {
            kanaTravail = kanaTravail->suivant;
        }

        // On actualise l'écran une 1ere fois et on met les positions en fonctions de la tailles des images
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
        if (ordre == 0) // Si c'est en kana vers romaji
        {
            positionGauche.x = 230 - (kanaTravail->imageKana->w / 2);
            positionDroite.x = 770 - (kanaTravail->imageRomaji->w / 2);
            SDL_BlitSurface(kanaTravail->imageKana, NULL, ecran, &positionGauche);
        }
        else if (ordre == 1) // Si c'est en romaji vers kana
        {
            positionGauche.x = 230 - (kanaTravail->imageRomaji->w / 2);
            positionDroite.x = 770 - (kanaTravail->imageKana->w / 2);
            SDL_BlitSurface(kanaTravail->imageRomaji, NULL, ecran, &positionGauche);
        }
        for (i = 0 ; i < 3 ; i++) // Pour les boutons
        {
            SDL_BlitSurface(bouton[i][0], NULL, ecran, &positionBouton[i]);
        }
        SDL_Flip(ecran);

        // On regarde ce que fait l'utilisateur
        continuerEvent = 1;
        while (continuerEvent)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuerEvent = 0;
                    continuerJeu = 0;
                    *continuerProgramme = 0;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            continuerEvent = 0;
                            continuerJeu = 0;
                            break;

                        case SDLK_DOWN:
                            if (ordre == 0) // Si c'est en kana vers romaji
                            {
                                SDL_BlitSurface(kanaTravail->imageRomaji, NULL, ecran, &positionDroite);
                            }
                            else if (ordre == 1) // Si c'est en romaji vers kana
                            {
                                SDL_BlitSurface(kanaTravail->imageKana, NULL, ecran, &positionDroite);
                            }
                            SDL_Flip(ecran);
                            break;

                        case SDLK_RIGHT:
                            continuerEvent = 0;
                            break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    for (i = 0 ; i < 3 ; i++)
                    {
                        if((event.motion.x> positionBouton[i].x) && (event.motion.x< positionBouton[i].x + bouton[i][0]->w) &&
                           (event.motion.y> positionBouton[i].y) && (event.motion.y< positionBouton[i].y + bouton[i][0]->h))
                        {
                             SDL_BlitSurface(bouton[i][1], NULL, ecran, &positionBouton[i]);
                        }
                        else
                        {
                            SDL_BlitSurface(bouton[i][0], NULL, ecran, &positionBouton[i]);
                        }
                    }
                    SDL_Flip(ecran);
                    break;

                case SDL_MOUSEBUTTONUP:
                    if((event.button.x> positionBouton[0].x) && (event.button.x< positionBouton[0].x + bouton[0][0]->w) &&
                        (event.button.y> positionBouton[0].y) && (event.button.y< positionBouton[0].y + bouton[0][0]->h))
                    {
                        if (ordre == 0) // Si c'est en kana vers romaji
                        {
                            SDL_BlitSurface(kanaTravail->imageRomaji, NULL, ecran, &positionDroite);
                        }
                        else if (ordre == 1) // Si c'est en romaji vers kana
                        {
                            SDL_BlitSurface(kanaTravail->imageKana, NULL, ecran, &positionDroite);
                        }
                        SDL_Flip(ecran);
                    }
                    else if((event.button.x> positionBouton[1].x) && (event.button.x< positionBouton[1].x + bouton[1][0]->w) &&
                            (event.button.y> positionBouton[1].y) && (event.button.y< positionBouton[1].y + bouton[1][0]->h))
                    {
                        continuerEvent = 0;
                    }
                    else if((event.button.x> positionBouton[2].x) && (event.button.x< positionBouton[2].x + bouton[2][0]->w) &&
                            (event.button.y> positionBouton[2].y) && (event.button.y< positionBouton[2].y + bouton[2][0]->h))
                    {
                        continuerEvent = 0;
                        continuerJeu = 0;
                    }
                    break;
            }
        }
    }

    // ################################################################
    for (i = 0 ; i < 4 ; i++)
    {
        for (j = 0 ; j < 2 ; j++)
        {
            SDL_free(bouton[i][j]);
        }
    }
    SDL_FreeSurface(fleche);
    supprimer(liste);
}

