//Hand image adapted from freepik
//Hourglass image adapted from vecteezy

#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"
#include "string"
#include "UniTexture.h"

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;

//Paths go here, make more vars if needed, set to "NULL" if nothing to load
const std::string texturePath = "Hourglass.png";
const std::string backPath = "Hand.jpg";

//!Make sure to include all necessary flags! here by or'ing them together (e.g 'imgInitFlags = IMG_INIT_JPG | IMG_INIT_PNG' )
const int sdlInitFlags = SDL_INIT_VIDEO;
const int imgInitFlags = IMG_INIT_JPG;
const int windowFlags = 0;
const int rendererFlags = SDL_RENDERER_PRESENTVSYNC;

//window creation values -- !See flags section for windowFlags!
const int window_w = 1000;
const int window_h = 500;
const int window_x = SDL_WINDOWPOS_UNDEFINED;
const int window_y = SDL_WINDOWPOS_UNDEFINED;
const char windowTitle[5] = "Test"; //!Make sure to update size when changing titles!

bool init()
{
	bool success = true;
	if (SDL_Init(sdlInitFlags) < 0)
	{
		printf("Failed to initialize SDL subsystems! ERR:%s\n", SDL_GetError());
		success = false;
	}
	else if (!(IMG_Init(imgInitFlags) & imgInitFlags))
	{
		printf("Failed to initialize SDL_image subsystems! ERR:%s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow(windowTitle, window_x, window_y, window_w, window_h, windowFlags);
		if (gWindow == NULL)
		{
			printf("Failed to create window! Err:%s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, rendererFlags);
			if (gRenderer == NULL)
			{
				printf("Failed to generate renderer from window! Err:%s\n", SDL_GetError());
				success = false;
			}
		}
	}
	return success;
}

void close()
{
	SDL_FreeSurface(gScreenSurface);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	//Destroy/free all other globals

	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Could not initialize!");
	}
	else
	{

		UniTexture testure;
		UniTexture backText;

		testure.setRenderTarget(gRenderer);
		backText.setRenderTarget(gRenderer);

		if (!testure.loadFromImage(texturePath, new int[3] {0, 255, 255}))
		{
			printf("Could not generate texture from %s!", texturePath.c_str());
		}
		else if (!backText.loadFromImage(backPath))
		{
			printf("Could not generate texture from %s!", backPath.c_str());
			testure.free();
		}
		else
		{
			int sprite_w = 179;
			int sprite_h = 470;
			int spriteBuff_x = 20;
			int spriteBuff_y = 87;
			int frameT = 8;
			int frameTop = frameT*6;
			int spriteRender_x = 560 - sprite_w/2;
			int spriteRender_y = 500 - sprite_h;

			backText.render(0,0);
			testure.renderClipped(spriteRender_x, spriteRender_y);
			SDL_RenderPresent(gRenderer);

			SDL_Event e; //event tracker
			bool quit = false;
			int frame = 0;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
						quit = true;
				}

				if (!(frame % frameT))
				{
					testure.clip(sprite_w * frame / frameT+spriteBuff_x, spriteBuff_y,sprite_w,sprite_h);

					if (frame == frameTop)
						frame = 0;
				}

				backText.render(0, 0);
				testure.renderClipped(spriteRender_x, spriteRender_y);

				SDL_RenderPresent(gRenderer);

				frame++;
			}

			testure.free();
			backText.free();
		}
	}
	close();

	return 0;
}