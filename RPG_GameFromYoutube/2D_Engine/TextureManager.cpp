#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* fileName) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* playerTex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);

	SDL_FreeSurface(tmpSurface);

	return playerTex;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect &src, SDL_Rect &dest) {
	int result = SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}