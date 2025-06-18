#pragma once

#include "Components.hpp"
#include "../TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component {
private:
	int animIndex = 0;

	std::map<const char*, Animation> animations;

	TransformComponent* transform;
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;

	bool animated = false;
	int frames = 0;
	int speed = 100;
	
public:

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTexture(path);
	}
	SpriteComponent(const char* path, bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("idle", idle);
		animations.emplace("walk", walk);

		play("idle");

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
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;
		
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override {
		TextureManager::draw(texture, srcRect, destRect, spriteFlip);
	}

	void play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};