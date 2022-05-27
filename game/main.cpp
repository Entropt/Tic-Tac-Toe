/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings

#include "include/CommonFunction.h"
#include "include/BaseObject.h"


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

int status = 1;
SDL_Event event;
BaseObject menu;
BaseObject single_player;
BaseObject multi_player;
BaseObject exit_icon;
BaseObject restart_icon;
BaseObject continue_icon;
BaseObject return_icon;
BaseObject play_gr;
BaseObject X_animation, O_animation;
BaseObject winable, unwinable;
BaseObject name_border[2];
TTF_Font* font;
string p_name[2];

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
		return -1;
	}

	loadMedia();

	int curTick = 0, lastTick = 0;
	int curPlayer = -1;

	while(status > 0)
    {
        curTick = SDL_GetTicks();
        if(curTick - lastTick >= 33)
        {
            ////chay ct

            if(status == 2 || status == 3)
            {
                return_icon.setX((SCREEN_WIDTH - return_icon.getW()) / 2);
                return_icon.setY(800);
            }

            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                    status = 0;
                if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(status == 1)
                    {
                        if(inRect(x, y, single_player.GetRect()))
                            status = 2;
                        else if(inRect(x, y, multi_player.GetRect()))
                        {
                            curPlayer = -1;
                            p_name[0] = p_name[1] = " ";
                            status = 3;
                        }
                        else if(inRect(x, y, exit_icon.GetRect()))
                            status = 0;
                    }
                    else if(status == 2)
                    {
                        if(inRect(x, y, winable.GetRect()))
                            status = 4;
                        else if(inRect(x, y, unwinable.GetRect()))
                            status = 5;
                        else if(inRect(x, y, return_icon.GetRect()))
                            status = 1;
                    }
                    else if(status == 3)
                    {
                        if(inRect(x, y, name_border[0].GetRect()))
                            curPlayer = 0;
                        else if(inRect(x, y, name_border[1].GetRect()))
                            curPlayer = 1;
                        else if(inRect(x, y, return_icon.GetRect()))
                            status = 1;
                        else if(inRect(x, y, continue_icon.GetRect()))
                            status = 6;
                        else curPlayer = -1;
                    }

                }

                if(event.type == SDL_KEYDOWN)
                {
                    if(status == 3 && curPlayer != -1)
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_a: {p_name[curPlayer] += 'a'; break;}
                        case SDLK_b: {p_name[curPlayer] += 'b'; break;}
                        case SDLK_c: {p_name[curPlayer] += 'c'; break;}
                        case SDLK_d: {p_name[curPlayer] += 'd'; break;}
                        case SDLK_e: {p_name[curPlayer] += 'e'; break;}
                        case SDLK_f: {p_name[curPlayer] += 'f'; break;}
                        case SDLK_g: {p_name[curPlayer] += 'g'; break;}
                        case SDLK_h: {p_name[curPlayer] += 'h'; break;}
                        case SDLK_i: {p_name[curPlayer] += 'i'; break;}
                        case SDLK_j: {p_name[curPlayer] += 'j'; break;}
                        case SDLK_k: {p_name[curPlayer] += 'k'; break;}
                        case SDLK_l: {p_name[curPlayer] += 'l'; break;}
                        case SDLK_m: {p_name[curPlayer] += 'm'; break;}
                        case SDLK_n: {p_name[curPlayer] += 'n'; break;}
                        case SDLK_o: {p_name[curPlayer] += 'o'; break;}
                        case SDLK_p: {p_name[curPlayer] += 'p'; break;}
                        case SDLK_q: {p_name[curPlayer] += 'q'; break;}
                        case SDLK_r: {p_name[curPlayer] += 'r'; break;}
                        case SDLK_s: {p_name[curPlayer] += 's'; break;}
                        case SDLK_t: {p_name[curPlayer] += 't'; break;}
                        case SDLK_u: {p_name[curPlayer] += 'u'; break;}
                        case SDLK_v: {p_name[curPlayer] += 'v'; break;}
                        case SDLK_w: {p_name[curPlayer] += 'w'; break;}
                        case SDLK_x: {p_name[curPlayer] += 'x'; break;}
                        case SDLK_y: {p_name[curPlayer] += 'y'; break;}
                        case SDLK_z: {p_name[curPlayer] += 'z'; break;}
                        case SDLK_BACKSPACE: {if (p_name[curPlayer].size() > 1) p_name[curPlayer].pop_back(); break;}
                    }
                }

            }

            //////////////

            if(status )
            {

            }


            //////////////Render
            SDL_RenderClear(gRenderer);

            if(status == 1)
            {
                menu.Render(gRenderer, NULL);
                single_player.Render(gRenderer, NULL);
                multi_player.Render(gRenderer, NULL);
                exit_icon.Render(gRenderer, NULL);

            }
            else if(status == 2)
            {
                menu.Render(gRenderer, NULL);
                winable.Render(gRenderer, NULL);
                unwinable.Render(gRenderer, NULL);
                return_icon.Render(gRenderer, NULL);
            }
            else if(status == 3)
            {
                menu.Render(gRenderer, NULL);
                SDL_Surface* sf = NULL;
                SDL_Texture* tx = NULL;

                sf = TTF_RenderText_Solid(font, "Enter player 1's name:", white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                int w, h;
                w = sf->w, h = sf->h;
                SDL_Rect nRect = {0, 0, w, h};
                nRect.x = SCREEN_WIDTH / 4 - w / 2;
                nRect.y = 600;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);
                name_border[0].setX(nRect.x + (w - name_border[0].getW()) / 2);
                name_border[0].setY(nRect.y + h + 50);
                name_border[0].Render(gRenderer, NULL);

                sf = TTF_RenderText_Solid(font, "Enter player 2's name:", white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                w = sf->w, h = sf->h;
                nRect = {0, 0, w, h};
                nRect.x = 3 * SCREEN_WIDTH / 4 - w / 2;
                nRect.y = 600;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);
                name_border[1].setX(nRect.x + (w - name_border[1].getW()) / 2);
                name_border[1].setY(nRect.y + h + 50);
                name_border[1].Render(gRenderer, NULL);

                for(int i = 0; i <= 1; i++)
                {
                    if(p_name[i].size() > 8) p_name[i].pop_back();

                    if(p_name[i].size() > 1 && p_name[i][1] >= 'a' && p_name[i][1] <= 'z') p_name[i][1] -= int('a' - 'A');

                    sf = TTF_RenderText_Solid(font, p_name[i].c_str(), black);
                    tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                    w = sf->w, h = sf->h;
                    SDL_Rect tRect = {0, 0, w, h};
                    tRect.x = name_border[i].getX() + (name_border[i].getW() - w) / 2;
                    tRect.y = name_border[i].getY() + (name_border[i].getH() - h) / 2;
                    SDL_RenderCopy(gRenderer, tx, NULL, &tRect);
                }


                sf = TTF_RenderText_Solid(font, "Player's name must be between 1 and 7 letters.", red);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                w = sf->w, h = sf->h;
                nRect = {0, 0, w, h};
                nRect.x = (SCREEN_WIDTH - w) / 2;
                nRect.y = 500;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);

                return_icon.Render(gRenderer, NULL);

            }

            SDL_RenderPresent(gRenderer);


            lastTick = curTick;
        }
    }


	//Free resources and close SDL
	close();

	return 0;
}
///////Function

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
	TTF_Init();
	font = TTF_OpenFont("font/timesbd.ttf", 36);

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprites
	if(!menu.LoadImg("image/menu.png", gRenderer))
        success = false;

    if(!single_player.LoadImg("image/Singleplayer_icon.png", gRenderer))
        success = false;

    if(!multi_player.LoadImg("image/multiplayer_icon.png", gRenderer))
        success = false;

    if(!exit_icon.LoadImg("image/Exit_icon.png", gRenderer))
        success = false;

    if(!return_icon.LoadImg("image/return.png", gRenderer))
        success = false;

    if(!continue_icon.LoadImg("image/continue.png", gRenderer))
        success = false;

    if(!restart_icon.LoadImg("image/restart.png", gRenderer))
        success = false;

    if(!play_gr.LoadImg("image/play_gr.png", gRenderer))
        success = false;

    if(!X_animation.LoadImg("image/X_animation.png", gRenderer))
        success = false;

    if(!O_animation.LoadImg("image/O_animation.png", gRenderer))
        success = false;

    if(!winable.LoadImg("image/Winable.png", gRenderer))
        success = false;

    if(!unwinable.LoadImg("image/UnWinable.png", gRenderer))
        success = false;

    if(!name_border[0].LoadImg("image/name_border.png", gRenderer))
        success = false;

    if(!name_border[1].LoadImg("image/name_border.png", gRenderer))
        success = false;

    single_player.setX((SCREEN_WIDTH - single_player.getW()) / 2);
    single_player.setY(567);

    multi_player.setX(single_player.getX());
    multi_player.setY(703);

    exit_icon.setX(single_player.getX());
    exit_icon.setY(839);



    winable.setX(388);
    winable.setY(600);

    unwinable.setX(1185);
    unwinable.setY(600);

	return success;
}

void close()
{

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}
