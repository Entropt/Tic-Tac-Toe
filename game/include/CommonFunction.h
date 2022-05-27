
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

static SDL_Window* gWindow = NULL;
static SDL_Surface* gScreenSurface = NULL;
static SDL_Surface* gHelloWorld = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


///Screen

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const SDL_Color white = {255, 255, 255, 255};
const SDL_Color black = {0, 0, 0, 255};
const SDL_Color red = {255, 0, 0, 255};

bool inRect(int x, int y, SDL_Rect rect);

///status shows the screen being rendered

const int MAIN_MENU = 1;
const int SINGLEPLAYER = 2;
const int MULTIPLAYER = 3;
const int SINGLE_FIRST_PICK = 4;
const int SINGLE_GAMEPLAY = 5;
const int MULTI_GAMEPLAY = 6;

string int2str(int num);

#endif
