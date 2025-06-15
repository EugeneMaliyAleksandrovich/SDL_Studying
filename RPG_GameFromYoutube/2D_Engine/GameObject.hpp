#pragma once

#include "Game.hpp"
#include "TextureManager.hpp"

class GameObject {
public:
	SDL_Texture* objectTexture;

	GameObject(const char* textureSheet, int x = 0, int y = 0);
	~GameObject();

	void update();
	void render();

private:
	int xpos;
	int ypos;

	
	SDL_Rect srcRect, destRect;
};