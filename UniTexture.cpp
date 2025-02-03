#include "UniTexture.h"

UniTexture::UniTexture()
{
	texture = NULL;

	renderTarget = NULL;

	width = 0;
	height = 0;
}

UniTexture::~UniTexture()
{
	free();
}

void UniTexture::setRenderTarget(SDL_Renderer* renderTarget)
{
	this->renderTarget = renderTarget;
}

bool UniTexture::loadFromImage(const std::string path,const int* chromaKeyHex)
{
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, *(chromaKeyHex), *(chromaKeyHex+1), *(chromaKeyHex+2)));

		newTexture = SDL_CreateTextureFromSurface(renderTarget, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}

bool UniTexture::loadFromImage(const std::string path)
{
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{

		newTexture = SDL_CreateTextureFromSurface(renderTarget, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}

int UniTexture::getWidth()
{
	return width;
}

int UniTexture::getHeight()
{
	return height;
}

void UniTexture::render(int x,int y)
{
	SDL_Rect posRect = { x,y,width,height };

	SDL_RenderCopy(renderTarget,texture,NULL,&posRect);
}

void UniTexture::renderClipped(int x, int y)
{
	SDL_Rect posRect = { x,y,clipRect.w,clipRect.h };

	SDL_RenderCopy(renderTarget, texture, &clipRect, &posRect);
}

void UniTexture::clip(int from_x, int from_y, int w, int h)
{
	clipRect = { from_x,from_y,w,h };
}

void UniTexture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);

		width = 0;
		height = 0;
		renderTarget = NULL;
		texture = NULL;
	}
}