
//The mouse button

#ifndef L_BUTTON_H_
#define L_BUTTON_H_

#include "../include/CommonFunction.h"
#include "../include/LButton.h"
#include "../include/LTexture.h"




class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );

		//Shows button sprite
		void render();

	private:
	    LTexture gButtonSpriteSheetTexture = NULL;

		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;
};

#endif
