#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_Mixer.h>

using namespace std;

void playGame();

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void startGameBackground (SDL_Renderer * renderer);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

void makeRandomNumber (int valueBoard [][4]);

void renderGame (SDL_Renderer *renderer, int valueBoard [][4]);

void renderGameOver (SDL_Renderer *renderer);

void renderWinGame (SDL_Renderer *renderer);

void up(int valueBoard[][4]);

void down(int valueBoard[][4]);

void left(int valueBoard[][4]);

void right(int valueBoard[][4]);

bool checkGame (int valueBoard[][4]);

void musicBackground (Mix_Music *music);

#endif // SDL_UTILS_H
