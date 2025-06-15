#include "GameObject.hpp"

GameObject::GameObject(const char* textureSheet, int x, int y) {
	objectTexture = TextureManager::loadTexture(textureSheet);
	xpos = x;
	ypos = y;
}

GameObject::~GameObject() {

}

void GameObject::update() {
	xpos++;
	ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = srcRect.h * 2;
	destRect.w = srcRect.w * 2;
	destRect.x = xpos;
	destRect.y = ypos;
}

void GameObject::render() {
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}