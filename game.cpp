
#include <SDL.h>
#include <SDL_TTF.h>
#include <stdio.h>
#include <string>
#include "game.h"

int GameData::Setup() /**
					  *I set the background to a resized background picture in line 27.  Only real change I made to this from the original code.
					  */
{
	if(SDL_Init( SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL ErrorL %s \n", SDL_GetError);
		return -1;
	}
	if ((mWindow = SDL_CreateWindow("Summer 2015 Project", 100, 100, 840, 600, 0)) == NULL)
	{
		printf("SDL ErrorL %s \n", SDL_GetError());
		return -1;
	}
	if ((mScreenSurface = SDL_GetWindowSurface(mWindow)) == NULL)
	{
		printf("SDL ErrorL %s \n", SDL_GetError());
		return -1;
	}
	if ((mSurface2 = SDL_LoadBMP("images/background.bmp")) == NULL)
	{
		printf("SDL ErrorL %s \n", SDL_GetError());
		return -1;
	}
	return 0;
}
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)/**
																									  *I think this function was made to show where the text starting
																									  *point would appear.  I assume the parameter set up would be
																									  *x offset, y offset, what you want written, where you want it written.  Not too sure though
																									  */
{
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clip, destination, &offset);
}

int GameData::Draw()/**
					*Here is pretty much where I started getting lost.
					*This is where I set my font, font size, color, and the message.
					*I also attempted to use the apply surface function to blit the words but, I think that's wrong.
					*/
{
	TTF_Font *mFont = NULL;
	SDL_Surface *message;
	SDL_Color mColor = { 150, 150, 150 };
	mFont = TTF_OpenFont("images/GreatVibes-Regular.otf", 32);
	SDL_UpdateWindowSurface(mWindow);
	SDL_BlitSurface(mSurface2, NULL, mScreenSurface, NULL);
	message = TTF_RenderText_Solid(mFont, "Oh hi, I wasn't expecting you.", mColor);
	apply_surface(0, 150, mSurface2, message);
	return 0;
}

int GameData::Input()
{
	SDL_Event e;
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
	{
		mDone = true;
	}
	//else if (e.type == SDL_CLICK)//Ain't a real function, need to find function
	//{
		//return 0;
	//}
	return 0;
}
int GameData::Shutdown()
{
	SDL_FreeSurface(mSurface2);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	return 0;
}


int GameData::Run()
{
	//game loop
	do
	{
		Input();
		Draw();
	} while (!mDone);
	return 0;
}