
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


enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];

///Screen

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#endif
