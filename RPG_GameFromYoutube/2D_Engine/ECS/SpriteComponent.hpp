#pragma once

#include "Components.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
private:
	PositionComponent* position;
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTexture(path);
	}

	void setTexture(const char* path) {
		texture = TextureManager::loadTexture(path);
	}

	void init() override {
		position = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 64;
	}
	void update() override {
		destRect.x = position->x();
		destRect.y = position->y();
	}
	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}

};