#pragma once

#include "Components.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTexture(path);
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path) {
		texture = TextureManager::loadTexture(path);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void update() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}

};