/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings

#include "include/CommonFunction.h"
#include "include/BaseObject.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

bool checkAvailable();
void gameData();

//Frees media and shuts down SDL


void initData();
void winableBot();
void unwinableBot();
bool check();
int winner_checker(vector<int> board);

void close();

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
BaseObject bot_first_icon;
BaseObject player_first_icon;
BaseObject horizontal_line;
BaseObject vertical_line;
BaseObject X1_line;
BaseObject X2_line;

TTF_Font* font;
TTF_Font* fontBig;

void tester();

int status = MAIN_MENU;
bool winable_mode, player_first_mode;
string p_name[2];
vector<int> board (9, 0); ///0 = non-existent, 1 = X, 2 = O

map < vector<int>, int > optMove1; ///bot_start
map < vector<int>, int > optMove2;
int score[2];
SDL_Rect tile[9]; ///position of 9 tiles
int frame[9]; //full -1
int turn = 1;


int main( int argc, char* args[] )
{
    srand(time(0));

    gameData();

//    tester();

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

            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                    status = 0;
                if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(status == MAIN_MENU)
                    {
                        if(inRect(x, y, single_player.GetRect()))
                            status = SINGLEPLAYER;
                        else if(inRect(x, y, multi_player.GetRect()))
                        {
                            curPlayer = -1;
                            p_name[0] = p_name[1] = " ";
                            status = MULTIPLAYER;
                        }
                        else if(inRect(x, y, exit_icon.GetRect()))
                            status = 0;
                    }
                    else if(status == SINGLEPLAYER)
                    {
                        if(inRect(x, y, winable.GetRect())) {
                            winable_mode = 1;
                            status = SINGLE_FIRST_PICK;
                        }
                        if(inRect(x, y, unwinable.GetRect())) {
                            winable_mode = 0;
                            status = SINGLE_FIRST_PICK;
                        }


                        if(inRect(x, y, return_icon.GetRect()))
                            status = 1;
                    }
                    else if(status == MULTIPLAYER)
                    {
                        if(inRect(x, y, name_border[0].GetRect()))
                            curPlayer = 0;
                        else if(inRect(x, y, name_border[1].GetRect()))
                            curPlayer = 1;
                        else if(inRect(x, y, return_icon.GetRect()))
                            status = 1;
                        else if(inRect(x, y, continue_icon.GetRect()))
                        {
                            if (p_name[0].size() > 1 && p_name[1].size() > 1) {
                                score[0] = score[1] = 0;
                                status = MULTI_GAMEPLAY;
                                initData();
                            }
                        }
                        else curPlayer = -1;
                    }
                    else if (status == SINGLE_FIRST_PICK)
                    {
                        if (inRect(x, y, player_first_icon.GetRect())) {
                            player_first_mode = 1;
                            score[0] = score[1] = 0;
                            status = SINGLE_GAMEPLAY;
                            initData();
                        }
                        if (inRect(x, y, bot_first_icon.GetRect())) {
                            player_first_mode = 0;
                            score[0] = score[1] = 0;
                            status = SINGLE_GAMEPLAY;
                            initData();
                        }


                        if (inRect(x, y, return_icon.GetRect()))
                            status = SINGLEPLAYER;
                    }
                    else if (status == SINGLE_GAMEPLAY) {
                        if (inRect(x, y, return_icon.GetRect()))
                            status = SINGLE_FIRST_PICK;

                        if (inRect(x, y, restart_icon.GetRect()))
                            initData();


                        if (turn % 2 == player_first_mode && turn <= 9) {
                            for (int i = 0; i < 9; i++)
                                if (inRect(x, y, tile[i]) && board[i] == 0 && check()){
                                    board[i] = !player_first_mode + 1;
                                    frame[i] = 0;
                                    turn++;
                                    break;
                                }
                        }
                    }
                    else if (status == MULTI_GAMEPLAY) {
                        if (inRect(x, y, return_icon.GetRect()))
                            status = MULTIPLAYER;

                        if (inRect(x, y, restart_icon.GetRect()))
                            initData();

                        if (turn % 2) { if (turn <= 9)
                            for (int i = 0; i < 9; i++)
                                if (inRect(x, y, tile[i]) && board[i] == 0 && check()){
                                    board[i] = 1;
                                    frame[i] = 0;
                                    turn++;
                                }
                        }
                            else { if (turn <= 9)
                                for (int i = 0; i < 9; i++) {
                                    if (inRect(x, y, tile[i]) && board[i] == 0 && check()){
                                        board[i] = 2;
                                        frame[i] = 0;
                                        turn++;
                                    }
                            }
                        }
                    }

                }

                if(event.type == SDL_KEYDOWN)
                {
                    if(status == MULTIPLAYER && curPlayer != -1)
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

            //////////////Processing
            if(status == SINGLEPLAYER || status == SINGLE_FIRST_PICK)
            {
                return_icon.setX((SCREEN_WIDTH - return_icon.getW()) / 2);
                return_icon.setY(900);
            }
            else if (status == SINGLE_GAMEPLAY || status == MULTI_GAMEPLAY) {
                return_icon.setX(60);
                return_icon.setY(50);
            }
            else if (status == MULTIPLAYER) {
                return_icon.setX(760);
                return_icon.setY(900);

                continue_icon.setX(1060);
                continue_icon.setY(900);
            }

            if(status == SINGLE_GAMEPLAY)
            {

                int game_status = winner_checker(board); /// = 0 if draw, 1 if X wins, 2 if O wins

                if (game_status == !player_first_mode + 1 && check()) {
                    score[0]++;
                    SDL_Delay(2000);
                    initData();
                }
                else if (game_status == player_first_mode + 1 && check()) {
                    score[1]++;
                    SDL_Delay(2000);
                    initData();
                }
                else if (turn >= 10 && check()) {
                    SDL_Delay(2000);
                    initData();
                }
                //Bot Winable
                if (winable_mode) winableBot();
                else unwinableBot();
            }

            if (status == MULTI_GAMEPLAY) {

                int game_status = winner_checker(board); /// = 0 if draw, 1 if X wins, 2 if O wins

                if (game_status == 1 && check()) {
                    score[0]++;
                    SDL_Delay(2000);
                    initData();
                }
                else if (game_status == 2 && check()) {
                    score[1]++;
                    SDL_Delay(2000);
                    initData();
                }
                else if (turn >= 10 && check()) {
                    SDL_Delay(2000);
                    initData();
                }
            }

            //////////////Render
            SDL_RenderClear(gRenderer);

            if(status == MAIN_MENU)
            {
                menu.Render(gRenderer, NULL);
                single_player.Render(gRenderer, NULL);
                multi_player.Render(gRenderer, NULL);
                exit_icon.Render(gRenderer, NULL);
            }
            else if(status == SINGLEPLAYER)
            {
                menu.Render(gRenderer, NULL);
                winable.Render(gRenderer, NULL);
                unwinable.Render(gRenderer, NULL);
                return_icon.Render(gRenderer, NULL);
            }
            else if(status == MULTIPLAYER)
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
                continue_icon.Render(gRenderer, NULL);
            }
            else if (status == SINGLE_FIRST_PICK)
            {
                menu.Render(gRenderer, NULL);

                player_first_icon.SetRect(winable.GetRect());
                bot_first_icon.SetRect(unwinable.GetRect());

                player_first_icon.Render(gRenderer, NULL);
                bot_first_icon.Render(gRenderer, NULL);
                return_icon.Render(gRenderer, NULL);
            }
            else if(status == SINGLE_GAMEPLAY)
            {
                play_gr.Render(gRenderer, NULL);

                SDL_Surface* sf = NULL;
                SDL_Texture* tx = NULL;

                sf = TTF_RenderText_Solid(fontBig, "Player", white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                int w, h;
                w = sf->w, h = sf->h;
                SDL_Rect nRect = {0, 0, w, h};
                nRect.x = 200;
                nRect.y = 100;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);

                sf = TTF_RenderText_Solid(fontBig, "Bot", white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                w = sf->w, h = sf->h;
                nRect = {0, 0, w, h};
                nRect.x = 280;
                nRect.y = 820;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);

                sf = TTF_RenderText_Solid(fontBig, int2str(score[0]).c_str(), white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                w = sf->w, h = sf->h;
                nRect = {0, 0, w, h};
                nRect.x = 340;
                nRect.y = 280;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);

                sf = TTF_RenderText_Solid(fontBig, int2str(score[1]).c_str(), white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                w = sf->w, h = sf->h;
                nRect = {0, 0, w, h};
                nRect.x = 340;
                nRect.y = 650;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);

                for (int i = 0; i < 9; i++){
                    if (board[i] == 1 || board[i] == 2)
                    {
                        SDL_Rect tRect = {174 * frame[i], 0, 174, 174};
                        if(board[i] == 1)
                            SDL_RenderCopy(gRenderer, X_animation.GetObjectA(), &tRect, &tile[i]);
                        else
                            SDL_RenderCopy(gRenderer, O_animation.GetObjectA(), &tRect, &tile[i]);
                        if(frame[i] < 8)
                            frame[i]++;
                    }
                }
                return_icon.Render(gRenderer, NULL);


                restart_icon.setX(50);
                restart_icon.setY(900);
                restart_icon.Render(gRenderer, NULL);
            }
            else if (status == MULTI_GAMEPLAY) {
                play_gr.Render(gRenderer, NULL);

                SDL_Surface* sf = NULL;
                SDL_Texture* tx = NULL;

                sf = TTF_RenderText_Solid(fontBig, p_name[0].c_str(), white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                int w, h;
                w = sf->w, h = sf->h;
                SDL_Rect nRect = {0, 0, w, h};
                nRect.x = 353 - w / 2;
                nRect.y = 100;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);

                sf = TTF_RenderText_Solid(fontBig, p_name[1].c_str(), white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                w = sf->w, h = sf->h;
                nRect = {0, 0, w, h};
                nRect.x = 353 - w / 2;
                nRect.y = 820;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);

                sf = TTF_RenderText_Solid(fontBig, int2str(score[0]).c_str(), white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                w = sf->w, h = sf->h;
                nRect = {0, 0, w, h};
                nRect.x = 340;
                nRect.y = 280;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);

                sf = TTF_RenderText_Solid(fontBig, int2str(score[1]).c_str(), white);
                tx = SDL_CreateTextureFromSurface(gRenderer, sf);
                w = sf->w, h = sf->h;
                nRect = {0, 0, w, h};
                nRect.x = 340;
                nRect.y = 650;
                SDL_RenderCopy(gRenderer, tx, NULL, &nRect);

                for (int i = 0; i < 9; i++){
                    if (board[i] == 1 || board[i] == 2)
                    {
                        SDL_Rect tRect = {174 * frame[i], 0, 174, 174};
                        if(board[i] == 1)
                            SDL_RenderCopy(gRenderer, X_animation.GetObjectA(), &tRect, &tile[i]);
                        else
                            SDL_RenderCopy(gRenderer, O_animation.GetObjectA(), &tRect, &tile[i]);
                        if(frame[i] < 8)
                            frame[i]++;
                    }
                }
                return_icon.Render(gRenderer, NULL);

                restart_icon.setX(50);
                restart_icon.setY(900);
                restart_icon.Render(gRenderer, NULL);
            }

            SDL_RenderPresent(gRenderer);


            lastTick = curTick;
        }
    }

	close();

	return 0;
}
///////---------------------------------------------------Function---------------------------------------------------

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
	fontBig = TTF_OpenFont("font/timesbd.ttf", 120);

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

    if(!player_first_icon.LoadImg("image/player_first_icon.png", gRenderer))
        success = false;

    if(!bot_first_icon.LoadImg("image/bot_first_icon.png", gRenderer))
        success = false;

    if(!horizontal_line.LoadImg("image/horizontal.png", gRenderer))
        success = false;

    if(!vertical_line.LoadImg("image/vertical.png", gRenderer))
        success = false;

    if(!X1_line.LoadImg("image/X1.png", gRenderer))
        success = false;

    if(!X2_line.LoadImg("image/X2.png", gRenderer))
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

bool checkAvailable() {
    for (int i = 0; i < 9; i++)
        if (board[i] == 0) return true;

    return false;
}

void winableBot() {
    int p;
    if (turn % 2 != player_first_mode && turn <= 9 && check()) {
        p = rand() % 9;

        while (board[p] != 0)
            p = rand() % 9;

        board[p] = player_first_mode + 1;
        turn++;
        frame[p] = 0;
    }
}

int minimax(vector<int> board, int depth, bool bot_turn);

void unwinableBot() {
    int p, mid;
    int res = INT_MIN;
    if (turn % 2 != player_first_mode && turn <= 9 && check()) {
        for (int i = 0; i < 9; i++)
            if (board[i] == 0) {
                board[i] = player_first_mode + 1;

                mid = minimax(board, 9 - turn, 1);
                board[i] = 0;

                if (mid > res) {
                    res = mid;
                    p = i;
                }

            }
        board[p] = player_first_mode + 1;
        turn++;
        frame[p] = 0;
    }
}

int minimax(vector<int> board, int depth, bool bot_turn) {
    if (depth == 0)
        return 0;

    int res = 0;
    int game_status = winner_checker(board);
    if (game_status == !player_first_mode + 1) {
        return -depth;
    }
    else if (game_status == player_first_mode + 1) {
        return depth;
    }

    for (int i = 0; i < 9; i++)
        if (board[i] == 0) {
            if (bot_turn) {
                res = INT_MIN;
                board[i] = player_first_mode + 1;
                res = max(res, minimax(board, depth - 1, 0));
            }
            else {
                res = INT_MAX;
                board[i] = !player_first_mode + 1;
                res = min(res, minimax(board, depth - 1, 1));
            }
            board[i] = 0;
        }

    return res;
}
void gameData() {
    for (int i = 0; i < 9; i++)
        if (i == 0) tile[i] = {736, 48, 307, 307};
        else tile[i] = {tile[0].x + (i % 3) * 335, tile[0].y + (i / 3) * 335, 307, 307};
}

void initData() {
    for (int i = 0; i < 9; i++) {
        board[i] = 0;
        frame[i] = -1;
    }
    turn = 1;
}

bool check()
{
    for(int i = 0; i < 9; i++)
    {
        if(board[i] > 0 && frame[i] < 8)
            return false;
    }
    return true;
}

int winner_checker(vector<int> board) {
    if (board[0] == board[1] && board[1] == board[2] && board[0] != 0) return board[0];
    if (board[3] == board[4] && board[4] == board[5] && board[3] != 0) return board[3];
    if (board[6] == board[7] && board[7] == board[8] && board[6] != 0) return board[6];
    if (board[0] == board[3] && board[3] == board[6] && board[0] != 0) return board[0];
    if (board[1] == board[4] && board[4] == board[7] && board[1] != 0) return board[1];
    if (board[2] == board[5] && board[5] == board[8] && board[2] != 0) return board[2];
    if (board[0] == board[4] && board[4] == board[8] && board[0] != 0) return board[0];
    if (board[2] == board[4] && board[4] == board[6] && board[2] != 0) return board[2];

    return 0;
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
