#pragma once
#ifndef UNITEXTURE_H_
#define UNITEXTURE_H_

#include"SDL.h"
#include "string"
#include "SDL_image.h"

class UniTexture
{
public:
	UniTexture();
	~UniTexture();

	void setRenderTarget(SDL_Renderer* renderTarget);

	bool loadFromImage(const std::string path, const int* chromaKeyHex);
	bool loadFromImage(const std::string path);
	bool loadFromString();

	void clip(int from_x, int from_y, int w, int h);

	void render(int x, int y);
	void renderClipped(int x, int y);

	int getWidth();
	int getHeight();

	void free();

private:
	int width;
	int height;

	SDL_Texture* texture;

	SDL_Renderer* renderTarget;

	SDL_Rect clipRect;
};

#endif