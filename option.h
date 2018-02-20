#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <string.h>

void readKanaSelected(int hiraganaActif[], int katakanaActif[]);
void writeKanaSelected(int hiraganaActif[], int katakanaActif[]);
void option(SDL_Surface *ecran, int *continuerProgramme, int hiraganaActif[], int katakanaActif[], char kana[][3]);
void changeKanaSelected(SDL_Surface *ecran, int *continuerProgramme, int *continuerOption, int kanaActif[], char kana[][3],
                         int type);
